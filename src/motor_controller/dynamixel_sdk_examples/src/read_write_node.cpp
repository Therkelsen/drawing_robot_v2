// Copyright 2021 ROBOTIS CO., LTD.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/*******************************************************************************
// This example is written for DYNAMIXEL X(excluding XL-320) and MX(2.0) series with U2D2.
// For other series, please refer to the product eManual and modify the Control Table addresses and other definitions.
// To test this example, please follow the commands below.
//
// Open terminal #1
// $ ros2 launch dynamixel_sdk_examples motor_controller.launch.py
//
// Open terminal #2 (run one of below commands at a time)
// $ ros2 topic pub -1 motor_<id>/set_position dynamixel_sdk_custom_interfaces/SetPosition "{id: <id>, position: <position>}"
// $ ros2 service call /get_position dynamixel_sdk_custom_interfaces/srv/GetPosition "id: <id>"
//
// Author: Will Son
*******************************************************************************/

// https://github.com/ROBOTIS-GIT/DynamixelSDK/blob/master/c%2B%2B/example/protocol2.0/sync_read_write/sync_read_write.cpp
// https://www.generationrobots.com/media/Dynamixel-AX-12-user-manual.pdf page 24

#include <cstdio>
#include <memory>
#include <string>

#include "dynamixel_sdk/dynamixel_sdk.h"
#include "dynamixel_sdk_custom_interfaces/msg/set_position_multiple.hpp"
#include "dynamixel_sdk_custom_interfaces/msg/set_position.hpp"
#include "dynamixel_sdk_custom_interfaces/srv/get_position.hpp"
#include "rclcpp/rclcpp.hpp"
#include "rcutils/cmdline_parser.h"

#include "read_write_node.hpp"

// Control table address for X series (except XL-320)
#define ADDR_OPERATING_MODE 8
#define ADDR_TORQUE_ENABLE 24
#define ADDR_GOAL_POSITION 30
#define ADDR_PRESENT_POSITION 36

// Protocol version
#define PROTOCOL_VERSION 1.0  // Default Protocol version of DYNAMIXEL X series.

// Default setting
#define BAUDRATE 1000000  // Default Baudrate of DYNAMIXEL X series
#define DEVICE_NAME "/dev/ttyACM0"  // [Linux]: "/dev/ttyUSB*", [Windows]: "COM*"

dynamixel::PortHandler * portHandler;
dynamixel::PacketHandler * packetHandler;

uint8_t dxl_error = 0;
uint32_t goal_position = 0;
int dxl_comm_result = COMM_TX_FAIL;

rclcpp::Subscription<dynamixel_sdk_custom_interfaces::msg::SetPositionMultiple>::SharedPtr set_position_multiple_subscriber_;

ReadWriteNode::ReadWriteNode()
: Node("read_write_node")
{
  RCLCPP_INFO(this->get_logger(), "Run read write node");

  this->declare_parameter<std::string>("topic_name", "set_position");
  std::string topic_name;
  this->get_parameter("topic_name", topic_name);

  this->declare_parameter<std::string>("multi_driver", "set_position");
  std::string multi_driver;
  this->get_parameter("multi_driver", multi_driver);

  RCLCPP_INFO(this->get_logger(), "Subscribing to topic: %s", multi_driver.c_str());

  int8_t qos_depth = 0;
  this->get_parameter("qos_depth", qos_depth);

  const auto QOS_RKL10V =
    rclcpp::QoS(rclcpp::KeepLast(qos_depth)).reliable().durability_volatile();

  // Updated subscriber implementation
  set_position_multiple_subscriber_ = this->create_subscription<dynamixel_sdk_custom_interfaces::msg::SetPositionMultiple>(
    topic_name,
    QOS_RKL10V,
    [this](const dynamixel_sdk_custom_interfaces::msg::SetPositionMultiple::SharedPtr msg) -> void {
      // Prepare SYNC WRITE parameters
      std::vector<uint8_t> param_data;

      // Motor 1: Add ID and position to param_data
      param_data.push_back(msg->id_1);
      param_data.push_back(DXL_LOBYTE(DXL_LOWORD(msg->position_1)));
      param_data.push_back(DXL_HIBYTE(DXL_LOWORD(msg->position_1)));
      param_data.push_back(DXL_LOBYTE(DXL_HIWORD(msg->position_1)));
      param_data.push_back(DXL_HIBYTE(DXL_HIWORD(msg->position_1)));

      // Motor 2: Add ID and position to param_data
      param_data.push_back(msg->id_2);
      param_data.push_back(DXL_LOBYTE(DXL_LOWORD(msg->position_2)));
      param_data.push_back(DXL_HIBYTE(DXL_LOWORD(msg->position_2)));
      param_data.push_back(DXL_LOBYTE(DXL_HIWORD(msg->position_2)));
      param_data.push_back(DXL_HIBYTE(DXL_HIWORD(msg->position_2)));

      // Execute SYNC WRITE
      dxl_comm_result = packetHandler->syncWriteTxOnly(
          portHandler,
          ADDR_GOAL_POSITION,  // Starting address of Goal Position
          4,                   // Length of Goal Position data per motor
          param_data.data(),   // SYNC WRITE data
          param_data.size()    // Size of the data
      );

      // Handle communication result
      if (dxl_comm_result != COMM_SUCCESS) {
        RCLCPP_ERROR(this->get_logger(), "SYNC WRITE failed: %s", packetHandler->getTxRxResult(dxl_comm_result));
      } else {
        RCLCPP_INFO(
            this->get_logger(),
            "SYNC WRITE successful: [ID 1: %d, Position 1: %d] [ID 2: %d, Position 2: %d]",
            msg->id_1, msg->position_1, msg->id_2, msg->position_2
        );
      }
    }
);

  auto get_present_position =
    [this](
    const std::shared_ptr<GetPosition::Request> request,
    std::shared_ptr<GetPosition::Response> response) -> void
    {
      // Read Present Position (length : 4 bytes) and Convert uint32 -> int32
      // When reading 2 byte data from AX / MX(1.0), use read2ByteTxRx() instead.
      dxl_comm_result = packetHandler->read4ByteTxRx(
        portHandler,
        (uint8_t) request->id,
        ADDR_PRESENT_POSITION,
        reinterpret_cast<uint32_t *>(&present_position),
        &dxl_error
      );

      RCLCPP_INFO(
        this->get_logger(),
        "Get [ID: %d] [Present Position: %d]",
        request->id,
        present_position
      );

      response->position = present_position;
    };

  get_position_server_ = create_service<GetPosition>("get_position", get_present_position);
}

