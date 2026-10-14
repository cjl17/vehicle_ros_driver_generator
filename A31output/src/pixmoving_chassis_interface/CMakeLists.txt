cmake_minimum_required(VERSION 3.8)
project(pixmoving_chassis_interface)

# find dependencies
find_package(ament_cmake_auto REQUIRED)
ament_auto_find_build_dependencies()
find_package(rclcpp_components REQUIRED)
find_package(yaml-cpp REQUIRED)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
  set(CMAKE_CXX_EXTENSIONS OFF)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

ament_auto_add_library(${PROJECT_NAME} SHARED
  src/pixmoving_chassis_interface.cpp
  src/pixmoving_task.cpp
  src/pixmoving_autoware.cpp
  src/pixmoving_drive_mode.cpp              # 新增：状态机实现
  src/pixmoving_autoware_state_machine.cpp  # 新增：状态机集成
  src/pixmoving_chassis.cpp
  src/pixmoving_mileage.cpp
  src/pixmoving_sensor.cpp
  src/chassis_interface_common.cpp
  src/planning_metrics_monitor.cpp          # 新增：规划指标监控
)
target_link_libraries(${PROJECT_NAME} yaml-cpp)

rclcpp_components_register_node(${PROJECT_NAME}
  PLUGIN "pixmoving::chassis::interface::PixmovingChassisInterfaceNode"
  EXECUTABLE chassis_interface_node_component
)

ament_auto_add_executable(chassis_interface_node
  src/pixmoving_chassis_interface_node.cpp
)

target_link_libraries(chassis_interface_node
  ${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_cmake_gtest REQUIRED)

  ament_add_gtest(test_drive_mode_manager
    test/test_drive_mode_manager.cpp
  )

  ament_add_gtest(test_planning_metrics_monitor
    test/test_planning_metrics_monitor.cpp
  )

  if(TARGET test_drive_mode_manager)
    target_include_directories(test_drive_mode_manager PRIVATE include)
    target_link_libraries(test_drive_mode_manager ${PROJECT_NAME})
  endif()

  if(TARGET test_planning_metrics_monitor)
    target_include_directories(test_planning_metrics_monitor PRIVATE include)
    target_link_libraries(test_planning_metrics_monitor ${PROJECT_NAME})
  endif()
endif()

# install
ament_auto_package(
  INSTALL_TO_SHARE
  launch
  config
)
