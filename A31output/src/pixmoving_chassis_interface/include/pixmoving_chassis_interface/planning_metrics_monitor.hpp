#pragma once

#include <autoware_adapi_v1_msgs/msg/operation_mode_state.hpp>
#include <autoware_planning_msgs/msg/lanelet_route.hpp>
#include <autoware_vehicle_msgs/msg/velocity_report.hpp>
#include <pix_robobus_driver_msgs/msg/va_brake_sta_fb.hpp>
#include <sensor_msgs/msg/imu.hpp>
#include <rclcpp/rclcpp.hpp>
#include <tier4_metric_msgs/msg/metric_array.hpp>
#include <pixmoving_hmi_msgs/msg/planning_metrics.hpp>
#include <pixmoving_hmi_msgs/msg/vehicle_info.hpp>
#include "pixmoving_chassis_interface/chassis_interface_common.hpp"
#include <cstdint>
#include <string>
#include <map>
#include <unordered_set>

namespace pixmoving
{
namespace chassis
{
namespace interface
{

/// @brief 规划评估指标数据结构
struct PlanningMetrics
{
  // 舒适性相关指标
  double jerk_mean = 0.0;          // 平均急动度
  double jerk_min = 0.0;           // 最小急动度
  double jerk_max = 0.0;           // 最大急动度

  double acceleration_mean = 0.0;  // 平均加速度
  double acceleration_min = 0.0;   // 最小加速度
  double acceleration_max = 0.0;   // 最大加速度

  double velocity_mean = 0.0;      // 平均速度

  // 轨迹突变/稳定性相关指标
  double stability_mean = 0.0;                       // 平均轨迹稳定性（横向偏差）
  double stability_min = 0.0;                        // 最小轨迹稳定性
  double stability_max = 0.0;                        // 最大轨迹稳定性

  double stability_frechet_mean = 0.0;               // Frechet距离（轨迹相似度）

  double lateral_displacement_local = 0.0;           // 局部横向位移
  double lateral_displacement_lookahead_mean = 0.0;  // 前瞻横向位移平均值
  double lateral_displacement_lookahead_max = 0.0;   // 前瞻横向位移最大值

  // 当前运动状态
  double kinematic_velocity = 0.0;      // 当前速度
  double kinematic_acceleration = 0.0;  // 当前加速度
  double kinematic_jerk = 0.0;          // 当前急动度

  // 时间戳
  rclcpp::Time timestamp;

  // 数据有效性标志
  bool has_comfort_data = false;
  bool has_stability_data = false;
};

/// @brief 规划指标监控类
class PlanningMetricsMonitor
{
public:
  /// @brief 构造函数
  /// @param node ROS2 节点指针
  explicit PlanningMetricsMonitor(rclcpp::Node* node);

  /// @brief 析构函数
  ~PlanningMetricsMonitor() = default;

  /// @brief 获取最新的规划指标数据
  /// @return 规划指标结构体
  PlanningMetrics getLatestMetrics() const;

  /// @brief 检查数据是否有效（最近是否收到数据）
  /// @param timeout_sec 超时时间（秒）
  /// @return 数据是否有效
  bool isDataValid(double timeout_sec = 1.0) const;

  /// @brief 设置阈值
  /// @param thresholds 阈值结构体
  void setThresholds(const MetricsThresholds& thresholds);

private:
  /// @brief 规划指标回调函数
  /// @param msg MetricArray 消息
  void metricsCallback(const tier4_metric_msgs::msg::MetricArray::SharedPtr msg);

  /// @brief IMU 回调函数，用于维护危险事件状态
  /// @param msg IMU 消息
  void imuCallback(const sensor_msgs::msg::Imu::SharedPtr msg);

  /// @brief 自驾模式状态回调，用于控制稳定性事件触发条件
  void operationModeCallback(const autoware_adapi_v1_msgs::msg::OperationModeState::SharedPtr msg);

  /// @brief 车速回调，用于静止时抑制稳定性事件
  void velocityCallback(const autoware_vehicle_msgs::msg::VelocityReport::SharedPtr msg);

  /// @brief 路线回调，用于判断 ego lane 是否在有效 route 上
  void routeCallback(const autoware_planning_msgs::msg::LaneletRoute::SharedPtr msg);

  /// @brief Pixmoving 车辆信息回调，用于按业务驾驶模式门控规划事件
  void vehicleInfoCallback(const pixmoving_hmi_msgs::msg::VehicleInfo::SharedPtr msg);

  /// @brief 底盘刹车反馈回调，用于抑制人工刹车引起的舒适性事件
  void brakeStatusCallback(const pix_robobus_driver_msgs::msg::VaBrakeStaFb::SharedPtr msg);

