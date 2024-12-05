#include "rclcpp/rclcpp.hpp"
#include <cv_bridge/cv_bridge.h>
#include <map>
#include <memory>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <unistd.h>
#include <cstdint>
#include <vector>
#include "drawer/msg/num.hpp"
#include <algorithm>
#include <cmath>
#include "nn_analyzer.hpp"


/* Layer 1 matrix multiplication */
void l1_mm(float input[n_inputs], const float weights[n_inputs][n_layer1], float (&output)[1][n_layer1]) {
    for (int j = 0; j < n_layer1; ++j) {
        // #pragma HLS UNROLL
        float sum = 0;
        for (int k = 0; k < n_inputs; ++k) {
            // #pragma HLS UNROLL
            sum += input[k] * weights[k][j];
        }
        output[0][j] = sum;
    }
}

/* Layer 2 matrix multiplication */
void l2_mm(float input[1][n_layer1], const float weights[n_layer1][n_layer2], float (&output)[1][n_layer2]) {
    for (int j = 0; j < n_layer2; ++j) {
        // #pragma HLS UNROLL
        float sum = 0;
        for (int k = 0; k < n_layer1; ++k) {
            // #pragma HLS UNROLL
            sum += input[0][k] * weights[k][j];
        }
        output[0][j] = sum;
    }
}

/* Layer 3 matrix multiplication */
void l3_mm(float input[1][n_layer2], const float weights[n_layer2][n_layer3], float (&output)[1][n_layer3]) {
    for (int j = 0; j < n_layer3; ++j) {
        // #pragma HLS UNROLL
        float sum = 0;
        for (int k = 0; k < n_layer2; ++k) {
            // #pragma HLS UNROLL
            sum += input[0][k] * weights[k][j];
        }
        output[0][j] = sum;
    }
}

/* ReLU layer 1 activation function */
void l1_relu(float input[1][n_layer1], float (&output)[1][n_layer1]) {
    for (int i = 0; i < n_layer1; ++i) {
        // #pragma HLS UNROLL
        output[0][i] = std::max(0.0f, input[0][i]);
    }
}

/* ReLU layer 2 activation function */
void l2_relu(float input[1][n_layer2], float (&output)[1][n_layer2]) {
    for (int i = 0; i < n_layer2; ++i) {
        // #pragma HLS UNROLL
        output[0][i] = std::max(0.0f, input[0][i]);
    }
}

/* Softmax layer 3 activation function */
void l3_softmax(float input[1][n_layer3], int &pred) {
    int max_idx = -1;
    float max_val = -std::numeric_limits<float>::infinity();

    for (int i = 0; i < n_layer3; ++i) {
        // #pragma HLS UNROLL
        if (input[0][i] > max_val) {
            max_idx = i;
            max_val = input[0][i];
        }
    }
    pred = max_idx;
}


class NNAnalyzerCpu : public rclcpp::Node
{
public:
    NNAnalyzerCpu() : Node("neural_network_analyzer")
    {
        // Create the publisher
        camera_subscription_ = this->create_subscription<sensor_msgs::msg::Image>("/image_ds", 10, 
            std::bind(&NNAnalyzerCpu::onImageMsg, this, std::placeholders::_1));

        number_publisher_ = this->create_publisher<drawer::msg::Num>("/number", 10);

        RCLCPP_INFO(this->get_logger(), "Ready to interact with the FPGA.");
    }

private:
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr camera_subscription_;
    rclcpp::Publisher<drawer::msg::Num>::SharedPtr number_publisher_;
    int data_size_bytes;
    int times_to_log = 30;
    int times_logged = 0;

    void onImageMsg(const sensor_msgs::msg::Image::SharedPtr msg) {
			RCLCPP_INFO(this->get_logger(), "Received image!");

			cv_bridge::CvImagePtr cv_ptr = cv_bridge::toCvCopy(msg, msg->encoding);
			cv::Mat img = cv_ptr->image;

            float arr[100] = {0};

            for(unsigned int i = 0; i < 10; i++){
                for(unsigned int j = 0; j < 10; j++){
                    arr[i*10 + j] = (img.at<uchar>(i, j))/255.0;
                }
            }

            float temp_output[1][n_layer1] = {0};
            float temp_output2[1][n_layer2] = {0};
            float temp_output3[1][n_layer3] = {0};
            int prediction = -1;

            rclcpp::Time start = this->get_clock()->now();

            l1_mm(arr, weights::layer1_weights, temp_output);
            l1_relu(temp_output, temp_output);
            l2_mm(temp_output, weights::layer2_weights, temp_output2);
            l2_relu(temp_output2, temp_output2);
            l3_mm(temp_output2, weights::layer3_weights, temp_output3);
            l3_softmax(temp_output3, prediction);

            // Stop timer
            rclcpp::Time stop = this->get_clock()->now();
            auto delta_t = (stop-start).nanoseconds();

            if(prediction == 9 && times_logged < times_to_log) {
                times_logged++;
                // Log to CSV file
                std::ofstream csv_file("9_u96_cpu.csv", std::ios::app); // Open file in append mode
                if (csv_file.is_open()) {
                    csv_file << delta_t << "\n"; // Write the delta_t in nanoseconds
                    csv_file.close(); // Close the file
                    RCLCPP_INFO(this->get_logger(), "Logged %d times", times_logged);
                } else {
                    RCLCPP_ERROR(this->get_logger(), "Unable to open the CSV file for logging!");
                }
            }

			RCLCPP_INFO(this->get_logger(), "The image resulted in number: %d", prediction);
            publishData(prediction);
		}

    void publishData(int num)
        {
            auto message = drawer::msg::Num();
            message.num = num; // Populate your message fields
            number_publisher_->publish(message);
        }


};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);

    auto node = std::make_shared<NNAnalyzerCpu>();
    rclcpp::spin(node);

    rclcpp::shutdown();
    return 0;
}