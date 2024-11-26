#include "rclcpp/rclcpp.hpp"
#include "drawer/srv/number.hpp"
#include "dynamixel_sdk_custom_interfaces/msg/set_position_multiple.hpp"
#include <map>
#include <vector>
#include <memory>
#include <unistd.h>

// For each number, we have an array of motor values [motor1, motor2]
std::map<int, std::vector<std::pair<int, int>>> mp;
const int motor_1 = 1;
const int motor_10 = 10;

void initialize_map()
{
    mp[0] = {{0, 0}, {200, 200}, {400, 400}, {800, 800}};
    mp[1] = {{1023, 1023}, {800, 800}, {600, 600}, {400, 400}};
    mp[2] = {{5, 5}, {10, 10}, {2, 4}, {7, 7}};
    mp[3] = {{5, 5}, {10, 10}, {2, 4}, {7, 7}};
    mp[4] = {{5, 5}, {10, 10}, {2, 4}, {7, 7}};
    mp[5] = {{5, 5}, {10, 10}, {2, 4}, {7, 7}};
    mp[6] = {{5, 5}, {10, 10}, {2, 4}, {7, 7}};
    mp[7] = {{5, 5}, {10, 10}, {2, 4}, {7, 7}};
    mp[8] = {{5, 5}, {10, 10}, {2, 4}, {7, 7}};
    mp[9] = {{5, 5}, {10, 10}, {2, 4}, {7, 7}};
}

class NumberDrawerNode : public rclcpp::Node
{
public:
    NumberDrawerNode() : Node("number_drawer")
    {
        // Initialize the map
        initialize_map();

        // Create the publisher
        publisher = this->create_publisher<dynamixel_sdk_custom_interfaces::msg::SetPositionMultiple>("/set_position", 1);

        // Create the service
        service_ = this->create_service<drawer::srv::Number>(
            "number", std::bind(&NumberDrawerNode::draw, this, std::placeholders::_1, std::placeholders::_2));

        RCLCPP_INFO(this->get_logger(), "Ready to draw a number.");
    }

private:
    void draw(const std::shared_ptr<drawer::srv::Number::Request> request,
              std::shared_ptr<drawer::srv::Number::Response> response)
    {
        RCLCPP_INFO(this->get_logger(), "Incoming request to draw number: %ld", request->num);

        int num = request->num;

        // Ensure the number is valid
        if (mp.find(num) == mp.end())
        {
            RCLCPP_ERROR(this->get_logger(), "Invalid number: %d", num);
            response->done = false;
            return;
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
            publisher->publish(message);
            
            // This is the shortest possible sleep. I assume the package transmission takes one second.
            sleep(1);
        }

        // Set the response
        response->done = true;
        RCLCPP_INFO(this->get_logger(), "Number %d drawn successfully.", num);
    }

    rclcpp::Publisher<dynamixel_sdk_custom_interfaces::msg::SetPositionMultiple>::SharedPtr publisher;
    rclcpp::Service<drawer::srv::Number>::SharedPtr service_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);

    auto node = std::make_shared<NumberDrawerNode>();
    rclcpp::spin(node);

    rclcpp::shutdown();
    return 0;
}
