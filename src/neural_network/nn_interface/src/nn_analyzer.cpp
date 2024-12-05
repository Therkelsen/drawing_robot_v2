#include "rclcpp/rclcpp.hpp"
#include <cv_bridge/cv_bridge.h>
#include <fstream>
#include <map>
#include <memory>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <unistd.h>
#include <cstdint>
#include <vector>
#include <xnn_inference.h>
#include "drawer/msg/num.hpp"

class NNAnalyzer : public rclcpp::Node
{
public:
    NNAnalyzer() : Node("neural_network_analyzer")
    {
        data_size_bytes = 100 * sizeof(float);
        int res = (int)XNn_inference_Initialize(&nn, "nn_inference");
        RCLCPP_INFO(this->get_logger(), "IP Ready? %s", res == 0 ? "true" : "false");
        if(res)
            exit(1);

        // Create the publisher
        camera_subscription_ = this->create_subscription<sensor_msgs::msg::Image>("/image_ds", 10, 
            std::bind(&NNAnalyzer::onImageMsg, this, std::placeholders::_1));

        number_publisher_ = this->create_publisher<drawer::msg::Num>("/number", 10);

        RCLCPP_INFO(this->get_logger(), "Ready to interact with the FPGA.");
    }

private:
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr camera_subscription_;
    rclcpp::Publisher<drawer::msg::Num>::SharedPtr number_publisher_;
    int data_size_bytes;
    XNn_inference nn;
    int times_to_log = 300;
    int times_logged = 0;

    void onImageMsg(const sensor_msgs::msg::Image::SharedPtr msg) {
			RCLCPP_INFO(this->get_logger(), "Received image!");

			cv_bridge::CvImagePtr cv_ptr = cv_bridge::toCvCopy(msg, msg->encoding);
			cv::Mat img = cv_ptr->image;

            float arr[100] = {0};
            
            // Resetting input array

            // Start timer
            rclcpp::Time start = this->get_clock()->now();
            XNn_inference_Write_input_img_Bytes(&nn, 0, (char*)arr, data_size_bytes);
            
            for(unsigned int i = 0; i < 10; i++){
                for(unsigned int j = 0; j < 10; j++){
                    arr[i*10 + j] = (img.at<uchar>(i, j))/255.0;
                }
            }

            XNn_inference_Write_input_img_Bytes(&nn, 0, (char*)arr, data_size_bytes);

            XNn_inference_Start(&nn);

            while(!XNn_inference_IsDone(&nn)){
          	    // usleep(100);
            }
            
            int out_r_value = (int)XNn_inference_Get_out_r(&nn);

            // Stop timer
            rclcpp::Time stop = this->get_clock()->now();
            auto delta_t = (stop-start).nanoseconds();

            if(times_logged < times_to_log) {
                times_logged++;
                // Log to CSV file
                std::ofstream csv_file("alite.csv", std::ios::app); // Open file in append mode
                if (csv_file.is_open()) {
                    csv_file << delta_t << "\n"; // Write the delta_t in nanoseconds
                    csv_file.close(); // Close the file
                    RCLCPP_INFO(this->get_logger(), "Logged %d times", times_logged);
                } else {
                    RCLCPP_ERROR(this->get_logger(), "Unable to open the CSV file for logging!");
                }
            }


			RCLCPP_INFO(this->get_logger(), "The image resulted in number: %d", out_r_value);
            // callDrawService(out_r_value);
            publishData(out_r_value);
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

    auto node = std::make_shared<NNAnalyzer>();
    rclcpp::spin(node);

    rclcpp::shutdown();
    return 0;
}