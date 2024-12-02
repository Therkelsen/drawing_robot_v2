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
#include <cmath>
#include <eigen3/Eigen/Dense>

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
        double offset_x = 1;  // Horizontal offset to avoid overlap along x-axis
        double offset_y = 1;  // Vertical offset to avoid singularity

        coordinates[0] = {{0 + offset_x, 0 + offset_y}, {5 + offset_x, 0 + offset_y}, {5 + offset_x, 5 + offset_y}, {5 + offset_x, 10 + offset_y}, {0 + offset_x, 10 + offset_y}, {0 + offset_x, 5 + offset_y}, {0 + offset_x, 0 + offset_y}};
        coordinates[1] = {{0 + offset_x, 0 + offset_y}, {0 + offset_x, 5 + offset_y}, {0 + offset_x, 10 + offset_y}, {0 + offset_x, 5 + offset_y},  {0 + offset_x, 0 + offset_y}};
        coordinates[2] = {{0 + offset_x, 0 + offset_y}, {5 + offset_x, 0 + offset_y}, {5 + offset_x, 5 + offset_y},  {0 + offset_x, 5 + offset_y},  {0 + offset_x, 10 + offset_y}, {5 + offset_x, 10 + offset_y}, {0 + offset_x, 10 + offset_y}, {0 + offset_x, 5 + offset_y},  {5 + offset_x, 5 + offset_y},  {5 + offset_x, 0 + offset_y},  {0 + offset_x, 0 + offset_y}};
        coordinates[3] = {{0 + offset_x, 0 + offset_y}, {5 + offset_x, 0 + offset_y}, {0 + offset_x, 0 + offset_y},  {0 + offset_x, 5 + offset_y},  {5 + offset_x, 5 + offset_y},  {0 + offset_x, 5 + offset_y},  {0 + offset_x, 10 + offset_y}, {5 + offset_x, 10 + offset_y}, {0 + offset_x, 10 + offset_y}, {0 + offset_x, 5 + offset_y},  {0 + offset_x, 0 + offset_y}};
        coordinates[4] = {{0 + offset_x, 0 + offset_y}, {0 + offset_x, 5 + offset_y}, {0 + offset_x, 10 + offset_y}, {0 + offset_x, 5 + offset_y},  {5 + offset_x, 5 + offset_y},  {5 + offset_x, 10 + offset_y}, {5 + offset_x, 5 + offset_y},  {0 + offset_x, 5 + offset_y},  {0 + offset_x, 0 + offset_y}};
        coordinates[5] = {{0 + offset_x, 0 + offset_y}, {5 + offset_x, 0 + offset_y}, {0 + offset_x, 0 + offset_y},  {0 + offset_x, 5 + offset_y},  {5 + offset_x, 5 + offset_y},  {5 + offset_x, 10 + offset_y}, {0 + offset_x, 10 + offset_y}, {5 + offset_x, 10 + offset_y}, {5 + offset_x, 5 + offset_y},  {0 + offset_x, 5 + offset_y},  {0 + offset_x, 0 + offset_y}};
        coordinates[6] = {{0 + offset_x, 0 + offset_y}, {0 + offset_x, 5 + offset_y}, {0 + offset_x, 0 + offset_y},  {5 + offset_x, 0 + offset_y},  {5 + offset_x, 5 + offset_y},  {0 + offset_x, 5 + offset_y},  {5 + offset_x, 5 + offset_y},  {5 + offset_x, 10 + offset_y}, {0 + offset_x, 10 + offset_y}, {5 + offset_x, 10 + offset_y}, {5 + offset_x, 5 + offset_y}, {5 + offset_x, 0 + offset_y}, {0 + offset_x, 0 + offset_y}};
        coordinates[7] = {{0 + offset_x, 0 + offset_y}, {0 + offset_x, 5 + offset_y}, {0 + offset_x, 10 + offset_y}, {5 + offset_x, 10 + offset_y}, {0 + offset_x, 10 + offset_y}, {0 + offset_x, 5 + offset_y},  {0 + offset_x, 0 + offset_y}};
        coordinates[8] = {{0 + offset_x, 0 + offset_y}, {5 + offset_x, 0 + offset_y}, {5 + offset_x, 5 + offset_y},  {0 + offset_x, 5 + offset_y},  {0 + offset_x, 10 + offset_y}, {5 + offset_x, 10 + offset_y}, {5 + offset_x, 5 + offset_y},  {0 + offset_x, 5 + offset_y},  {0 + offset_x, 0 + offset_y}};
        coordinates[9] = {{0 + offset_x, 0 + offset_y}, {0 + offset_x, 5 + offset_y}, {0 + offset_x, 10 + offset_y}, {5 + offset_x, 10 + offset_y}, {5 + offset_x, 5 + offset_y},  {0 + offset_x, 5 + offset_y},  {0 + offset_x, 0 + offset_y}};
    };
} Numbers;

const int motor_1 = 1;
const int motor_10 = 10;
std::mutex num_mutex_;

// Constants
const double L = 3.0; // Length of the first link
const double d = 3.0; // Distance between motors
const double Pi = 3.141592653589793;

