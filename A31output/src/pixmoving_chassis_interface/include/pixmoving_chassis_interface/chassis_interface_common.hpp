#pragma once

#include "pixmoving_chassis_interface/chassis_interface_include.hpp"

namespace pixmoving
{
namespace chassis
{
namespace interface
{

/// @brief 车身驱动模式枚举，提供给前端 HMI 显示。
/// 数值由底层 CAN 协议定义，必须与后端/仪表保持一致。
enum class DriveMode : int8_t
{
  MANUAL_CONTROL = 1,         ///< 遥控/人工驾驶
  REMOTE_NETWORK = 2,         ///< 远程网络遥控
  EMERGENCY_STOP = 3,         ///< 紧急制动
  UNKNOWN = -1,               ///< 未知状态
  AUTO_STANDBY = 4,           ///< 自驾待命
  AUTO_EXECUTING = 5,         ///< 自驾执行中
  AUTO_TAKEOVER_MANUAL = 6,   ///< 人工接管
  AUTO_TAKEOVER_BRAKE = 7,    ///< 刹车接管
  AUTO_DONE_NORMAL = 8,       ///< 正常完成任务
  AUTO_DONE_NEAR = 9,         ///< 接近完成（即将到达）
  AUTO_CANCEL_TAKEOVER = 10,  ///< 接管导致任务取消
  AUTO_CANCEL_NEW_TASK = 11,  ///< 新任务导致旧任务取消
  AUTO_DONE_ESTOP_NEAR = 12   ///< 终点附近急停结束
};

/// @brief 站点匹配的临时结果，同时保存索引与名称。
struct TaskStationInfoTemp
{
  int8_t current_station_index = -1;
  int8_t target_station_index = -1;
  std::string current_station_name;
  std::string target_station_name;
};

// 阈值配置结构体
struct MetricsThresholds
{
  // 舒适性相关
  double jerk_uncomfortable_threshold = 1.0;  // 不舒适起步
  double accel_limit = 3.0;                   // 加速度极限值
  double comfort_jerk_clear_threshold = 0.8;  // 不舒适急动度恢复阈值
  double comfort_accel_clear_limit = 2.4;     // 不舒适加速度恢复阈值
  int comfort_bad_count_threshold = 3;        // 连续异常帧数达到后触发不舒适
  int comfort_good_count_threshold = 5;       // 连续正常帧数达到后恢复正常
  double comfort_min_event_duration_sec = 0.5;  // 不舒适事件最小持续时间

  // 危险事件相关
  double near_miss_trigger_accel = 3.0;  // 危险事件触发阈值
  double near_miss_clear_accel = 2.0;    // 危险事件消失阈值
  double imu_timeout_sec = 1.0;          // IMU 数据超时阈值

