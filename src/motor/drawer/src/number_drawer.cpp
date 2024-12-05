#include "drawer/msg/num.hpp"
#include "drawer/srv/draw.hpp"
#include "dynamixel_sdk_custom_interfaces/msg/set_position_multiple.hpp"
#include "rclcpp/rclcpp.hpp"
#include <chrono>
#include <cmath>
#include <eigen3/Eigen/Dense>
#include <map>
#include <memory>
#include <mutex>
#include <unistd.h>
#include <utility>
#include <vector>

// For each number, we have an array of motor values [motor1, motor2]

struct Coordinate {
    double x;
    double y;

    Coordinate(double x, double y) : x(x), y(y) {}
    Coordinate() : x(0), y(0) {}
};

struct JointValue{
    double theta;
    double phi;

    JointValue(double theta, double phi) : theta(theta), phi(phi) {}
    JointValue() : theta(0.0), phi(0.0) {}
};

struct Number {
    std::map<int, std::vector<Coordinate>> coordinates; // This is in our coordinate frame (in centimeters)
    Number() {
        double scale = 1; 
        double zero = 0 * scale;
        double one = 1 * scale;
        double two = 2 * scale;

        coordinates[0] = {{zero, -one}, {two, -one}, {two, one},   {zero, one},  {-two, one},  {-two, -one}, {zero, -one}};
        coordinates[1] = {{zero, -one}, {two, -one}, {zero, -one}, {-two, -one}, {zero, -one}};
        coordinates[2] = {{zero, -one}, {two, -one}, {two, one},   {two, -one},  {zero, -one}, {zero, one},  {-two, one}, {-two, -one},  {-two, one},  {zero, one},   {zero, -one}};
        coordinates[3] = {{zero, -one}, {two, -one}, {two, one},   {two, -one},  {zero, -one}, {zero, one},  {zero, -one}, {-two, -one}, {-two, one},  {-two, -one},  {zero, -one}};
        coordinates[4] = {{zero, -one}, {zero, one}, {two, one},   {zero, one},  {zero, -one}, {two, -one},  {zero, -one}, {-two, -one}, {zero, -one}};
        coordinates[5] = {{zero, -one}, {zero, one}, {two, one},   {two, -one},  {two, one},   {zero, one},  {zero, -one}, {-two, -one}, {-two, one},  {-two, -one},  {zero, -one}};
        coordinates[6] = {{zero, -one}, {zero, one}, {two, one},   {two, -one},  {two, one},   {zero, one},  {-two, one},  {two, -one},  {zero, -one}};
        coordinates[7] = {{zero, -one}, {two, -one}, {two, one},   {two, -one},  {zero, -one}, {-two, -one}, {zero, -one}};
        coordinates[8] = {{zero, -one}, {two, -one}, {two, one},   {zero, one},  {zero, -one}, {-two, -one}, {-two, one},  {zero, one},  {zero, -one}};
        coordinates[9] = {{zero, -one}, {two, -one}, {two, one},   {zero, one},  {zero, -one}, {-two, -one}, {-two, one},  {-two, -one}, {zero, -one}};
    };
} Numbers;

const int motor_1 = 1;
const int motor_10 = 10;
std::mutex num_mutex_;
bool printed = false;

// Constants
const double L = 5.0; // Length of the first link
const double d = 3.5; // Distance between motors
const double Pi = 3.141592653589793;

float rad2deg(float rad) {
    return rad * 180 / Pi;
}

float deg2rad(float deg) {
    return deg * Pi / 180;
}

std::vector<JointValue> tcp_to_joint_transform(const Coordinate& from, const Coordinate& to, const int& steps = 10) {
    std::vector<JointValue> trajectory(steps);

    for (int i = 0; i < steps; i++) {
        double a = i / static_cast<double>(steps - 1); // Interpolate linearly
        Coordinate i_point{
            from.x + a * (to.x - from.x),
            from.y + a * (to.y - from.y)};

            double dOffset = d/2;
            double frameOffsetY = 8;


            double theta = std::atan2(i_point.y, i_point.x + dOffset) + acos((pow(i_point.x + dOffset,2) + pow(i_point.y, 2)) / (2*L*sqrt(pow(i_point.x + dOffset,2) + pow(i_point.y, 2) )));
            double phi   = std::atan2(i_point.y, i_point.x - dOffset) - acos((pow(i_point.x - dOffset,2) + pow(i_point.y, 2)) / (2*L*sqrt(pow(i_point.x - dOffset,2) + pow(i_point.y, 2) )));
            trajectory[i] = JointValue(theta, phi);
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
          std::shared_ptr<drawer::srv::Draw::Response> response) {
        std::lock_guard<std::mutex> lock(num_mutex_);
        int num = num_;
        RCLCPP_INFO(this->get_logger(), "Incoming request to draw number: %d", num);

        // Ensure the number is valid
        if (Numbers.coordinates.find(num) == Numbers.coordinates.end()) {
            RCLCPP_ERROR(this->get_logger(), "Invalid number: %d", num);
            response->done = false;
            return;
        }

        // Generate the trajectory
        // std::vector<JointValue> trajectory = draw_number(Numbers.coordinates[num]);
        std::vector<JointValue> trajectory = {JointValue(0, 0), JointValue(deg2rad(20), deg2rad(20))};

        // Publish motor positions
        for (size_t i = 0; i < trajectory.size(); i++) {
            std::cout << rad2deg(trajectory[i].theta) << " " <<  rad2deg(trajectory[i].phi) << std::endl;
            //dynamixel_sdk_custom_interfaces::msg::SetPositionMultiple message;
            message.id_1 = motor_1;  // Motor ID for motor 1
            message.position_1 = static_cast<int>(trajectory[i].theta); // Convert to degrees

            message.id_2 = motor_10;  // Motor ID for motor 2
            message.position_2 = static_cast<int>(trajectory[i].phi); // Convert to degrees

            publisher_->publish(message);

            // Simulate delay for hardware actuation
            rclcpp::sleep_for(std::chrono::milliseconds(1000));
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
