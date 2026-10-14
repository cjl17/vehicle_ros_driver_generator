#pragma once

#include <rclcpp/rclcpp.hpp>

#include "sensor_msgs/msg/nav_sat_fix.hpp"
#include "std_msgs/msg/float32.hpp"
#include "std_msgs/msg/u_int8.hpp"
#include "tier4_debug_msgs/msg/float32_stamped.hpp"
#include "autoware_internal_debug_msgs/msg/float32_stamped.hpp"
#include <autoware_adapi_v1_msgs/msg/operation_mode_state.hpp>
#include <autoware_system_msgs/msg/autoware_state.hpp>
#include <autoware_vehicle_msgs/msg/control_mode_report.hpp>
#include <autoware_vehicle_msgs/msg/velocity_report.hpp>
#include <autoware_planning_msgs/msg/lanelet_route.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <get_osm_info_msgs/srv/get_primitive_length.hpp>
#include <get_osm_info_msgs/srv/get_route_stations.hpp>
#include <pixmoving_hmi_msgs/msg/autoware_info.hpp>
#include <pixmoving_hmi_msgs/msg/sensor_info.hpp>
#include <pixmoving_hmi_msgs/msg/v2d_all_station_info.hpp>
#include <pixmoving_hmi_msgs/msg/v2d_current_station_info.hpp>
#include <pixmoving_hmi_msgs/msg/task_semantic_status.hpp>
#include <pixmoving_hmi_msgs/msg/v2d_vehicle_info.hpp>
#include <pixmoving_hmi_msgs/msg/vehicle_info.hpp>
#include <tier4_external_api_msgs/msg/emergency.hpp>
#include <autoware_internal_planning_msgs/msg/velocity_limit.hpp>
#include <autoware_internal_msgs/msg/mission_remaining_distance_time.hpp>

#include <yaml-cpp/yaml.h>

#include <array>
#include <cstdint>
#include <future>
#include <mutex>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

// pix_robobus_driver_msgs
#include "pix_robobus_driver_msgs/msg/bcm_message4.hpp"
#include "pix_robobus_driver_msgs/msg/bcm_message5.hpp"
#include "pix_robobus_driver_msgs/msg/va_brake_sta_fb.hpp"
#include "pix_robobus_driver_msgs/msg/va_chassis_odo_fb.hpp"
#include "pix_robobus_driver_msgs/msg/va_chassis_wheel_tire_press_fb.hpp"
#include "pix_robobus_driver_msgs/msg/va_drive_sta_fb.hpp"
#include "pix_robobus_driver_msgs/msg/va_power_sta_fb.hpp"
#include "pix_robobus_driver_msgs/msg/va_steer_sta_fb.hpp"
#include "pix_robobus_driver_msgs/msg/vcu_soft_ver.hpp"
#include "pix_robobus_driver_msgs/msg/va_vehicle_sta_fb.hpp"
#include "pix_robobus_driver_msgs/msg/va_vehicle_work_sta_fb.hpp"
#include "pix_robobus_driver_msgs/msg/vcu_transfer.hpp"
#include "pix_robobus_driver_msgs/msg/vehicle_errcode1.hpp"
#include "pix_robobus_driver_msgs/msg/vin_resp1.hpp"
#include "pix_robobus_driver_msgs/msg/vin_resp2.hpp"
#include "pix_robobus_driver_msgs/msg/vin_resp3.hpp"
#include "aeb_interfaces/msg/aeb_info_report.hpp"
#include "aeb_interfaces/msg/aeb_info_shadow.hpp"
