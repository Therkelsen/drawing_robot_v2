cmake_minimum_required(VERSION 3.8)
project(drawer)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(dynamixel_sdk_custom_interfaces REQUIRED)
find_package(sensor_msgs REQUIRED)


# Specify the .srv file
rosidl_generate_interfaces(${PROJECT_NAME}
  "srv/Draw.srv"
  "msg/Num.msg" DEPENDENCIES std_msgs
)

#Create an executable for your node
add_executable(number_drawer src/number_drawer.cpp)
ament_target_dependencies(number_drawer rclcpp dynamixel_sdk_custom_interfaces sensor_msgs)
rosidl_target_interfaces(number_drawer ${PROJECT_NAME} "rosidl_typesupport_cpp")

# Install your node executable
install(TARGETS
  number_drawer
  DESTINATION lib/${PROJECT_NAME}
)

# Export package dependencies
ament_package()
