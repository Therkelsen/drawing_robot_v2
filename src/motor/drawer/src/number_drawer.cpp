#include "rclcpp/rclcpp.hpp"
#include "drawer/srv/draw.hpp"
#include "drawer/msg/num.hpp"
#include "dynamixel_sdk_custom_interfaces/msg/set_position_multiple.hpp"
#include <map>
#include <vector>
#include <memory>
#include <unistd.h>
#include <mutex>
#include <chrono>
#include <utility>

// For each number, we have an array of motor values [motor1, motor2]

struct Number {
    std::map<int, std::vector<std::pair<int, int>>> coordinates; // This is in our coordinate frame (in centimeters)
    Number() {
        coordinates[0] = {{0, 0}, {5, 0}, {5, 5},  {5, 10}, {0, 10}, {0, 5},  {0, 0}};
        coordinates[1] = {{0, 0}, {0, 5}, {0, 10}, {0, 5},  {0, 0}};
        coordinates[2] = {{0, 0}, {5, 0}, {5, 5},  {0, 5},  {0, 10}, {5, 10}, {0, 10}, {0, 5},  {5, 5},  {5, 0},  {0, 0}};
        coordinates[3] = {{0, 0}, {5, 0}, {0, 0},  {0, 5},  {5, 5},  {0, 5},  {0, 10}, {5, 10}, {0, 10}, {0, 5},  {0, 0}};
        coordinates[4] = {{0, 0}, {0, 5}, {0, 10}, {0, 5},  {5, 5},  {5, 10}, {5, 5},  {0, 5},  {0, 0}};
        coordinates[5] = {{0, 0}, {5, 0}, {0, 0},  {0, 5},  {5, 5},  {5, 10}, {0, 10}, {5, 10}, {5, 5},  {0, 5},  {0, 0}};
        coordinates[6] = {{0, 0}, {0, 5}, {0, 0},  {5, 0},  {5, 5},  {0, 5},  {5, 5},  {5, 10}, {0, 10}, {5, 10}, {5, 5}, {5, 0}, {0, 0}};
        coordinates[7] = {{0, 0}, {0, 5}, {0, 10}, {5, 10}, {0, 10}, {0, 5},  {0, 0}};
        coordinates[8] = {{0, 0}, {5, 0}, {5, 5},  {0, 5},  {0, 10}, {5, 10}, {5, 5},  {0, 5},  {0, 0}};
        coordinates[9] = {{0, 0}, {0, 5}, {0, 10}, {5, 10}, {5, 5},  {0, 5},  {0, 0}};
    }
} Numbers;

const int motor_1 = 1;
const int motor_10 = 10;
std::mutex num_mutex_;

std::vector<std::pair<int, int>> tcp_to_joint_transform(const std::pair<int, int>& from, const std::pair<int, int>& to, const int& steps = 10) {
    double a {1/steps};

    std::vector<std::pair<int, int>> trajectory(steps);

    for (int i {0}; i < steps - 1; i++) {
        int x {from.first + a * (to.first - from.first);
        int y {from.second + a * (to.second - from.second)};
        
        trajectory.at(i) = {x, y};
        a += a;
    }

    return trajectory;
}

std::vector<std::vector<std::pair<int, int>>> draw_number(const std::vector<std::pair<int, int>>& number, const int& steps = 10) {
    std::vector<std::pair<int, int>> trajectory(number.size() * steps);
    
    for (int i {1}; i < number.size() * steps; i++) {
        trajectory.at(i) = tcp_to_joint_transform(number.at(i - 1), number.at(i));
    }
    
    return trajectory;
}

class NumberDrawerNode : public rclcpp::Node
{
public:
    NumberDrawerNode() : Node("number_drawer")
    {
        // Initialize the map
        initialize_map();

        num_ = - 1;

        publisher_ = this->create_publisher<dynamixel_sdk_custom_interfaces::msg::SetPositionMultiple>("/set_position", 1);

        // Create the service
        service_ = this->create_service<drawer::srv::Draw>(
            "number", std::bind(&NumberDrawerNode::draw, this, std::placeholders::_1, std::placeholders::_2));

        number_subscription_ = this->create_subscription<drawer::msg::Num>("/number", 10, 
            std::bind(&NumberDrawerNode::onNumber, this, std::placeholders::_1));

        RCLCPP_INFO(this->get_logger(), "Ready to draw a number.");
    }

private:
    void onNumber(const drawer::msg::Num::SharedPtr msg) {
        std::lock_guard<std::mutex> lock(num_mutex_);
        num_ = msg->num;
    }

    void draw(const std::shared_ptr<drawer::srv::Draw::Request> request,
              std::shared_ptr<drawer::srv::Draw::Response> response)
    {
        std::lock_guard<std::mutex> lock(num_mutex_);
        int num = num_;
        RCLCPP_INFO(this->get_logger(), "Incoming request to draw number: %d", num);

        // Ensure the number is valid
        if (mp.find(num) == mp.end())
        {
            RCLCPP_ERROR(this->get_logger(), "Invalid number: %d", num);
            response->done = false;
            return;
        }

        std::vector<std::vector<std::pair<int, int>>> trajectories(Numbers.coord)
        for (size_t i = 0; i < Numbers.coordinates[num].size(); i++) {

        }

        // Publish motor positions
        for (size_t i = 0; i < mp[num].size(); i++)
        {
            auto message = dynamixel_sdk_custom_interfaces::msg::SetPositionMultiple();
            message.id_1 = motor_1; // motor ID for first motor
            message.position_1 = mp[num][i].first;

            message.id_2 = motor_10; // motor ID for second motor
            message.position_2 = mp[num][i].second;

            // Publish the message
            RCLCPP_INFO(this->get_logger(), "Publishing to motor ID %d: position=%d", message.id_1, message.position_1);
            RCLCPP_INFO(this->get_logger(), "Publishing to motor ID %d: position=%d", message.id_2, message.position_2);
            publisher_->publish(message);

            sleep(1);
        }

        // Set the response
        response->done = true;
        RCLCPP_INFO(this->get_logger(), "Number %d drawn successfully.", num);
    }

    rclcpp::Publisher<dynamixel_sdk_custom_interfaces::msg::SetPositionMultiple>::SharedPtr publisher_;
    rclcpp::Subscription<drawer::msg::Num>::SharedPtr number_subscription_;
    rclcpp::Service<drawer::srv::Draw>::SharedPtr service_;
    int num_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);

    auto node = std::make_shared<NumberDrawerNode>();
    rclcpp::spin(node);

    rclcpp::shutdown();
    return 0;
}
