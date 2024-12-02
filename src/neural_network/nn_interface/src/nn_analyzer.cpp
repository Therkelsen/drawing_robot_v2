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

    void onImageMsg(const sensor_msgs::msg::Image::SharedPtr msg) {
			RCLCPP_INFO(this->get_logger(), "Received image!");

			cv_bridge::CvImagePtr cv_ptr = cv_bridge::toCvCopy(msg, msg->encoding);
			cv::Mat img = cv_ptr->image;

            float arr[100] = {0};

            // 1
            // float arr[100] = {0.0, 0.0, 0.0, 0.0, 0.003921569, 0.003921569, 0.015686275, 0.019607844, 0.003921569, 0.0,
            //                   0.0, 0.0, 0.0, 0.003921569, 0.0, 0.02745098, 0.13725491, 0.015686275, 0.007843138, 0.0,
            //                   0.0, 0.0, 0.0, 0.003921569, 0.003921569, 0.34117648, 0.6, 0.015686275, 0.015686275, 0.0,
            //                   0.0, 0.0, 0.0, 0.011764706, 0.007843138, 0.60784316, 0.54509807, 0.015686275, 0.007843138, 0.0,
            //                   0.0, 0.0, 0.0, 0.007843138, 0.13725491, 0.9490196, 0.19607843, 0.019607844, 0.003921569, 0.0,
            //                   0.0, 0.0, 0.0, 0.007843138, 0.4627451, 0.627451, 0.019607844, 0.007843138, 0.007843138, 0.0,
            //                   0.0, 0.0, 0.0, 0.011764706, 0.68235296, 0.2901961, 0.0, 0.0, 0.0, 0.0,
            //                   0.0, 0.0, 0.0, 0.02745098, 0.7529412, 0.0627451, 0.0, 0.0, 0.0, 0.0,
            //                   0.0, 0.0, 0.0, 0.02745098, 0.6901961, 0.11372549, 0.0, 0.0, 0.0, 0.0,
            //                   0.0, 0.0, 0.0, 0.007843138, 0.015686275, 0.007843138, 0.0, 0.0, 0.0, 0.0};

            // 4
            // float arr[100] = {0.003921569, 0.007843138, 0.003921569, 0.007843138, 0.003921569, 0.007843138, 0.003921569, 0.007843138, 0.003921569, 0.0,
            //                   0.003921569, 0.023529412, 0.1254902, 0.003921569, 0.003921569, 0.003921569, 0.007843138, 0.003921569, 0.003921569, 0.0,
            //                   0.011764706, 0.011764706, 0.6745098, 0.023529412, 0.007843138, 0.003921569, 0.11372549, 0.05490196, 0.003921569, 0.0,
            //                   0.011764706, 0.043137256, 0.7058824, 0.043137256, 0.011764706, 0.019607844, 0.49411765, 0.34901962, 0.007843138, 0.0,
            //                   0.007843138, 0.21176471, 0.85490197, 0.6039216, 0.44705883, 0.5882353, 0.654902, 0.36862746, 0.011764706, 0.0,
            //                   0.007843138, 0.5411765, 0.2509804, 0.05882353, 0.0627451, 0.023529412, 0.35686275, 0.37254903, 0.007843138, 0.0,
            //                   0.007843138, 0.05490196, 0.019607844, 0.0, 0.0, 0.003921569, 0.31764707, 0.53333336, 0.003921569, 0.0,
            //                   0.011764706, 0.015686275, 0.015686275, 0.0, 0.0, 0.003921569, 0.1764706, 0.67058825, 0.007843138, 0.0,
            //                   0.007843138, 0.007843138, 0.007843138, 0.0, 0.0, 0.0, 0.07058824, 0.6, 0.007843138, 0.0,
            //                   0.0, 0.0, 0.0, 0.0, 0.0, 0.003921569, 0.011764706, 0.023529412, 0.011764706, 0.0};
            
            // Resetting input array
            XNn_inference_Write_input_img_Bytes(&nn, 0, (char*)arr, data_size_bytes);
            
            for(unsigned int i = 0; i < 10; i++){
                for(unsigned int j = 0; j < 10; j++){
                    arr[i*10 + j] = (img.at<uchar>(i, j))/255.0;
                }
            }

            XNn_inference_Write_input_img_Bytes(&nn, 0, (char*)arr, data_size_bytes);

            XNn_inference_Start(&nn);

            while(!XNn_inference_IsDone(&nn)){
          	    usleep(100);
            }
            
            int out_r_value = (int)XNn_inference_Get_out_r(&nn);

			RCLCPP_INFO(this->get_logger(), "The image resulted in number: %d", out_r_value);
            // callDrawService(out_r_value);
            publishData(out_r_value);
		}

    // void callDrawService(const int& num_to_draw) {
    //     RCLCPP_INFO(this->get_logger(), "Calling Number drawing service.");
    //     // Create a client for the '/number' service
    //     client_ = this->create_client<drawer::srv::Number>("/number");

    //     // Wait until the service is available
    //     while (!client_->wait_for_service(std::chrono::seconds(1))) {
    //         if (!rclcpp::ok()) {
    //             RCLCPP_ERROR(this->get_logger(), "Interrupted while waiting for the service. Exiting.");
    //             return;
    //         }
    //         RCLCPP_INFO(this->get_logger(), "Waiting for service /number...");
    //     }

    //     // Create a request and set the value of 'num'
    //     auto request = std::make_shared<drawer::srv::Number::Request>();
    //     request->num = num_to_draw;

    //     // Call the service asynchronously
    //     auto result = client_->async_send_request(request);

    //     // Wait for the result
    //     if (rclcpp::spin_until_future_complete(this->get_node_base_interface(), result) == rclcpp::FutureReturnCode::SUCCESS) {
    //         RCLCPP_INFO(this->get_logger(), "Service call succeeded.");
    //     } else {
    //         RCLCPP_ERROR(this->get_logger(), "Service call failed.");
    //     }
    // }
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