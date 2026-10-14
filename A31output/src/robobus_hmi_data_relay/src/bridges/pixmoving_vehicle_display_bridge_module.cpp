#include "robobus_hmi_data_relay/bridges/pixmoving_vehicle_display_bridge_module.hpp"

namespace
{
using namespace std::chrono_literals;

struct AlarmRange
{
  const char * name;
  uint32_t start;
  uint32_t end;
};

static const std::array<AlarmRange, 24> kAlarmRanges{{
  {"VCU", 0x01000000, 0x01000FFF},
  {"MCU", 0x01010000, 0x010101FF},
  {"BCM", 0x01020000, 0x010200FF},
  {"EHB", 0x01030000, 0x010300FF},
  {"EPS", 0x01040000, 0x010400FF},
  {"BMS", 0x01050000, 0x010500FF},
  {"RCU", 0x01060000, 0x010600FF},
  {"AC", 0x01070000, 0x010700FF},
  {"BCU", 0x01080000, 0x010800FF},
  {"DCDC", 0x01090000, 0x010900FF},
  {"OBC", 0x010A0000, 0x010A00FF},
  {"数字电源", 0x01100000, 0x011011FF},
  {"门控制器", 0x01120000, 0x011200FF},
  {"低速提示器", 0x01130000, 0x011300FF},
  {"长条控车屏", 0x01140000, 0x011400FF},
  {"传感器模块", 0x02010000, 0x0201FFFF},
  {"定位模块", 0x02020000, 0x0202FFFF},
  {"感知模块", 0x02030000, 0x0203FFFF},
  {"规划模块", 0x02040000, 0x0204FFFF},
  {"控制模块", 0x02050000, 0x0205FFFF},
  {"系统模块", 0x02060000, 0x0206FFFF},
  {"其他模块", 0x02070000, 0x0207FFFF},
  {"车端", 0x03010000, 0x0301FFFF},
  {"遥控座舱", 0x03020000, 0x0302FFFF},
}};

std::string package_libexec_path()
{
  namespace fs = std::filesystem;
  auto exe_path = fs::canonical("/proc/self/exe");
  auto prefix = exe_path.parent_path().parent_path().parent_path();
  auto libexec = prefix / "lib" / "robobus_hmi_data_relay";
  return libexec.string();
}

std::string run_command_capture(const std::string & command)
{
  std::array<char, 256> buffer{};
  std::string result;
  FILE * pipe = popen(command.c_str(), "r");
  if (!pipe) {
    return result;
  }
  while (fgets(buffer.data(), static_cast<int>(buffer.size()), pipe) != nullptr) {
    result += buffer.data();
  }
  pclose(pipe);
  return result;
}

bool file_exists(const std::string & path)
{
  return std::filesystem::exists(std::filesystem::path(path));
}
}  // namespace

