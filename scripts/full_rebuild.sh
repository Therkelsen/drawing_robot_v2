#!/bin/bash

clear

rm -rf build/ install/ log/

colcon build --packages-select usb_cam
colcon build --packages-select dynamixel_sdk
colcon build --packages-select dynamixel_sdk_custom_interfaces
colcon build --packages-select dynamixel_controller
colcon build --packages-select drawer
colcon build --packages-select nn_interface

. /opt/ros/foxy/setup.sh
. install/local_setup.sh