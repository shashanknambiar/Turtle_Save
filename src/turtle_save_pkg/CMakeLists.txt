cmake_minimum_required(VERSION 3.8)
project(turtle_save_pkg)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(turtlesim REQUIRED)
find_package(example_interfaces REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(turtlesim REQUIRED)
find_package(custom_interfaces REQUIRED)
find_package(std_msgs REQUIRED)

add_executable(turtlespawn_node src/turtlespawnnode.cpp)
ament_target_dependencies(turtlespawn_node rclcpp turtlesim example_interfaces custom_interfaces std_msgs)

add_executable(turtlecontrol_node src/turtlecontrolnode.cpp)
ament_target_dependencies(turtlecontrol_node rclcpp turtlesim geometry_msgs turtlesim custom_interfaces std_msgs)

install(TARGETS
  turtlespawn_node
  turtlecontrol_node
  DESTINATION lib/${PROJECT_NAME}
)


ament_package()