// Function to calculate the system of equations
Eigen::Vector2d equations(const Eigen::Vector2d& vars, const Coordinate& P) {
    double theta = vars(0);  // Angle of Motor 1
    double phi = vars(1);    // Angle of Motor 2

    // Elbow positions
    Coordinate E_1{-d / 2.0 + static_cast<double>(L) * cos(theta), static_cast<double>(L) * sin(theta)};
    Coordinate E_2{d / 2.0 + static_cast<double>(L) * cos(phi), static_cast<double>(L) * sin(phi)};

    Eigen::Vector2d eqs;
    eqs(0) = pow(P.x - E_1.x, 2) + pow(P.y - E_1.y, 2) - pow(static_cast<double>(L), 2);  // Motor 1 equation
    eqs(1) = pow(P.x - E_2.x, 2) + pow(P.y - E_2.y, 2) - pow(static_cast<double>(L), 2);  // Motor 2 equation

    return eqs;
}

// Function to calculate the Jacobian matrix
Eigen::Matrix2d jacobian(const Eigen::Vector2d& vars, const Coordinate& P) {
    double theta = vars(0);
    double phi = vars(1);

    // Elbow positions
    Coordinate E_1{-d / 2.0 + static_cast<double>(L) * cos(theta), static_cast<double>(L) * sin(theta)};
    Coordinate E_2{d / 2.0 + static_cast<double>(L) * cos(phi), static_cast<double>(L) * sin(phi)};

    Eigen::Matrix2d J;

    // Partial derivatives for the first equation (Motor 1)
    J(0, 0) = -2.0 * (P.x - E_1.x) * static_cast<double>(L) * sin(theta) + 2.0 * (P.y - E_1.y) * static_cast<double>(L) * cos(theta);  // d(eq1)/d(theta)
    J(0, 1) = 0.0;  // No dependence of eq1 on phi

    // Partial derivatives for the second equation (Motor 2)
    J(1, 0) = 0.0;  // No dependence of eq2 on theta
    J(1, 1) = -2.0 * (P.x - E_2.x) * static_cast<double>(L) * sin(phi) + 2.0 * (P.y - E_2.y) * static_cast<double>(L) * cos(phi);  // d(eq2)/d(phi)

    return J;
}

// Newton-Raphson Solver
Eigen::Vector2d solveInverseKinematics(const Coordinate& P, const JointValue& initial_guess) {
    // Initial guess for the motor angles
    Eigen::Vector2d vars = Eigen::Vector2d(initial_guess.theta, initial_guess.phi);

    // Iterative solver parameters
    const int max_iterations = 100;
    const double tolerance = 1e-2;  // Increased tolerance for easier convergence
    const double damping_factor = 0.1;  // Small damping factor for stability

    // Check if the point is reachable
    double distance = sqrt(P.x * P.x + P.y * P.y);
    if (distance > 2 * L) {
        throw std::runtime_error("Target point is out of reach.");
    }

    std::cout << "tolerance: " << tolerance << std::endl;
    for (int i = 0; i < max_iterations; ++i) {
        Eigen::Vector2d f = equations(vars, P);
        Eigen::Matrix2d J = jacobian(vars, P);

        // Damping for numerical stability
        Eigen::Vector2d delta = J.colPivHouseholderQr().solve(-f);
        delta *= (1.0 + damping_factor);

        vars += delta;

        // Check for convergence
        std::cout << "vars: " << vars[0] << " " << vars[1] << std::endl;
        std::cout << "delta norm: " << delta.norm() << std::endl;
        std::cout << "iterations: " << i << std::endl;
        if (delta.norm() < tolerance) {
            std::cout << "Converged after " << i + 1 << " iterations." << std::endl;
            return vars;
        }
    }

    throw std::runtime_error("Newton-Raphson did not converge.");
}

std::vector<JointValue> tcp_to_joint_transform(const Coordinate& from, const Coordinate& to, const int& steps = 10) {
    std::vector<JointValue> trajectory(steps);

    JointValue initial_guess{Pi / 4, Pi / 4};  // Initial guess for the first point

    for (int i = 0; i < steps; i++) {
        double a = i / static_cast<double>(steps - 1); // Interpolate linearly
        Coordinate interpolated_point{
            from.x + a * (to.x - from.x),
            from.y + a * (to.y - from.y)};

        try {
            Eigen::Vector2d angles = solveInverseKinematics(interpolated_point, initial_guess);
            initial_guess = JointValue{angles(0), angles(1)};  // Update the initial guess
            trajectory[i] = initial_guess;
        } catch (const std::runtime_error& e) {
            std::cerr << "IK failed at point (" << interpolated_point.x << ", " << interpolated_point.y << "): " << e.what() << std::endl;
            // Handle failure (e.g., skip the point, use a fallback solution, or halt execution)
            trajectory[i] = initial_guess;  // Retain the last valid configuration
        }
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
        std::vector<JointValue> trajectory = draw_number(Numbers.coordinates[num]);

        // Publish motor positions
        for (size_t i = 0; i < trajectory.size(); i++) {
            dynamixel_sdk_custom_interfaces::msg::SetPositionMultiple message;
            message.id_1 = motor_1;  // Motor ID for motor 1
            message.position_1 = static_cast<int>(trajectory[i].theta * 180 / Pi); // Convert to degrees

            message.id_2 = motor_10;  // Motor ID for motor 2
            message.position_2 = static_cast<int>(trajectory[i].phi * 180 / Pi); // Convert to degrees

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
