#include "robobus_hmi_data_relay/robobus_hmi_data_relay_node.hpp"

#include <rclcpp_components/register_node_macro.hpp>

namespace robobus_hmi_data_relay
{

RobobusHmiDataRelayNode::RobobusHmiDataRelayNode(const rclcpp::NodeOptions & options)
: rclcpp::Node("robobus_hmi_data_relay", options)
{
  (void)options;
  schedule_deferred_initialization();
}

void RobobusHmiDataRelayNode::schedule_deferred_initialization()
{
  deferred_init_timer_ = this->create_wall_timer(std::chrono::milliseconds(1), [this]() {
    if (deferred_init_timer_) {
      deferred_init_timer_->cancel();
      deferred_init_timer_.reset();
    }
    setup_modules();
  });
}

void RobobusHmiDataRelayNode::setup_modules()
{
  // Disabled: current vehicle deployment has no consumer for the legacy HMI
  // interfaces, and no longer needs the Git version publisher. Keep the code
  // commented for compatibility and easy restoration if required.
  // git_version_module_ =
  //   std::make_unique<robobus_hmi_data_relay::publishers::GitVersionPublisherModule>(this);
  // pixmoving_vehicle_display_bridge_module_ =
  //   std::make_unique<robobus_hmi_data_relay::bridges::PixmovingVehicleDisplayBridgeModule>(this);
  relay_autoware_transfer_bridge_module_ =
    std::make_unique<robobus_hmi_data_relay::bridges::RelayAutowareTransferBridgeModule>(this);
  diagnostic_alarm_bridge_module_ =
    std::make_unique<robobus_hmi_data_relay::bridges::DiagnosticAlarmBridgeModule>(this);
  blind_spot_monitor_module_ =
    std::make_unique<robobus_hmi_data_relay::monitors::BlindSpotMonitorModule>(this);
  health_monitor_module_ =
    std::make_unique<robobus_hmi_data_relay::monitors::HealthMonitorModule>(this);
}

RobobusHmiDataRelayNode::~RobobusHmiDataRelayNode() = default;

}  // namespace robobus_hmi_data_relay

RCLCPP_COMPONENTS_REGISTER_NODE(robobus_hmi_data_relay::RobobusHmiDataRelayNode)
