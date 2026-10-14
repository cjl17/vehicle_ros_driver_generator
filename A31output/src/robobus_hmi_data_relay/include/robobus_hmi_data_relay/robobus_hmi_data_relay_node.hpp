#ifndef ROBOBUS_HMI_DATA_RELAY__ROBOBUS_HMI_DATA_RELAY_NODE_HPP_
#define ROBOBUS_HMI_DATA_RELAY__ROBOBUS_HMI_DATA_RELAY_NODE_HPP_

#include "robobus_hmi_data_relay/bridges/diagnostic_alarm_bridge_module.hpp"
#include "robobus_hmi_data_relay/bridges/pixmoving_vehicle_display_bridge_module.hpp"
#include "robobus_hmi_data_relay/bridges/relay_autoware_transfer_module.hpp"
#include "robobus_hmi_data_relay/monitors/blind_spot_monitor_module.hpp"
#include "robobus_hmi_data_relay/monitors/health_monitor_module.hpp"
#include "robobus_hmi_data_relay/publishers/git_version_publisher_module.hpp"

#include <rclcpp/rclcpp.hpp>

namespace robobus_hmi_data_relay
{

class RobobusHmiDataRelayNode : public rclcpp::Node
{
public:
  explicit RobobusHmiDataRelayNode(const rclcpp::NodeOptions & options = rclcpp::NodeOptions());
  ~RobobusHmiDataRelayNode() override;

private:
  void schedule_deferred_initialization();
  void setup_modules();

  std::unique_ptr<robobus_hmi_data_relay::publishers::GitVersionPublisherModule>
    git_version_module_;
  std::unique_ptr<robobus_hmi_data_relay::bridges::PixmovingVehicleDisplayBridgeModule>
    pixmoving_vehicle_display_bridge_module_;
  std::unique_ptr<robobus_hmi_data_relay::monitors::BlindSpotMonitorModule>
    blind_spot_monitor_module_;
  std::unique_ptr<robobus_hmi_data_relay::monitors::HealthMonitorModule> health_monitor_module_;
  std::unique_ptr<robobus_hmi_data_relay::bridges::RelayAutowareTransferBridgeModule>
    relay_autoware_transfer_bridge_module_;
  std::unique_ptr<robobus_hmi_data_relay::bridges::DiagnosticAlarmBridgeModule>
    diagnostic_alarm_bridge_module_;
  rclcpp::TimerBase::SharedPtr deferred_init_timer_;
};

}  // namespace robobus_hmi_data_relay

#endif