  /// @brief 从 MetricArray 中提取指定指标的统计值
  /// @param metric_array 指标数组
  /// @param metric_name 指标名称
  /// @param stat_name 统计名称（mean/min/max）
  /// @param value 输出值
  /// @return 是否成功提取
  bool extractMetricValue(const std::vector<tier4_metric_msgs::msg::Metric>& metric_array,
                          const std::string& metric_name, double& value);

  /// @brief 从 MetricArray 中提取 lanelet id
  bool extractMetricValue(const std::vector<tier4_metric_msgs::msg::Metric>& metric_array,
                          const std::string& metric_name, std::int64_t& value);

  /// @brief 打印舒适性指标
  void printComfortMetrics();

  /// @brief 打印轨迹稳定性指标
  void printStabilityMetrics();

  /// @brief 根据当前缓存组包并发布
  /// @param stamp 输出消息时间戳
  void publishPlanningMetrics(const rclcpp::Time& stamp);

  /// @brief 根据 IMU 纵向加速度幅值更新危险事件状态
  /// @param longitudinal_accel_abs abs(ax)
  /// @param az_anomaly abs(az) 是否超过颠簸抑制阈值
  /// @param had_recent_imu_data 更新前是否已有未超时 IMU 状态
  void updateNearMissState(double longitudinal_accel_abs, bool az_anomaly, bool had_recent_imu_data);

  /// @brief 使用触发/恢复阈值和连续帧计数更新稳定性状态
  std::uint8_t updateStabilityState();

  /// @brief 使用触发/恢复阈值和连续帧计数更新舒适性状态
  std::uint8_t updateComfortState();

  /// @brief 当前是否允许稳定性事件触发
  bool isStabilityEvaluationEnabled() const;

  /// @brief 当前是否允许舒适性事件触发
  bool isComfortEvaluationEnabled() const;

  /// @brief 当前是否处于 Pixmoving 自驾执行模式
  bool isAutoExecutingMode() const;

  /// @brief 获取当前危险事件状态，处理 IMU 超时逻辑
  std::uint8_t getNearMissState() const;

  // ROS2 相关
  rclcpp::Node* node_;
  rclcpp::Subscription<tier4_metric_msgs::msg::MetricArray>::SharedPtr metrics_sub_;
  rclcpp::Subscription<sensor_msgs::msg::Imu>::SharedPtr imu_sub_;
  rclcpp::Subscription<autoware_adapi_v1_msgs::msg::OperationModeState>::SharedPtr operation_mode_sub_;
  rclcpp::Subscription<autoware_vehicle_msgs::msg::VelocityReport>::SharedPtr velocity_sub_;
  rclcpp::Subscription<autoware_planning_msgs::msg::LaneletRoute>::SharedPtr route_sub_;
  rclcpp::Subscription<pixmoving_hmi_msgs::msg::VehicleInfo>::SharedPtr vehicle_info_sub_;
  rclcpp::Subscription<pix_robobus_driver_msgs::msg::VaBrakeStaFb>::SharedPtr brake_status_sub_;
  rclcpp::Publisher<pixmoving_hmi_msgs::msg::PlanningMetrics>::SharedPtr planning_metrics_pub_;
  // 数据存储
  PlanningMetrics latest_metrics_;
  MetricsThresholds thresholds_;
  rclcpp::Time last_imu_time_;
  double last_imu_longitudinal_accel_ = 0.0;
  bool has_imu_data_ = false;
  std::uint8_t near_miss_state_ = 0;
  std::uint8_t stability_state_ = 0;
  int stability_bad_count_ = 0;
  int stability_good_count_ = 0;
  rclcpp::Time stability_bad_start_time_;
  std::uint8_t comfort_state_ = 0;
  int comfort_bad_count_ = 0;
  int comfort_good_count_ = 0;
  rclcpp::Time comfort_bad_start_time_;
  bool brake_pedal_pressed_ = false;
  rclcpp::Time comfort_brake_suppression_until_;
  bool has_operation_mode_data_ = false;
  bool is_autonomous_mode_ = false;
  bool has_velocity_data_ = false;
  double latest_vehicle_speed_mps_ = 0.0;
  bool has_route_data_ = false;
  bool has_ego_lane_id_ = false;
  std::int64_t latest_ego_lane_id_ = 0;
  std::unordered_set<std::int64_t> route_lane_ids_;
  bool has_vehicle_mode_data_ = false;
  int8_t latest_pixmoving_mode_ = -1;

  // 日志相关
  rclcpp::Time last_print_time_;
  double print_interval_sec_ = 2.0;  // 打印间隔（秒）
};

}  // namespace interface
}  // namespace chassis
}  // namespace pixmoving
