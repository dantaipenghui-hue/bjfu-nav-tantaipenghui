cmake_minimum_required(VERSION 3.8)
project(rm_oop_demo)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(visualization_msgs REQUIRED)
find_package(rosidl_default_generators REQUIRED)

rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/GameStatus.msg"
  "msg/RobotStatus.msg"
  "msg/AmmoStatus.msg"
  "srv/SupplyHp.srv"
  DEPENDENCIES std_msgs
)

add_executable(chassis_node src/chassis_node.cpp)
target_include_directories(chassis_node PUBLIC include)
ament_target_dependencies(chassis_node
  rclcpp
  geometry_msgs
  nav_msgs
  tf2
  tf2_ros
  visualization_msgs
)

add_executable(referee_mock_node src/referee_mock_node.cpp)
target_include_directories(referee_mock_node PUBLIC include)
ament_target_dependencies(referee_mock_node
  rclcpp
  std_msgs
)
rosidl_get_typesupport_target(cpp_typesupport_target ${PROJECT_NAME} "rosidl_typesupport_cpp")
target_link_libraries(referee_mock_node "${cpp_typesupport_target}")

add_executable(keyboard_teleop_node src/keyboard_teleop_node.cpp)
target_include_directories(keyboard_teleop_node PUBLIC include)
ament_target_dependencies(keyboard_teleop_node
  rclcpp
  geometry_msgs
)

install(TARGETS
  chassis_node
  referee_mock_node
  keyboard_teleop_node
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY launch rviz
  DESTINATION share/${PROJECT_NAME}
)

ament_export_dependencies(rosidl_default_runtime)
ament_package()
