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

struct Coordinate {
    int x;
    int y;

    Coordinate(int x, int y) : x(x), y(y) {}
    Coordinate() : x(0), y(0) {}
};

struct JointValue{
    float theta1;
    float theta2;

    JointValue(float theta1, float theta2) : theta1(theta1), theta2(theta2) {}
    JointValue() : theta1(0.0), theta2(0.0) {}
};

struct Number {
    std::map<int, std::vector<Coordinate>> coordinates; // This is in our coordinate frame (in centimeters)
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
    };
} Numbers;


const int motor_1 = 1;
const int motor_10 = 10;
std::mutex num_mutex_;

std::vector<JointValue> tcp_to_joint_transform(const Coordinate& from, const Coordinate& to, const int& steps = 10) {
    std::vector<JointValue> trajectory(steps);
    
    for (int i = 0; i < steps; i++) {
        double a = i / static_cast<double>(steps);
        float x = from.x + a * (to.x - from.x);
        float y = from.y + a * (to.y - from.y);

        //Inverse kinematics
        float theta1 = static_cast<float>(x);
        float theta2 = static_cast<float>(y);

        trajectory[i] = {theta1, theta2};
    }

    return trajectory;
}

std::vector<JointValue> draw_number(const std::vector<Coordinate>& number, const int& steps = 10) {
    std::vector<JointValue> trajectory;
    
    for (int i {1}; i < number.size(); i++) {
        std::vector<JointValue> single_trajectory = tcp_to_joint_transform(number.at(i - 1), number.at(i), steps);
        for(int j {0}; j < single_trajectory.size(); j++){
            trajectory.emplace_back(single_trajectory[j]);
        }
    }
    
    return trajectory;
}

class NumberDrawerNode : public rclcpp::Node
{
public:
    NumberDrawerNode() : Node("number_drawer")
    {
        // Initialize the map
        // initialize_map();

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
        if (Numbers.coordinates.find(num) == Numbers.coordinates.end())
        {
            RCLCPP_ERROR(this->get_logger(), "Invalid number: %d", num);
            response->done = false;
            return;
        }

        std::vector<JointValue> trajec = draw_number(Numbers.coordinates[num]);

        // // Publish motor positions
        for (size_t i = 0; i < trajec.size(); i++)
        {
            auto message = dynamixel_sdk_custom_interfaces::msg::SetPositionMultiple();
            message.id_1 = motor_1; // motor ID for first motor
            message.position_1 = static_cast<int>(trajec[i].theta1);

            message.id_2 = motor_10; // motor ID for second motor
            message.position_2 = static_cast<int>(trajec[i].theta2);

            //Publish the message
            RCLCPP_INFO(this->get_logger(), "Publishing to motor ID %d: position=%d", message.id_1, message.position_1);
            RCLCPP_INFO(this->get_logger(), "Publishing to motor ID %d: position=%d", message.id_2, message.position_2);
            //publisher_->publish(message);

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