ReadWriteNode::~ReadWriteNode()
{
}

void setupDynamixel(uint8_t dxl_id)
{
  // Use Position Control Mode
  dxl_comm_result = packetHandler->write1ByteTxRx(
    portHandler,
    dxl_id,
    ADDR_OPERATING_MODE,
    3,
    &dxl_error
  );

  if (dxl_comm_result != COMM_SUCCESS) {
    RCLCPP_ERROR(rclcpp::get_logger("read_write_node"), "Failed to set Position Control Mode.");
  } else {
    RCLCPP_INFO(rclcpp::get_logger("read_write_node"), "Succeeded to set Position Control Mode.");
  }

  // Enable Torque of DYNAMIXEL
  dxl_comm_result = packetHandler->write1ByteTxRx(
    portHandler,
    dxl_id,
    ADDR_TORQUE_ENABLE,
    1,
    &dxl_error
  );

  if (dxl_comm_result != COMM_SUCCESS) {
    RCLCPP_ERROR(rclcpp::get_logger("read_write_node"), "Failed to enable torque.");
  } else {
    RCLCPP_INFO(rclcpp::get_logger("read_write_node"), "Succeeded to enable torque.");
  }
}

int main(int argc, char * argv[])
{
  portHandler = dynamixel::PortHandler::getPortHandler(DEVICE_NAME);
  packetHandler = dynamixel::PacketHandler::getPacketHandler(PROTOCOL_VERSION);

  // Open Serial Port
  dxl_comm_result = portHandler->openPort();
  if (dxl_comm_result == false) {
    RCLCPP_ERROR(rclcpp::get_logger("read_write_node"), "Failed to open the port!");
    return -1;
  } else {
    RCLCPP_INFO(rclcpp::get_logger("read_write_node"), "Succeeded to open the port.");
  }

  // Set the baudrate of the serial port (use DYNAMIXEL Baudrate)
  dxl_comm_result = portHandler->setBaudRate(BAUDRATE);
  if (dxl_comm_result == false) {
    RCLCPP_ERROR(rclcpp::get_logger("read_write_node"), "Failed to set the baudrate!");
    return -1;
  } else {
    RCLCPP_INFO(rclcpp::get_logger("read_write_node"), "Succeeded to set the baudrate.");
  }

  setupDynamixel(BROADCAST_ID);

  rclcpp::init(argc, argv);

  auto readwritenode = std::make_shared<ReadWriteNode>();
  rclcpp::spin(readwritenode);
  rclcpp::shutdown();

  // Disable Torque of DYNAMIXEL
  packetHandler->write1ByteTxRx(
    portHandler,
    BROADCAST_ID,
    ADDR_TORQUE_ENABLE,
    0,
    &dxl_error
  );

  return 0;
}
