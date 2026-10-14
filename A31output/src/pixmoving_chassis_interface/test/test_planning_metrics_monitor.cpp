#include "pixmoving_chassis_interface/planning_metrics_monitor.hpp"

#include <rclcpp/rclcpp.hpp>

#include <pix_robobus_driver_msgs/msg/va_brake_sta_fb.hpp>
#include <pixmoving_hmi_msgs/msg/planning_metrics.hpp>
#include <tier4_metric_msgs/msg/metric.hpp>
#include <tier4_metric_msgs/msg/metric_array.hpp>

#include <gtest/gtest.h>

#include <chrono>
#include <cstdlib>
#include <functional>
#include <memory>
#include <thread>
#include <vector>

namespace pixmoving
{
namespace chassis
{
namespace interface
{
namespace
{

using namespace std::chrono_literals;

class PlanningMetricsMonitorTest : public ::testing::Test
{
protected:
  static void SetUpTestSuite()
  {
    setenv("ROS_DOMAIN_ID", "197", 1);
    setenv("ROS_LOG_DIR", "/tmp", 1);

    if (!rclcpp::ok()) {
      int argc = 0;
      char ** argv = nullptr;
      rclcpp::init(argc, argv);
    }
  }

  static void TearDownTestSuite()
  {
    if (rclcpp::ok()) {
      rclcpp::shutdown();
    }
  }

  void SetUp() override
  {
    node_ = std::make_shared<rclcpp::Node>("planning_metrics_monitor_test");
    monitor_ = std::make_unique<PlanningMetricsMonitor>(node_.get());

    MetricsThresholds thresholds;
    thresholds.jerk_uncomfortable_threshold = 1.0;
    thresholds.accel_limit = 100.0;
    thresholds.comfort_jerk_clear_threshold = 0.8;
    thresholds.comfort_accel_clear_limit = 80.0;
    thresholds.comfort_bad_count_threshold = 1;
    thresholds.comfort_good_count_threshold = 1;
    thresholds.comfort_min_event_duration_sec = 0.0;
    thresholds.comfort_require_auto_executing_mode = false;
    thresholds.comfort_suppress_on_brake_pedal = true;
    thresholds.comfort_brake_release_suppression_sec = 0.1;
    monitor_->setThresholds(thresholds);

    metrics_pub_ = node_->create_publisher<tier4_metric_msgs::msg::MetricArray>(
      "/planning/planning_evaluator/metrics", rclcpp::QoS(10));
    brake_pub_ = node_->create_publisher<pix_robobus_driver_msgs::msg::VaBrakeStaFb>(
      topics::VA_BRAKE_STA_FB, rclcpp::QoS(1));
    planning_metrics_sub_ = node_->create_subscription<pixmoving_hmi_msgs::msg::PlanningMetrics>(
      "/app/cloud_control_platform/planning_metrics", rclcpp::QoS(10),
      [this](const pixmoving_hmi_msgs::msg::PlanningMetrics::SharedPtr msg) {
        comfort_levels_.push_back(msg->comfort_level);
      });

    executor_ = std::make_unique<rclcpp::executors::SingleThreadedExecutor>();
    executor_->add_node(node_);

    ASSERT_TRUE(waitUntil([this]() {
      return metrics_pub_->get_subscription_count() > 0 &&
             brake_pub_->get_subscription_count() > 0 &&
             planning_metrics_sub_->get_publisher_count() > 0;
    }));
  }

  void TearDown() override
  {
    executor_->remove_node(node_);
    planning_metrics_sub_.reset();
    brake_pub_.reset();
    metrics_pub_.reset();
    monitor_.reset();
    node_.reset();
    executor_.reset();
  }

  bool waitUntil(const std::function<bool()> & predicate, std::chrono::milliseconds timeout = 2s)
  {
    const auto deadline = std::chrono::steady_clock::now() + timeout;
    while (std::chrono::steady_clock::now() < deadline) {
      executor_->spin_some();
      if (predicate()) {
        return true;
      }
      std::this_thread::sleep_for(5ms);
    }
    return predicate();
  }

  void spinFor(std::chrono::milliseconds duration)
  {
    const auto deadline = std::chrono::steady_clock::now() + duration;
    while (std::chrono::steady_clock::now() < deadline) {
      executor_->spin_some();
      std::this_thread::sleep_for(5ms);
    }
  }

  void publishBrakeState(bool pressed)
  {
    pix_robobus_driver_msgs::msg::VaBrakeStaFb msg;
    msg.vcu_brake_pedal_req_fb = pressed;
    brake_pub_->publish(msg);
    spinFor(30ms);
  }

  std::uint8_t publishUncomfortableMetric()
  {
    const auto previous_message_count = comfort_levels_.size();

    tier4_metric_msgs::msg::MetricArray msg;
    msg.stamp = node_->now();

    tier4_metric_msgs::msg::Metric comfort_metric;
    comfort_metric.name = "jerk/mean";
    comfort_metric.value = "2.0";
    msg.metric_array.push_back(comfort_metric);

    tier4_metric_msgs::msg::Metric kinematic_jerk;
    kinematic_jerk.name = "kinematic_state/jerk";
    kinematic_jerk.value = "2.0";
    msg.metric_array.push_back(kinematic_jerk);

    metrics_pub_->publish(msg);
    EXPECT_TRUE(waitUntil([this, previous_message_count]() {
      return comfort_levels_.size() > previous_message_count;
    }));

    return comfort_levels_.empty() ? 0 : comfort_levels_.back();
  }

  rclcpp::Node::SharedPtr node_;
  std::unique_ptr<PlanningMetricsMonitor> monitor_;
  std::unique_ptr<rclcpp::executors::SingleThreadedExecutor> executor_;
  rclcpp::Publisher<tier4_metric_msgs::msg::MetricArray>::SharedPtr metrics_pub_;
  rclcpp::Publisher<pix_robobus_driver_msgs::msg::VaBrakeStaFb>::SharedPtr brake_pub_;
  rclcpp::Subscription<pixmoving_hmi_msgs::msg::PlanningMetrics>::SharedPtr planning_metrics_sub_;
  std::vector<std::uint8_t> comfort_levels_;
};

TEST_F(PlanningMetricsMonitorTest, SuppressesComfortDuringBrakeAndReleaseCooldown)
{
  EXPECT_EQ(publishUncomfortableMetric(), 2);

  publishBrakeState(true);
  EXPECT_EQ(publishUncomfortableMetric(), 1);

  publishBrakeState(false);
  EXPECT_EQ(publishUncomfortableMetric(), 1);

  std::this_thread::sleep_for(120ms);
  EXPECT_EQ(publishUncomfortableMetric(), 2);
}

}  // namespace
}  // namespace interface
}  // namespace chassis
}  // namespace pixmoving
