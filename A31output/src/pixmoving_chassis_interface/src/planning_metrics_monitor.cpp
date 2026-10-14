#include "pixmoving_chassis_interface/planning_metrics_monitor.hpp"
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <sstream>

namespace pixmoving
{
namespace chassis
{
namespace interface
{
namespace
{
void normalizeClearLimit(double& clear_limit, double trigger_limit, const char* clear_name,
                         const char* trigger_name, const rclcpp::Logger& logger)
{
  if (clear_limit > trigger_limit)
  {
    const double normalized_clear_limit = trigger_limit * 0.8;
    RCLCPP_WARN(logger,
                "%s (%.3f) is greater than %s (%.3f). Using %.3f as clear threshold.",
                clear_name, clear_limit, trigger_name, trigger_limit, normalized_clear_limit);
    clear_limit = normalized_clear_limit;
  }
}
}  // namespace

PlanningMetricsMonitor::PlanningMetricsMonitor(rclcpp::Node* node) : node_(node)
{
  comfort_brake_suppression_until_ = rclcpp::Time(0, 0, node_->get_clock()->get_clock_type());

  // 订阅规划评估指标话题
  metrics_sub_ = node_->create_subscription<tier4_metric_msgs::msg::MetricArray>(
      "/planning/planning_evaluator/metrics", 10,
      std::bind(&PlanningMetricsMonitor::metricsCallback, this, std::placeholders::_1));

  imu_sub_ = node_->create_subscription<sensor_msgs::msg::Imu>(
      topics::GNSS_IMU, rclcpp::QoS(10), std::bind(&PlanningMetricsMonitor::imuCallback, this, std::placeholders::_1));

  operation_mode_sub_ = node_->create_subscription<autoware_adapi_v1_msgs::msg::OperationModeState>(
      topics::OPERATION_MODE_STATE, rclcpp::QoS(2),
      std::bind(&PlanningMetricsMonitor::operationModeCallback, this, std::placeholders::_1));

  velocity_sub_ = node_->create_subscription<autoware_vehicle_msgs::msg::VelocityReport>(
      topics::VEHICLE_VELOCITY_REPORT, rclcpp::QoS(10),
      std::bind(&PlanningMetricsMonitor::velocityCallback, this, std::placeholders::_1));

  route_sub_ = node_->create_subscription<autoware_planning_msgs::msg::LaneletRoute>(
      topics::PLANNING_ROUTE, rclcpp::QoS(1).transient_local(),
      std::bind(&PlanningMetricsMonitor::routeCallback, this, std::placeholders::_1));

  vehicle_info_sub_ = node_->create_subscription<pixmoving_hmi_msgs::msg::VehicleInfo>(
      pub_topics::VEHICLE_STATUS, rclcpp::QoS(10),
      std::bind(&PlanningMetricsMonitor::vehicleInfoCallback, this, std::placeholders::_1));

  brake_status_sub_ = node_->create_subscription<pix_robobus_driver_msgs::msg::VaBrakeStaFb>(
      topics::VA_BRAKE_STA_FB, rclcpp::QoS(1),
      std::bind(&PlanningMetricsMonitor::brakeStatusCallback, this, std::placeholders::_1));

  planning_metrics_pub_ = node_->create_publisher<pixmoving_hmi_msgs::msg::PlanningMetrics>(
      "/app/cloud_control_platform/planning_metrics", 10);

  last_print_time_ = node_->now();

  RCLCPP_INFO(node_->get_logger(), "=================================================================");
  RCLCPP_INFO(node_->get_logger(), "  Planning Metrics Monitor Initialized");
  RCLCPP_INFO(node_->get_logger(), "  Subscribed to: /planning/planning_evaluator/metrics");
  RCLCPP_INFO(node_->get_logger(), "  Subscribed to: %s", topics::GNSS_IMU);
  RCLCPP_INFO(node_->get_logger(), "  Subscribed to: %s", topics::OPERATION_MODE_STATE);
  RCLCPP_INFO(node_->get_logger(), "  Subscribed to: %s", topics::VEHICLE_VELOCITY_REPORT);
  RCLCPP_INFO(node_->get_logger(), "  Subscribed to: %s", topics::PLANNING_ROUTE);
  RCLCPP_INFO(node_->get_logger(), "  Subscribed to: %s", pub_topics::VEHICLE_STATUS);
  RCLCPP_INFO(node_->get_logger(), "  Subscribed to: %s", topics::VA_BRAKE_STA_FB);
  RCLCPP_INFO(node_->get_logger(), "  Monitoring:");
  RCLCPP_INFO(node_->get_logger(), "    - Comfort Metrics: jerk, acceleration, velocity");
  RCLCPP_INFO(node_->get_logger(), "    - Stability Metrics: trajectory stability, lateral displacement");
  RCLCPP_INFO(node_->get_logger(), "    - Near Miss State: IMU longitudinal acceleration magnitude");
  RCLCPP_INFO(node_->get_logger(), "=================================================================");
}

void PlanningMetricsMonitor::metricsCallback(const tier4_metric_msgs::msg::MetricArray::SharedPtr msg)
{
  latest_metrics_.timestamp = rclcpp::Time(msg->stamp);
  has_ego_lane_id_ = extractMetricValue(msg->metric_array, "ego_lane_info/lane_id", latest_ego_lane_id_);

  // 提取舒适性指标
  bool has_jerk = extractMetricValue(msg->metric_array, "jerk/mean", latest_metrics_.jerk_mean);
  extractMetricValue(msg->metric_array, "jerk/min", latest_metrics_.jerk_min);
  extractMetricValue(msg->metric_array, "jerk/max", latest_metrics_.jerk_max);

  bool has_accel = extractMetricValue(msg->metric_array, "acceleration/mean", latest_metrics_.acceleration_mean);
  extractMetricValue(msg->metric_array, "acceleration/min", latest_metrics_.acceleration_min);
  extractMetricValue(msg->metric_array, "acceleration/max", latest_metrics_.acceleration_max);

  bool has_vel = extractMetricValue(msg->metric_array, "velocity/mean", latest_metrics_.velocity_mean);

  latest_metrics_.has_comfort_data = has_jerk || has_accel || has_vel;

  // 提取轨迹稳定性指标
  bool has_stability = extractMetricValue(msg->metric_array, "stability/mean", latest_metrics_.stability_mean);
  extractMetricValue(msg->metric_array, "stability/min", latest_metrics_.stability_min);
  extractMetricValue(msg->metric_array, "stability/max", latest_metrics_.stability_max);

  bool has_frechet =
      extractMetricValue(msg->metric_array, "stability_frechet/mean", latest_metrics_.stability_frechet_mean);

  bool has_local_disp = extractMetricValue(msg->metric_array, "lateral_trajectory_displacement_local/mean",
                                           latest_metrics_.lateral_displacement_local);

  bool has_lookahead = extractMetricValue(msg->metric_array, "lateral_trajectory_displacement_lookahead/mean",
                                          latest_metrics_.lateral_displacement_lookahead_mean);
  extractMetricValue(msg->metric_array, "lateral_trajectory_displacement_lookahead/max",
                     latest_metrics_.lateral_displacement_lookahead_max);

  latest_metrics_.has_stability_data = has_stability || has_frechet || has_local_disp || has_lookahead;

  // 提取当前运动状态
  extractMetricValue(msg->metric_array, "kinematic_state/vel", latest_metrics_.kinematic_velocity);
  extractMetricValue(msg->metric_array, "kinematic_state/acc", latest_metrics_.kinematic_acceleration);
  extractMetricValue(msg->metric_array, "kinematic_state/jerk", latest_metrics_.kinematic_jerk);

  // 帧计数只由新的 evaluator 样本推进，避免其他数据源发布时重复累计。
  updateComfortState();
  updateStabilityState();
  publishPlanningMetrics(latest_metrics_.timestamp);
}

void PlanningMetricsMonitor::imuCallback(const sensor_msgs::msg::Imu::SharedPtr msg)
{
  const bool had_recent_imu_data =
      has_imu_data_ && (node_->now() - last_imu_time_).seconds() <= thresholds_.imu_timeout_sec;

  last_imu_time_ = rclcpp::Time(msg->header.stamp);
  if (last_imu_time_.nanoseconds() == 0)
  {
    last_imu_time_ = node_->now();
  }

  has_imu_data_ = true;
  last_imu_longitudinal_accel_ = msg->linear_acceleration.x;
  const double longitudinal_accel_abs = std::abs(last_imu_longitudinal_accel_);
  const bool az_anomaly = std::abs(msg->linear_acceleration.z) > 12.0;
  const auto previous_state = near_miss_state_;
  updateNearMissState(longitudinal_accel_abs, az_anomaly, had_recent_imu_data);

  if (previous_state != near_miss_state_ && latest_metrics_.timestamp.nanoseconds() != 0)
  {
    publishPlanningMetrics(last_imu_time_);
  }
}

void PlanningMetricsMonitor::operationModeCallback(
    const autoware_adapi_v1_msgs::msg::OperationModeState::SharedPtr msg)
{
  has_operation_mode_data_ = true;
  is_autonomous_mode_ = msg->mode == autoware_adapi_v1_msgs::msg::OperationModeState::AUTONOMOUS &&
                        msg->is_autoware_control_enabled;
}

void PlanningMetricsMonitor::velocityCallback(const autoware_vehicle_msgs::msg::VelocityReport::SharedPtr msg)
{
  has_velocity_data_ = true;
  latest_vehicle_speed_mps_ = msg->longitudinal_velocity;
}

void PlanningMetricsMonitor::routeCallback(const autoware_planning_msgs::msg::LaneletRoute::SharedPtr msg)
{
  route_lane_ids_.clear();
  for (const auto& segment : msg->segments)
  {
    if (segment.preferred_primitive.id > 0)
    {
      route_lane_ids_.insert(segment.preferred_primitive.id);
    }
    for (const auto& primitive : segment.primitives)
    {
      if (primitive.id > 0)
      {
        route_lane_ids_.insert(primitive.id);
      }
    }
  }
  has_route_data_ = !route_lane_ids_.empty();
}

void PlanningMetricsMonitor::vehicleInfoCallback(const pixmoving_hmi_msgs::msg::VehicleInfo::SharedPtr msg)
{
  has_vehicle_mode_data_ = true;
  latest_pixmoving_mode_ = msg->mode;

  // mode=7 作为原始刹车反馈之外的备用信号，持续刷新释放后的抑制窗口。
  if (thresholds_.comfort_suppress_on_brake_pedal &&
      latest_pixmoving_mode_ == ChassisInterfaceUtils::toInt8(DriveMode::AUTO_TAKEOVER_BRAKE))
  {
    comfort_brake_suppression_until_ =
        node_->now() + rclcpp::Duration::from_seconds(thresholds_.comfort_brake_release_suppression_sec);
  }
}

void PlanningMetricsMonitor::brakeStatusCallback(
    const pix_robobus_driver_msgs::msg::VaBrakeStaFb::SharedPtr msg)
{
  const bool brake_pedal_pressed = msg->vcu_brake_pedal_req_fb == 1;

  if (thresholds_.comfort_suppress_on_brake_pedal && (brake_pedal_pressed || brake_pedal_pressed_))
  {
    comfort_brake_suppression_until_ =
        node_->now() + rclcpp::Duration::from_seconds(thresholds_.comfort_brake_release_suppression_sec);
  }

  if (thresholds_.comfort_suppress_on_brake_pedal && brake_pedal_pressed != brake_pedal_pressed_)
  {
    RCLCPP_INFO(node_->get_logger(),
                "Comfort evaluation brake suppression %s; release cooldown: %.1f s",
                brake_pedal_pressed ? "started" : "release cooldown started",
                thresholds_.comfort_brake_release_suppression_sec);
  }

  brake_pedal_pressed_ = brake_pedal_pressed;
}

void PlanningMetricsMonitor::publishPlanningMetrics(const rclcpp::Time& stamp)
{
  pixmoving_hmi_msgs::msg::PlanningMetrics planning_metrics;
  planning_metrics.header.stamp = stamp.nanoseconds() == 0 ? node_->now() : stamp;
  planning_metrics.jerk_mean = latest_metrics_.jerk_mean;
  planning_metrics.jerk_min = latest_metrics_.jerk_min;
  planning_metrics.jerk_max = latest_metrics_.jerk_max;
  planning_metrics.acceleration_mean = latest_metrics_.acceleration_mean;
  planning_metrics.acceleration_min = latest_metrics_.acceleration_min;
  planning_metrics.acceleration_max = latest_metrics_.acceleration_max;
  planning_metrics.velocity_mean = latest_metrics_.velocity_mean;
  planning_metrics.kinematic_velocity = latest_metrics_.kinematic_velocity;
  planning_metrics.kinematic_acceleration = latest_metrics_.kinematic_acceleration;
  planning_metrics.kinematic_jerk = latest_metrics_.kinematic_jerk;
  planning_metrics.has_comfort_data = latest_metrics_.has_comfort_data;
  planning_metrics.has_stability_data = latest_metrics_.has_stability_data;
  planning_metrics.stability_mean = latest_metrics_.stability_mean;
  planning_metrics.stability_min = latest_metrics_.stability_min;
  planning_metrics.stability_max = latest_metrics_.stability_max;
  planning_metrics.stability_frechet_mean = latest_metrics_.stability_frechet_mean;
  planning_metrics.lateral_displacement_local = latest_metrics_.lateral_displacement_local;
  planning_metrics.lateral_displacement_lookahead_mean = latest_metrics_.lateral_displacement_lookahead_mean;
  planning_metrics.lateral_displacement_lookahead_max = latest_metrics_.lateral_displacement_lookahead_max;

  planning_metrics.comfort_level = comfort_state_;
  planning_metrics.stability_level = stability_state_;

  planning_metrics.has_near_miss = getNearMissState();
  planning_metrics_pub_->publish(planning_metrics);
}

void PlanningMetricsMonitor::setThresholds(const MetricsThresholds& thresholds)
{
  thresholds_ = thresholds;
  if (thresholds_.near_miss_clear_accel < 0.0)
  {
    RCLCPP_WARN(node_->get_logger(),
                "near_miss_clear_accel (%.3f) is negative. Near miss uses abs(ax), "
                "so the clear threshold will use its absolute value.",
                thresholds_.near_miss_clear_accel);
    thresholds_.near_miss_clear_accel = std::abs(thresholds_.near_miss_clear_accel);
  }
  if (thresholds_.near_miss_trigger_accel < 0.0)
  {
    RCLCPP_WARN(node_->get_logger(),
                "near_miss_trigger_accel (%.3f) is negative. Near miss uses abs(ax), "
                "so the trigger threshold will use its absolute value.",
                thresholds_.near_miss_trigger_accel);
    thresholds_.near_miss_trigger_accel = std::abs(thresholds_.near_miss_trigger_accel);
  }
  if (thresholds_.near_miss_clear_accel > thresholds_.near_miss_trigger_accel)
  {
    RCLCPP_WARN(node_->get_logger(),
                "near_miss_clear_accel (%.3f) is greater than near_miss_trigger_accel (%.3f). "
                "Clamping clear threshold to trigger threshold.",
                thresholds_.near_miss_clear_accel, thresholds_.near_miss_trigger_accel);
    thresholds_.near_miss_clear_accel = thresholds_.near_miss_trigger_accel;
  }
  normalizeClearLimit(thresholds_.stability_mean_clear_limit, thresholds_.stability_mean_limit,
                      "stability_mean_clear_limit", "stability_mean_limit", node_->get_logger());
  normalizeClearLimit(thresholds_.frechet_clear_limit, thresholds_.frechet_limit,
                      "frechet_clear_limit", "frechet_limit", node_->get_logger());
  normalizeClearLimit(thresholds_.local_disp_clear_limit, thresholds_.local_disp_limit,
                      "local_disp_clear_limit", "local_disp_limit", node_->get_logger());
  normalizeClearLimit(thresholds_.lookahead_max_clear_limit, thresholds_.lookahead_max_limit,
                      "lookahead_max_clear_limit", "lookahead_max_limit", node_->get_logger());
  normalizeClearLimit(thresholds_.comfort_jerk_clear_threshold, thresholds_.jerk_uncomfortable_threshold,
                      "comfort_jerk_clear_threshold", "jerk_uncomfortable_threshold", node_->get_logger());
  normalizeClearLimit(thresholds_.comfort_accel_clear_limit, thresholds_.accel_limit,
                      "comfort_accel_clear_limit", "accel_limit", node_->get_logger());
  thresholds_.comfort_bad_count_threshold = std::max(1, thresholds_.comfort_bad_count_threshold);
  thresholds_.comfort_good_count_threshold = std::max(1, thresholds_.comfort_good_count_threshold);
  thresholds_.comfort_min_event_duration_sec = std::max(0.0, thresholds_.comfort_min_event_duration_sec);
  thresholds_.comfort_brake_release_suppression_sec =
      std::max(0.0, thresholds_.comfort_brake_release_suppression_sec);
  thresholds_.stability_bad_count_threshold = std::max(1, thresholds_.stability_bad_count_threshold);
  thresholds_.stability_good_count_threshold = std::max(1, thresholds_.stability_good_count_threshold);
  thresholds_.stability_min_event_duration_sec = std::max(0.0, thresholds_.stability_min_event_duration_sec);
  RCLCPP_INFO(node_->get_logger(),
              "\n========== Planning Metrics Thresholds ==========\n"
              "jerk_uncomfortable_threshold : %.3f\n"
              "accel_limit                  : %.3f\n"
              "comfort_jerk_clear_threshold : %.3f\n"
              "comfort_accel_clear_limit    : %.3f\n"
              "comfort_bad_count_threshold  : %d\n"
              "comfort_good_count_threshold : %d\n"
              "comfort_min_event_duration_sec: %.3f\n"
              "near_miss_trigger_accel      : %.3f\n"
              "near_miss_clear_accel        : %.3f\n"
              "imu_timeout_sec              : %.3f\n"
              "stability_mean_limit         : %.3f\n"
              "frechet_limit                : %.3f\n"
              "local_disp_limit             : %.3f\n"
              "lookahead_max_limit          : %.3f\n"
              "stability_mean_clear_limit   : %.3f\n"
              "frechet_clear_limit          : %.3f\n"
              "local_disp_clear_limit       : %.3f\n"
              "lookahead_max_clear_limit    : %.3f\n"
              "stability_bad_count_threshold: %d\n"
              "stability_good_count_threshold: %d\n"
              "stability_min_event_duration_sec: %.3f\n"
              "stability_require_autonomous_mode: %s\n"
              "stability_suppress_when_stopped  : %s\n"
              "stability_standstill_speed_threshold_mps: %.3f\n"
              "stability_require_route_lane     : %s\n"
              "stability_require_auto_executing_mode: %s\n"
              "comfort_require_auto_executing_mode  : %s\n"
              "comfort_suppress_on_brake_pedal      : %s\n"
              "comfort_brake_release_suppression_sec: %.3f\n"
              "===============================================\n",
              thresholds_.jerk_uncomfortable_threshold, thresholds_.accel_limit,
              thresholds_.comfort_jerk_clear_threshold, thresholds_.comfort_accel_clear_limit,
              thresholds_.comfort_bad_count_threshold, thresholds_.comfort_good_count_threshold,
              thresholds_.comfort_min_event_duration_sec,
              thresholds_.near_miss_trigger_accel,
              thresholds_.near_miss_clear_accel, thresholds_.imu_timeout_sec, thresholds_.stability_mean_limit,
              thresholds_.frechet_limit, thresholds_.local_disp_limit, thresholds_.lookahead_max_limit,
              thresholds_.stability_mean_clear_limit, thresholds_.frechet_clear_limit,
              thresholds_.local_disp_clear_limit, thresholds_.lookahead_max_clear_limit,
              thresholds_.stability_bad_count_threshold, thresholds_.stability_good_count_threshold,
              thresholds_.stability_min_event_duration_sec,
              thresholds_.stability_require_autonomous_mode ? "true" : "false",
              thresholds_.stability_suppress_when_stopped ? "true" : "false",
              thresholds_.stability_standstill_speed_threshold_mps,
              thresholds_.stability_require_route_lane ? "true" : "false",
              thresholds_.stability_require_auto_executing_mode ? "true" : "false",
              thresholds_.comfort_require_auto_executing_mode ? "true" : "false",
              thresholds_.comfort_suppress_on_brake_pedal ? "true" : "false",
              thresholds_.comfort_brake_release_suppression_sec);
}

bool PlanningMetricsMonitor::extractMetricValue(const std::vector<tier4_metric_msgs::msg::Metric>& metric_array,
                                                const std::string& metric_name, double& value)
{
  for (const auto& metric : metric_array)
  {
    if (metric.name == metric_name)
    {
      // 对于 kinematic_state，直接使用 unit 字段作为子指标名
      if (metric_name == "kinematic_state")
      {
        try
        {
          value = std::stod(metric.value);
          return true;
        }
        catch (const std::exception& e)
        {
          RCLCPP_WARN(node_->get_logger(), "Failed to parse metric value for %s: %s", metric_name.c_str(), e.what());
          return false;
        }
      }
      else
      {
        // 对于其他指标，使用 unit 字段作为统计类型（mean/min/max）
        try
        {
          value = std::stod(metric.value);
          return true;
        }
        catch (const std::exception& e)
        {
          RCLCPP_WARN(node_->get_logger(), "Failed to parse metric value for %s: %s", metric_name.c_str(), e.what());
          return false;
        }
      }
    }
  }
  return false;
}

bool PlanningMetricsMonitor::extractMetricValue(const std::vector<tier4_metric_msgs::msg::Metric>& metric_array,
                                                const std::string& metric_name, std::int64_t& value)
{
  for (const auto& metric : metric_array)
  {
    if (metric.name == metric_name)
    {
      try
      {
        value = std::stoll(metric.value);
        return true;
      }
      catch (const std::exception& e)
      {
        RCLCPP_WARN(node_->get_logger(), "Failed to parse metric value for %s: %s", metric_name.c_str(), e.what());
        return false;
      }
    }
  }
  return false;
}

void PlanningMetricsMonitor::printComfortMetrics()
{
  if (!latest_metrics_.has_comfort_data)
  {
    return;
  }

  std::stringstream ss;
  ss << "\n";
  ss << "╔════════════════════════════════════════════════════════════════╗\n";
  ss << "║              驾驶舒适性指标 (Comfort Metrics)                  ║\n";
  ss << "╠════════════════════════════════════════════════════════════════╣\n";
  ss << "║ 急动度 (Jerk) [m/s³]:                                          ║\n";
  ss << "║   平均值: " << std::setw(10) << std::fixed << std::setprecision(4) << latest_metrics_.jerk_mean
     << " m/s³                                    ║\n";
  ss << "║   最小值: " << std::setw(10) << std::fixed << std::setprecision(4) << latest_metrics_.jerk_min
     << " m/s³                                    ║\n";
  ss << "║   最大值: " << std::setw(10) << std::fixed << std::setprecision(4) << latest_metrics_.jerk_max
     << " m/s³                                    ║\n";
  ss << "╟────────────────────────────────────────────────────────────────╢\n";
  ss << "║ 加速度 (Acceleration) [m/s²]:                                  ║\n";
  ss << "║   平均值: " << std::setw(10) << std::fixed << std::setprecision(4) << latest_metrics_.acceleration_mean
     << " m/s²                                   ║\n";
  ss << "║   最小值: " << std::setw(10) << std::fixed << std::setprecision(4) << latest_metrics_.acceleration_min
     << " m/s²                                   ║\n";
  ss << "║   最大值: " << std::setw(10) << std::fixed << std::setprecision(4) << latest_metrics_.acceleration_max
     << " m/s²                                   ║\n";
  ss << "╟────────────────────────────────────────────────────────────────╢\n";
  ss << "║ 速度 (Velocity) [m/s]:                                         ║\n";
  ss << "║   平均值: " << std::setw(10) << std::fixed << std::setprecision(4) << latest_metrics_.velocity_mean
     << " m/s                                     ║\n";
  ss << "╟────────────────────────────────────────────────────────────────╢\n";
  ss << "║ 当前运动状态 (Current Kinematic State):                        ║\n";
  ss << "║   速度:   " << std::setw(10) << std::fixed << std::setprecision(4) << latest_metrics_.kinematic_velocity
     << " m/s                                     ║\n";
  ss << "║   加速度: " << std::setw(10) << std::fixed << std::setprecision(4) << latest_metrics_.kinematic_acceleration
     << " m/s²                                   ║\n";
  ss << "║   急动度: " << std::setw(10) << std::fixed << std::setprecision(4) << latest_metrics_.kinematic_jerk
     << " m/s³                                    ║\n";
  ss << "╚════════════════════════════════════════════════════════════════╝\n";

  RCLCPP_INFO(node_->get_logger(), "%s", ss.str().c_str());
}

void PlanningMetricsMonitor::printStabilityMetrics()
{
  if (!latest_metrics_.has_stability_data)
  {
    return;
  }

  std::stringstream ss;
  ss << "\n";
  ss << "╔════════════════════════════════════════════════════════════════╗\n";
  ss << "║           轨迹稳定性指标 (Trajectory Stability Metrics)        ║\n";
  ss << "╠════════════════════════════════════════════════════════════════╣\n";
  ss << "║ 轨迹稳定性 (Stability) [m]:                                    ║\n";
  ss << "║   平均横向偏差: " << std::setw(10) << std::fixed << std::setprecision(4) << latest_metrics_.stability_mean
     << " m                                  ║\n";
  ss << "║   最小横向偏差: " << std::setw(10) << std::fixed << std::setprecision(4) << latest_metrics_.stability_min
     << " m                                  ║\n";
  ss << "║   最大横向偏差: " << std::setw(10) << std::fixed << std::setprecision(4) << latest_metrics_.stability_max
     << " m                                  ║\n";
  ss << "╟────────────────────────────────────────────────────────────────╢\n";
  ss << "║ Frechet距离 (轨迹相似度) [m]:                                  ║\n";
  ss << "║   平均值: " << std::setw(10) << std::fixed << std::setprecision(4) << latest_metrics_.stability_frechet_mean
     << " m                                      ║\n";
  ss << "╟────────────────────────────────────────────────────────────────╢\n";
  ss << "║ 横向位移 (Lateral Displacement) [m]:                           ║\n";
  ss << "║   局部位移:     " << std::setw(10) << std::fixed << std::setprecision(4)
     << latest_metrics_.lateral_displacement_local << " m                              ║\n";
  ss << "║   前瞻平均位移: " << std::setw(10) << std::fixed << std::setprecision(4)
     << latest_metrics_.lateral_displacement_lookahead_mean << " m                              ║\n";
  ss << "║   前瞻最大位移: " << std::setw(10) << std::fixed << std::setprecision(4)
     << latest_metrics_.lateral_displacement_lookahead_max << " m                              ║\n";
  ss << "╚════════════════════════════════════════════════════════════════╝\n";

  RCLCPP_INFO(node_->get_logger(), "%s", ss.str().c_str());
}

std::uint8_t PlanningMetricsMonitor::updateComfortState()
{
  if (!latest_metrics_.has_comfort_data)
  {
    comfort_state_ = 0;
    comfort_bad_count_ = 0;
    comfort_good_count_ = 0;
    comfort_bad_start_time_ = rclcpp::Time(0, 0, node_->get_clock()->get_clock_type());
    return comfort_state_;
  }

  if (!isComfortEvaluationEnabled())
  {
    comfort_state_ = 1;
    comfort_bad_count_ = 0;
    comfort_good_count_ = 0;
    comfort_bad_start_time_ = rclcpp::Time(0, 0, node_->get_clock()->get_clock_type());
    return comfort_state_;
  }

  const double abs_jerk = std::abs(latest_metrics_.kinematic_jerk);
  const double abs_accel = std::abs(latest_metrics_.kinematic_acceleration);
  const bool is_over_trigger =
      abs_jerk > thresholds_.jerk_uncomfortable_threshold || abs_accel > thresholds_.accel_limit;
  const bool is_under_clear =
      abs_jerk <= thresholds_.comfort_jerk_clear_threshold && abs_accel <= thresholds_.comfort_accel_clear_limit;

  if (comfort_state_ == 0)
  {
    comfort_state_ = 1;
  }

  if (comfort_state_ == 2)
  {
    if (is_under_clear)
    {
      ++comfort_good_count_;
      comfort_bad_count_ = 0;
      if (comfort_good_count_ >= thresholds_.comfort_good_count_threshold)
      {
        comfort_state_ = 1;
        comfort_good_count_ = 0;
      }
    }
    else
    {
      comfort_good_count_ = 0;
    }
    return comfort_state_;
  }

  if (is_over_trigger)
  {
    if (comfort_bad_count_ == 0)
    {
      comfort_bad_start_time_ = node_->now();
    }
    ++comfort_bad_count_;
    comfort_good_count_ = 0;
    const double bad_duration =
        comfort_bad_start_time_.nanoseconds() == 0 ? 0.0 : (node_->now() - comfort_bad_start_time_).seconds();
    if (comfort_bad_count_ >= thresholds_.comfort_bad_count_threshold &&
        bad_duration >= thresholds_.comfort_min_event_duration_sec)
    {
      comfort_state_ = 2;
      comfort_bad_count_ = 0;
      comfort_bad_start_time_ = rclcpp::Time(0, 0, node_->get_clock()->get_clock_type());
    }
  }
  else
  {
    comfort_bad_count_ = 0;
    comfort_bad_start_time_ = rclcpp::Time(0, 0, node_->get_clock()->get_clock_type());
  }

  return comfort_state_;
}

std::uint8_t PlanningMetricsMonitor::updateStabilityState()
{
  if (!latest_metrics_.has_stability_data)
  {
    stability_state_ = 0;
    stability_bad_count_ = 0;
    stability_good_count_ = 0;
    stability_bad_start_time_ = rclcpp::Time(0, 0, node_->get_clock()->get_clock_type());
    return stability_state_;
  }

  if (!isStabilityEvaluationEnabled())
  {
    stability_state_ = 1;
    stability_bad_count_ = 0;
    stability_good_count_ = 0;
    stability_bad_start_time_ = rclcpp::Time(0, 0, node_->get_clock()->get_clock_type());
    return stability_state_;
  }

  const bool is_over_trigger =
      latest_metrics_.stability_mean > thresholds_.stability_mean_limit ||
      latest_metrics_.stability_frechet_mean > thresholds_.frechet_limit ||
      latest_metrics_.lateral_displacement_local > thresholds_.local_disp_limit ||
      latest_metrics_.lateral_displacement_lookahead_max > thresholds_.lookahead_max_limit;

  const bool is_under_clear =
      latest_metrics_.stability_mean <= thresholds_.stability_mean_clear_limit &&
      latest_metrics_.stability_frechet_mean <= thresholds_.frechet_clear_limit &&
      latest_metrics_.lateral_displacement_local <= thresholds_.local_disp_clear_limit &&
      latest_metrics_.lateral_displacement_lookahead_max <= thresholds_.lookahead_max_clear_limit;

  if (stability_state_ == 0)
  {
    stability_state_ = 1;
  }

  if (stability_state_ == 2)
  {
    if (is_under_clear)
    {
      ++stability_good_count_;
      stability_bad_count_ = 0;
      if (stability_good_count_ >= thresholds_.stability_good_count_threshold)
      {
        stability_state_ = 1;
        stability_good_count_ = 0;
      }
    }
    else
    {
      stability_good_count_ = 0;
    }
    return stability_state_;
  }

  if (is_over_trigger)
  {
    if (stability_bad_count_ == 0)
    {
      stability_bad_start_time_ = node_->now();
    }
    ++stability_bad_count_;
    stability_good_count_ = 0;
    const double bad_duration =
        stability_bad_start_time_.nanoseconds() == 0 ? 0.0 : (node_->now() - stability_bad_start_time_).seconds();
    if (stability_bad_count_ >= thresholds_.stability_bad_count_threshold &&
        bad_duration >= thresholds_.stability_min_event_duration_sec)
    {
      stability_state_ = 2;
      stability_bad_count_ = 0;
      stability_bad_start_time_ = rclcpp::Time(0, 0, node_->get_clock()->get_clock_type());
    }
  }
  else
  {
    stability_bad_count_ = 0;
    stability_bad_start_time_ = rclcpp::Time(0, 0, node_->get_clock()->get_clock_type());
  }

  return stability_state_;
}

bool PlanningMetricsMonitor::isStabilityEvaluationEnabled() const
{
  if (thresholds_.stability_require_auto_executing_mode && !isAutoExecutingMode())
  {
    return false;
  }

  if (thresholds_.stability_require_autonomous_mode && (!has_operation_mode_data_ || !is_autonomous_mode_))
  {
    return false;
  }

  if (thresholds_.stability_suppress_when_stopped && has_velocity_data_ &&
      std::abs(latest_vehicle_speed_mps_) <= thresholds_.stability_standstill_speed_threshold_mps)
  {
    return false;
  }

  if (thresholds_.stability_require_route_lane)
  {
    if (!has_route_data_ || !has_ego_lane_id_ || latest_ego_lane_id_ <= 0)
    {
      return false;
    }
    if (route_lane_ids_.count(latest_ego_lane_id_) == 0)
    {
      return false;
    }
  }

  return true;
}

bool PlanningMetricsMonitor::isComfortEvaluationEnabled() const
{
  if (thresholds_.comfort_suppress_on_brake_pedal &&
      (brake_pedal_pressed_ || node_->now() < comfort_brake_suppression_until_))
  {
    return false;
  }

  if (thresholds_.comfort_require_auto_executing_mode && !isAutoExecutingMode())
  {
    return false;
  }

  return true;
}

bool PlanningMetricsMonitor::isAutoExecutingMode() const
{
  return has_vehicle_mode_data_ &&
         latest_pixmoving_mode_ == ChassisInterfaceUtils::toInt8(DriveMode::AUTO_EXECUTING);
}

void PlanningMetricsMonitor::updateNearMissState(double longitudinal_accel_abs, bool az_anomaly,
                                                 bool had_recent_imu_data)
{
  if (!had_recent_imu_data || near_miss_state_ == 0)
  {
    near_miss_state_ =
        (longitudinal_accel_abs > thresholds_.near_miss_trigger_accel && !az_anomaly) ? 2 : 1;
    return;
  }

  if (longitudinal_accel_abs > thresholds_.near_miss_trigger_accel && !az_anomaly)
  {
    near_miss_state_ = 2;
    return;
  }

  if (longitudinal_accel_abs <= thresholds_.near_miss_clear_accel)
  {
    near_miss_state_ = 1;
  }
}

std::uint8_t PlanningMetricsMonitor::getNearMissState() const
{
  if (!has_imu_data_)
  {
    return 0;
  }

  if ((node_->now() - last_imu_time_).seconds() > thresholds_.imu_timeout_sec)
  {
    return 0;
  }

  return near_miss_state_;
}

PlanningMetrics PlanningMetricsMonitor::getLatestMetrics() const
{
  return latest_metrics_;
}

bool PlanningMetricsMonitor::isDataValid(double timeout_sec) const
{
  auto current_time = node_->now();
  auto time_diff = (current_time - latest_metrics_.timestamp).seconds();
  return time_diff < timeout_sec;
}

}  // namespace interface
}  // namespace chassis
}  // namespace pixmoving