  // 稳定性相关
  double stability_mean_limit = 0.3;        // 整体偏差触发阈值
  double frechet_limit = 0.5;               // 形状畸变触发阈值
  double local_disp_limit = 0.15;           // 局部跳变触发阈值
  double lookahead_max_limit = 0.5;         // 前瞻最大跳变触发阈值
  double stability_mean_clear_limit = 0.24; // 整体偏差恢复阈值
  double frechet_clear_limit = 0.4;         // 形状畸变恢复阈值
  double local_disp_clear_limit = 0.12;     // 局部跳变恢复阈值
  double lookahead_max_clear_limit = 0.4;   // 前瞻最大跳变恢复阈值
  int stability_bad_count_threshold = 3;    // 连续异常帧数达到后触发突变
  int stability_good_count_threshold = 10;  // 连续正常帧数达到后恢复正常
  double stability_min_event_duration_sec = 0.5;  // 轨迹突变事件最小持续时间
  bool stability_require_autonomous_mode = true;  // 仅自驾模式下允许触发轨迹突变
  bool stability_suppress_when_stopped = true;    // 静止时抑制轨迹突变
  double stability_standstill_speed_threshold_mps = 0.2;  // 稳定性静止速度阈值
  bool stability_require_route_lane = true;  // 仅当前 ego lane 在有效 route 上时允许触发轨迹突变
  bool stability_require_auto_executing_mode = true;  // 仅 Pixmoving mode=5 时允许触发轨迹突变
  bool comfort_require_auto_executing_mode = true;  // 仅 Pixmoving mode=5 时允许触发舒适性异常
  bool comfort_suppress_on_brake_pedal = true;  // 人工刹车及释放冷却期间抑制舒适性异常
  double comfort_brake_release_suppression_sec = 10.0;  // 人工刹车释放后的抑制时长
};

/// @brief 与底盘接口相关的通用 topic 名称常量。
namespace topics
{
// Autoware / planning 相关
constexpr char PLANNING_GOAL[] = "/planning/mission_planning/goal";
constexpr char LOCALIZATION_POSE[] = "/localization/pose_twist_fusion_filter/pose";
constexpr char AUTOWARE_STATE[] = "/autoware/state";
constexpr char VELOCITY_LIMIT[] = "/planning/scenario_planning/current_max_velocity";
constexpr char PLANNING_ROUTE[] = "/planning/mission_planning/route";
constexpr char VEHICLE_VELOCITY_REPORT[] = "/vehicle/status/velocity_status";
constexpr char LOCAL_TRANSFORM_PROBABILITY[] = "/localization/pose_estimator/nearest_voxel_transformation_likelihood";
constexpr char EMERGENCY_STATE[] = "/api/autoware/get/emergency";
constexpr char OPERATION_MODE_STATE[] = "/system/operation_mode/state";
constexpr char CONTROL_MODE_REPORT[] = "/vehicle/status/control_mode";
constexpr char MISSION_REMAINING_DISTANCE_TIME[] = "/planning/mission_remaining_distance_time";

// 传感器相关
constexpr char GNSS_FIX[] = "/sensing/gnss/fix";
constexpr char GNSS_IMU[] = "/sensing/gnss/imu";
constexpr char GNSS_HEADING[] = "/sensing/gnss/heading";
constexpr char GNSS_MAIN_ANTENNA_SATELLITE_COUNT[] = "/sensing/gnss/chc/main_antenna_satellite_count";
constexpr char GNSS_AUX_ANTENNA_SATELLITE_COUNT[] = "/sensing/gnss/chc/auxiliary_antenna_satellite_count";

// Pix Robobus driver 相关
constexpr char BCM_MESSAGE4[] = "/pix_robobus/bcm_message4";
constexpr char BCM_MESSAGE5[] = "/pix_robobus/bcm_message5";
constexpr char VA_DRIVE_STA_FB[] = "/pix_robobus/va_drive_sta_fb";
constexpr char VA_BRAKE_STA_FB[] = "/pix_robobus/va_brake_sta_fb";
constexpr char VA_STEER_STA_FB[] = "/pix_robobus/va_steer_sta_fb";
constexpr char VA_VEHICLE_WORK_STA_FB[] = "/pix_robobus/va_vehicle_work_sta_fb";
constexpr char VA_POWER_STA_FB[] = "/pix_robobus/va_power_sta_fb";
constexpr char VA_VEHICLE_STA_FB[] = "/pix_robobus/va_vehicle_sta_fb";
constexpr char VA_CHASSIS_ODO_FB[] = "/pix_robobus/va_chassis_odo_fb";
constexpr char VA_CHASSIS_WHEEL_TIRE_PRESS_FB[] = "/pix_robobus/va_chassis_wheel_tire_press_fb";
constexpr char VIN_RESP1[] = "/pix_robobus/vin_resp1";
constexpr char VIN_RESP2[] = "/pix_robobus/vin_resp2";
constexpr char VIN_RESP3[] = "/pix_robobus/vin_resp3";
constexpr char VCU_TRANSFER[] = "/pix_robobus/vcu_transfer";
constexpr char VCU_SOFT_VER[] = "/pix_robobus/vcu_soft_ver";
constexpr char VEHICLE_ERRCODE1[] = "/pix_robobus/vehicle_errcode1";
constexpr char AEB_INFO_REPORT[] = "/pix/AebInfoReport";
constexpr char AEB_INFO_SHADOW[] = "/pix/AebInfoShadow";

}  // namespace topics

/// @brief 与底盘接口相关的 service 名称常量。
namespace services
{
constexpr char GET_PRIMITIVE_LENGTH[] = "/cloud_control_platform/get_lenght/from_lanelet";
constexpr char GET_ROUTE_STATIONS[] = "/cloud_control_platform/get_route_stations";
}  // namespace services

/// @brief Pixmoving chassis interface 发布的 topic 名称常量。
namespace pub_topics
{
constexpr char V2D_VEHICLE_INFO[] = "/app/display/vehicle_info";
constexpr char ALL_STATION_INFO[] = "/app/display/all_station_info";
constexpr char CURRENT_STATION_INFO[] = "/app/display/current_station_info";
constexpr char TASK_SEMANTIC_STATUS[] = "/app/display/debug/task_semantic_status";
constexpr char VEHICLE_STATUS[] = "/app/cloud_control_platform/vehicle_info";
constexpr char SENSOR_INFO[] = "/app/cloud_control_platform/sensor_info";
constexpr char AUTOWARE_STATE_INFO[] = "/app/cloud_control_platform/autoware_info";
constexpr char NEARBY_FINISH[] = "/app/cloud_control_platform/nearby_finish";
}  // namespace pub_topics

/// @brief 车身接口的通用工具函数。
class ChassisInterfaceUtils
{
public:
  /// @brief 计算两点三维欧氏距离。
  static float calculateDistance(const geometry_msgs::msg::Point& p1, const geometry_msgs::msg::Point& p2);

  /// @brief 将驱动模式代码转换为中文描述（HMI 显示用）。
  static std::string driveModeToString(int8_t mode);

  /// @brief 将 @ref DriveMode 转换为传输所需的 int8 值。
  static int8_t toInt8(DriveMode mode);

  /// @brief 从四元数提取偏航角（弧度，假设 ENU 坐标）。
  static double yawFromQuaternion(const geometry_msgs::msg::Quaternion& q);

  /// @brief 计算两偏航角的最小绝对差值（弧度，范围 0~pi，考虑环绕）。
  static double angleDifference(double yaw1, double yaw2);
};

}  // namespace interface
}  // namespace chassis
}  // namespace pixmoving
