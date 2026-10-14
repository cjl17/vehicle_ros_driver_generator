cmake_minimum_required(VERSION 3.5)
project(pix_robobus_driver)

find_package(ament_cmake_auto REQUIRED)
ament_auto_find_build_dependencies()

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
  set(CMAKE_CXX_EXTENSIONS OFF)
endif()
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

ament_auto_add_library(${PROJECT_NAME}_control_command SHARED
	src/libs/av_aeb_ctrl.cc
	src/libs/av_drive_ctrl.cc
	src/libs/av_brake_ctrl.cc
	src/libs/av_steer_ctrl.cc
	src/libs/av_vehicle_ctrl.cc
	src/libs/av_wheel_torque_ctrl.cc
	src/libs/av_manual_spd_limit.cc
	src/libs/av_self_driving_work_st.cc
	src/libs/auto_message.cc
	src/libs/remote_message.cc
	src/libs/acu_sys_time.cc
	src/libs/av_message1.cc
	src/libs/av_message2.cc

  src/libs/Byte.cc
  src/control_command.cpp
)

rclcpp_components_register_node(${PROJECT_NAME}_control_command
  PLUGIN "pix_robobus_driver::control_command::ControlCommand"
  EXECUTABLE ${PROJECT_NAME}_control_command_node
)

ament_auto_add_library(${PROJECT_NAME}_report_parser SHARED
	src/libs/vcu_soft_ver.cc
	src/libs/ac_message1.cc
	src/libs/ac_message2.cc
	src/libs/vin_resp1.cc
	src/libs/vin_resp2.cc
	src/libs/vin_resp3.cc
	src/libs/vehicle_errcode1.cc
	src/libs/vehicle_errcode2.cc
	src/libs/historical_vehiclefailures1.cc
	src/libs/historical_vehiclefailures2.cc
	src/libs/va_drive_sta_fb.cc
	src/libs/va_brake_sta_fb.cc
	src/libs/va_steer_sta_fb.cc
	src/libs/va_vehicle_work_sta_fb.cc
	src/libs/va_power_sta_fb.cc
	src/libs/va_vehicle_sta_fb.cc
	src/libs/va_vehicle_flt_sta.cc
	src/libs/va_chassis_wheel_rpm_fb.cc
	src/libs/va_chassis_odo_fb.cc
	src/libs/vcu_transfer.cc
	src/libs/va_chassis_wheel_tire_press_fb.cc
	src/libs/va_chassis_wheel_angle_fb.cc
	src/libs/va_chassis_wheel_torque_fb.cc
	src/libs/bcm_message4.cc
	src/libs/bcm_message5.cc
	src/libs/dp_messgae4.cc
	src/libs/dp_messgae5.cc

  src/libs/Byte.cc
  src/report_parser.cpp
)

rclcpp_components_register_node(${PROJECT_NAME}_report_parser
  PLUGIN "pix_robobus_driver::report_parser::ReportParser"
  EXECUTABLE ${PROJECT_NAME}_report_parser_node
)

# install
ament_auto_package(
  INSTALL_TO_SHARE
  launch
  # config
)