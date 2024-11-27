#include "drawer/srv/number.hpp"
#include "rclcpp/rclcpp.hpp"
#include <cv_bridge/cv_bridge.h>
#include <map>
#include <memory>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <unistd.h>
#include <vector>
#include <xnn_inference.h>

class NNAnalyzer : public rclcpp::Node
{
public:
    NNAnalyzer() : Node("neural_network_analyzer")
    {
        data_size_bytes = 100 * sizeof(int);
        int res = (int)XNn_inference_Initialize(&nn, "nn_inference");
        RCLCPP_INFO(this->get_logger(), "IP Ready? %s", res == 0 ? "true" : "false");
        if(res)
            exit(1);

        // Create the publisher
        camera_subscription_ = this->create_subscription<sensor_msgs::msg::Image>("/image_ds", 10, 
            std::bind(&NNAnalyzer::onImageMsg, this, std::placeholders::_1));

        RCLCPP_INFO(this->get_logger(), "Ready to interact with the FPGA.");
    }

private:
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr camera_subscription_;
    rclcpp::Client<drawer::srv::Number>::SharedPtr client_;
    int data_size_bytes;
    XNn_inference nn;

    void onImageMsg(const sensor_msgs::msg::Image::SharedPtr msg) {
			RCLCPP_INFO(this->get_logger(), "Received image!");

			cv_bridge::CvImagePtr cv_ptr = cv_bridge::toCvCopy(msg, msg->encoding);
			cv::Mat img = cv_ptr->image;

            int arr[100] ={0};
            
            // Resetting input array
            XNn_inference_Write_input_img_Bytes(&nn, 0, (char*)arr, data_size_bytes);
            
            for(unsigned int i = 0; i < 10; i++){
                for(unsigned int j = 0; j < 10; j++){
                    arr[i*10 + j] = img.at<uchar>(i, j);
                }
            }

            XNn_inference_Write_input_img_Bytes(&nn, 0, (char*)arr, data_size_bytes);

            XNn_inference_Start(&nn);

            while(!XNn_inference_IsDone(&nn)){
          	    usleep(100);
            }
            
            int out_r_value = (int)XNn_inference_Get_out_r(&nn);

			RCLCPP_INFO(this->get_logger(), "The image resulted in number: %d", out_r_value);
            callDrawService(out_r_value);
		}

    void callDrawService(const int& num_to_draw) {
        RCLCPP_INFO(this->get_logger(), "Calling Number drawing service.");
        // Create a client for the '/number' service
        client_ = this->create_client<drawer::srv::Number>("/number");

        // Wait until the service is available
        while (!client_->wait_for_service(std::chrono::seconds(1))) {
            if (!rclcpp::ok()) {
                RCLCPP_ERROR(this->get_logger(), "Interrupted while waiting for the service. Exiting.");
                return;
            }
            RCLCPP_INFO(this->get_logger(), "Waiting for service /number...");
        }

        // Create a request and set the value of 'num'
        auto request = std::make_shared<drawer::srv::Number::Request>();
        request->num = num_to_draw;

        // Call the service asynchronously
        auto result = client_->async_send_request(request);

        // Wait for the result
        if (rclcpp::spin_until_future_complete(this->get_node_base_interface(), result) == rclcpp::FutureReturnCode::SUCCESS) {
            RCLCPP_INFO(this->get_logger(), "Service call succeeded.");
        } else {
            RCLCPP_ERROR(this->get_logger(), "Service call failed.");
        }
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