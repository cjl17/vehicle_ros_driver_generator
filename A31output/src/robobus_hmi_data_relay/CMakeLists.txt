cmake_minimum_required(VERSION 3.8)
project(robobus_hmi_data_relay)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake_auto REQUIRED)
ament_auto_find_build_dependencies()
find_package(rclcpp_components REQUIRED)
find_package(yaml-cpp REQUIRED)

ament_auto_add_library(${PROJECT_NAME} SHARED
  src/robobus_hmi_data_relay_node.cpp
  src/bridges/diagnostic_alarm_bridge_module.cpp
  src/bridges/relay_autoware_transfer_module.cpp
  src/bridges/pixmoving_vehicle_display_bridge_module.cpp
  src/monitors/blind_spot_monitor_module.cpp
  src/monitors/health_monitor_module.cpp
  src/publishers/git_version_publisher_module.cpp
)
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
target_link_libraries(${PROJECT_NAME} yaml-cpp)

rclcpp_components_register_node(${PROJECT_NAME}
  PLUGIN "robobus_hmi_data_relay::RobobusHmiDataRelayNode"
  EXECUTABLE robobus_hmi_data_relay_node
)

ament_auto_package(
  INSTALL_TO_SHARE
  launch
  config
)
