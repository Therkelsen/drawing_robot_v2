cmake_minimum_required(VERSION 3.8)
project(nn_interface)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(OpenCV REQUIRED)
find_package(rclcpp REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)
#Create an executable for your node

add_executable(nn_analyzer src/nn_analyzer.cpp)
ament_target_dependencies(nn_analyzer rclcpp OpenCV rclcpp cv_bridge sensor_msgs)
target_link_libraries(nn_analyzer ${OpenCV_LIBS} ${cv_bridge_LIBRARIES})
target_sources(nn_analyzer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/drivers/nn_inference_v1_0/src/xnn_inference.c 
  ${CMAKE_CURRENT_SOURCE_DIR}/drivers/nn_inference_v1_0/src/xnn_inference_linux.c)
target_include_directories(nn_analyzer PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/drivers/nn_inference_v1_0/src
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # uncomment the line when a copyright and license is not present in all source files
  #set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # uncomment the line when this package is not in a git repo
  #set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

# Install your node executable
install(TARGETS
  nn_analyzer
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