namespace robobus_hmi_data_relay::bridges
{

PixmovingVehicleDisplayBridgeModule::PixmovingVehicleDisplayBridgeModule(rclcpp::Node * node)
: node_(node),
  tools_path_(package_libexec_path()),
  has_pactl_(std::system("command -v pactl >/dev/null 2>&1") == 0)
{
  setup_forwarders();
  setup_services();
  setup_clients();

  alarm_sub_ = node_->create_subscription<pixmoving_hmi_msgs::msg::Alarm>(
    "/communiction/alarm", 10,
    std::bind(&PixmovingVehicleDisplayBridgeModule::on_alarm, this, std::placeholders::_1));

  system_volume_pub_ = node_->create_publisher<pixmoving_hmi_msgs::msg::SystemVolumeReport>(
    "/app/vehicle/system_volume_report", 10);
  system_volume_timer_ = node_->create_wall_timer(
    2s, std::bind(&PixmovingVehicleDisplayBridgeModule::publish_system_volume, this));
}

void PixmovingVehicleDisplayBridgeModule::setup_forwarders()
{
  create_ipc_to_hmi_forwarder<tier4_vehicle_msgs::msg::ActuationStatusStamped>(
    "/vehicle/status/actuation_status");
  create_ipc_to_hmi_forwarder<autoware_internal_debug_msgs::msg::Float32Stamped>(
    "/localization/pose_estimator/nearest_voxel_transformation_likelihood");
  create_ipc_to_hmi_forwarder<std_msgs::msg::Float32>("/sensing/gnss/chc/heading");
  create_ipc_to_hmi_forwarder<autoware_perception_msgs::msg::PredictedObjects>(
    "/perception/object_recognition/objects");
  create_ipc_to_hmi_forwarder<autoware_vehicle_msgs::msg::ControlModeReport>(
    "/vehicle/status/control_mode");
  create_ipc_to_hmi_forwarder<autoware_vehicle_msgs::msg::GearReport>(
    "/vehicle/status/gear_status");
  create_ipc_to_hmi_forwarder<autoware_vehicle_msgs::msg::SteeringReport>(
    "/vehicle/status/steering_status");
  create_ipc_to_hmi_forwarder<autoware_vehicle_msgs::msg::TurnIndicatorsReport>(
    "/vehicle/status/turn_indicators_status");
  create_ipc_to_hmi_forwarder<autoware_vehicle_msgs::msg::VelocityReport>(
    "/vehicle/status/velocity_status");
  create_ipc_to_hmi_forwarder<autoware_system_msgs::msg::AutowareState>("/autoware/state");
  create_ipc_to_hmi_forwarder<autoware_perception_msgs::msg::TrafficLightGroupArray>(
    "/perception/traffic_light_recognition/traffic_signals");
  create_ipc_to_hmi_forwarder<autoware_planning_msgs::msg::Path>(
    "/planning/path_candidate/start_planner");
  create_ipc_to_hmi_forwarder<autoware_planning_msgs::msg::Trajectory>(
    "/planning/scenario_planning/trajectory");
  create_ipc_to_hmi_forwarder<visualization_msgs::msg::MarkerArray>("/map/vector_map_marker");
  create_ipc_to_hmi_forwarder<sensor_msgs::msg::NavSatFix>("/sensing/gnss/fix");
  create_ipc_to_hmi_forwarder<sensor_msgs::msg::PointCloud2>("/map/pointcloud_map");
  create_ipc_to_hmi_forwarder<pixmoving_hmi_msgs::msg::VehicleInfo>(
    "/app/cloud_control_platform/vehicle_info");
  create_ipc_to_hmi_forwarder<pixmoving_hmi_msgs::msg::AutowareInfo>(
    "/app/cloud_control_platform/autoware_info");
  create_ipc_to_hmi_forwarder<pixmoving_hmi_msgs::msg::SensorInfo>(
    "/app/cloud_control_platform/sensor_info");
  create_ipc_to_hmi_forwarder<pixmoving_hmi_msgs::msg::Alarm>("/communiction/alarm");
  create_ipc_to_hmi_forwarder<pixmoving_hmi_msgs::msg::V2dCurrentStationInfo>(
    "/app/display/current_station_info");
  create_ipc_to_hmi_forwarder<pixmoving_hmi_msgs::msg::V2dAllStationInfo>(
    "/app/display/all_station_info");

  create_hmi_to_ipc_forwarder<autoware_vehicle_msgs::msg::Engage>("hmi_output/autoware/engage");
  create_hmi_to_ipc_forwarder<geometry_msgs::msg::PoseStamped>(
    "hmi_output/planning/mission_planning/goal");
  create_hmi_to_ipc_forwarder<geometry_msgs::msg::PoseWithCovarianceStamped>("hmi_output/initialpose");
  create_hmi_to_ipc_forwarder<pixmoving_hmi_msgs::msg::AppComm>("hmi_output/app_comm");
}

void PixmovingVehicleDisplayBridgeModule::setup_services()
{
  app_control_service_ = node_->create_service<pixmoving_hmi_msgs::srv::AppControl>(
    "/app/app_control",
    std::bind(
      &PixmovingVehicleDisplayBridgeModule::handle_app_control, this, std::placeholders::_1,
      std::placeholders::_2, std::placeholders::_3));

  get_ipc_info_service_ = node_->create_service<pixmoving_hmi_msgs::srv::GetIPCInfo>(
    "/app/get_ipc_info",
    std::bind(
      &PixmovingVehicleDisplayBridgeModule::handle_get_ipc_info, this, std::placeholders::_1,
      std::placeholders::_2, std::placeholders::_3));
}

void PixmovingVehicleDisplayBridgeModule::setup_clients()
{
  door_client_ = node_->create_client<tier4_external_api_msgs::srv::SetDoor>("/api/vehicle/set/door");
  ota_client_ = node_->create_client<pixmoving_hmi_msgs::srv::OtaCmd>("/cloud_control_platform/ota/ota_cmd");
}

void PixmovingVehicleDisplayBridgeModule::on_alarm(const pixmoving_hmi_msgs::msg::Alarm::SharedPtr msg)
{
  std::string prefix;
  for (const auto & range : kAlarmRanges) {
    if (range.start <= static_cast<uint32_t>(msg->code) &&
      static_cast<uint32_t>(msg->code) <= range.end)
    {
      prefix = std::string("[") + range.name + "] ";
      break;
    }
  }
  RCLCPP_INFO(
    node_->get_logger(), "[display_bridge] alarm code=%d level=%d type=%d msg=%s%s ts=%lu",
    msg->code, msg->level, msg->type, prefix.c_str(), msg->msg.c_str(), msg->ts);
}

void PixmovingVehicleDisplayBridgeModule::handle_app_control(
  const std::shared_ptr<rmw_request_id_t>,
  const std::shared_ptr<pixmoving_hmi_msgs::srv::AppControl::Request> request,
  std::shared_ptr<pixmoving_hmi_msgs::srv::AppControl::Response> response)
{
  if (request->recording_data_status) execute_tool("recording_data");
  if (request->building_map) execute_tool("loading_map");

  if (request->export_status) {
    if (request->export_path == request->EXPORT_LOCAL) {
      execute_tool("export_data_to_local");
    } else if (request->export_path == request->EXPORT_CLOUD) {
      execute_tool("export_data_to_cloud");
    } else if (request->export_path == request->EXPORT_SPARE_TIME2) {
      execute_tool("export_spare_time2");
    }
  }

  if (request->loading_map_status) {
    if (request->loading_map_type == request->MAP_PCD) {
      execute_tool("download_pcd_map");
    } else if (request->loading_map_type == request->MAP_OSM) {
      execute_tool("download_osm_map");
    }
  }

  if (request->upload_map_status) {
    if (request->upload_map_type == request->MAP_PCD) {
      execute_tool("upload_pcd_map");
    } else if (request->upload_map_type == request->MAP_OSM) {
      execute_tool("upload_osm_map");
    }
  }

  if (request->log_update_status == request->LOG_DOW) {
    execute_tool("log_dow");
  } else if (request->log_update_status == request->LOG_UP) {
    execute_tool("log_up");
  }

  if (
    request->ota_upgrade_form_app == request->OTA_QUERY ||
    request->ota_upgrade_form_app == request->OTA_START ||
    request->ota_upgrade_form_app == request->OTA_UPGRADE_HMI)
  {
    send_ota_cmd_request(request->ota_upgrade_form_app);
  }

  if (request->system_volume_set >= 0 && request->system_volume_set <= 100) {
    set_system_volume(request->system_volume_set);
    response->res = true;
  } else {
    response->res = false;
  }

  send_set_door_request(request->vehicle_door_status);
  response->success = true;
  response->message = "IPC info retrieved successfully.";
  response->building_map_progress = 75;
  response->ota_upgrade_progress = 30;
  response->system_volume_srv_report = get_system_volume().value_or(-1);
}

void PixmovingVehicleDisplayBridgeModule::handle_get_ipc_info(
  const std::shared_ptr<rmw_request_id_t>,
  const std::shared_ptr<pixmoving_hmi_msgs::srv::GetIPCInfo::Request>,
  std::shared_ptr<pixmoving_hmi_msgs::srv::GetIPCInfo::Response> response)
{
  auto now = node_->get_clock()->now();
  response->timestamp.sec = static_cast<int32_t>(now.seconds());
  response->timestamp.nanosec =
    static_cast<uint32_t>((now.nanoseconds() % 1000000000LL));
  response->vcu_firmware_version = "v1.2.0_20241023_Robo-Bus_a31";
  response->auto_driving_version = get_auto_driving_version();
  response->vehicle_vin = "VIN1HGBH41JXMN20241023_Robo-Bus_a31";
  response->vehicle_name = run_command_capture("hostname");
  if (!response->vehicle_name.empty() && response->vehicle_name.back() == '\n') {
    response->vehicle_name.pop_back();
  }
}

void PixmovingVehicleDisplayBridgeModule::publish_system_volume()
{
  auto volume = get_system_volume();
  if (!volume.has_value()) {
    return;
  }
  pixmoving_hmi_msgs::msg::SystemVolumeReport msg;
  auto now = node_->get_clock()->now();
  msg.timestamp.sec = static_cast<int32_t>(now.seconds());
  msg.timestamp.nanosec =
    static_cast<uint32_t>((now.nanoseconds() % 1000000000LL));
  msg.system_volume_report = *volume;
  system_volume_pub_->publish(msg);
}

std::optional<int> PixmovingVehicleDisplayBridgeModule::get_system_volume() const
{
  if (!has_pactl_) {
    return std::nullopt;
  }
  auto output = run_command_capture("pactl get-sink-volume @DEFAULT_SINK@");
  std::regex pattern(R"((\d+)%)");
  std::smatch match;
  if (std::regex_search(output, match, pattern)) {
    return std::stoi(match[1].str());
  }
  return std::nullopt;
}

void PixmovingVehicleDisplayBridgeModule::set_system_volume(int volume) const
{
  if (!has_pactl_) {
    return;
  }
  std::ostringstream command;
  command << "pactl set-sink-volume @DEFAULT_SINK@ " << volume << "%";
  std::system(command.str().c_str());
}

void PixmovingVehicleDisplayBridgeModule::execute_tool(const std::string & tool_name) const
{
  auto tool_path = tools_path_ + "/" + tool_name;
  if (!file_exists(tool_path)) {
    RCLCPP_WARN(node_->get_logger(), "[display_bridge] tool not found: %s", tool_path.c_str());
    return;
  }
  std::system(tool_path.c_str());
}

std::string PixmovingVehicleDisplayBridgeModule::get_auto_driving_version() const
{
  namespace fs = std::filesystem;
  fs::path dir =
    fs::path(std::getenv("HOME")) / "pix" / "robobus" / "HMI" / ".OTA" / "downloads" / "systems";
  if (!fs::exists(dir)) {
    return "Current software version not found";
  }
  for (const auto & entry : fs::directory_iterator(dir)) {
    if (entry.path().extension() == ".zip") {
      return entry.path().stem().string();
    }
  }
  return "Current software version not found";
}

void PixmovingVehicleDisplayBridgeModule::send_set_door_request(bool open)
{
  if (!door_client_->service_is_ready()) {
    return;
  }
  auto request = std::make_shared<tier4_external_api_msgs::srv::SetDoor::Request>();
  request->open = open;
  using SharedFuture = rclcpp::Client<tier4_external_api_msgs::srv::SetDoor>::SharedFuture;
  door_client_->async_send_request(
    request,
    [this](SharedFuture future) {
      try {
        auto response = future.get();
        RCLCPP_INFO(
          node_->get_logger(), "[display_bridge] SetDoor response code=%d message=%s",
          response->status.code, response->status.message.c_str());
      } catch (const std::exception & e) {
        RCLCPP_ERROR(node_->get_logger(), "[display_bridge] SetDoor request failed: %s", e.what());
      }
    });
}

void PixmovingVehicleDisplayBridgeModule::send_ota_cmd_request(int8_t mode)
{
  if (!ota_client_->service_is_ready()) {
    return;
  }
  auto request = std::make_shared<pixmoving_hmi_msgs::srv::OtaCmd::Request>();
  request->upgrade_mode = mode;
  using SharedFuture = rclcpp::Client<pixmoving_hmi_msgs::srv::OtaCmd>::SharedFuture;
  ota_client_->async_send_request(
    request,
    [this](SharedFuture future) {
      try {
        auto response = future.get();
        RCLCPP_INFO(
          node_->get_logger(), "[display_bridge] OtaCmd response res=%d status=%d", response->res,
          response->status);
      } catch (const std::exception & e) {
        RCLCPP_ERROR(node_->get_logger(), "[display_bridge] OtaCmd request failed: %s", e.what());
      }
    });
}

}  // namespace robobus_hmi_data_relay::bridges
