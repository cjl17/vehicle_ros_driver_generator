#include "pixmoving_chassis_interface/pixmoving_chassis_interface.hpp"

#include <cstdio>
#include <cstring>
#include <fstream>
#include <rclcpp/serialization.hpp>

namespace
{
constexpr std::uint32_t kVehicleInfoTmPtmSnapshotMagic = 0x56495450u;

struct VehicleInfoTmPtmSnapshot
{
  std::uint32_t magic;
  std::int32_t tm;
  std::int32_t ptm;
};
}  // namespace

namespace pixmoving
{
namespace chassis
{
namespace interface
{

bool PixmovingChassisInterfaceNode::loadVehicleInfoSnapshot()
{
  if (vehicle_info_snapshot_path_.empty())
  {
    return false;
  }

  std::ifstream input(vehicle_info_snapshot_path_, std::ios::binary | std::ios::ate);
  if (!input.is_open())
  {
    return false;
  }

  const auto file_size = input.tellg();
  if (file_size <= 0)
  {
    return false;
  }

  std::vector<char> buffer(static_cast<std::size_t>(file_size));
  input.seekg(0, std::ios::beg);
  input.read(buffer.data(), static_cast<std::streamsize>(buffer.size()));
  if (!input.good() && !input.eof())
  {
    RCLCPP_WARN(this->get_logger(), "Failed to read cached VehicleInfo snapshot: %s", vehicle_info_snapshot_path_.c_str());
    return false;
  }

  if (buffer.size() == sizeof(VehicleInfoTmPtmSnapshot))
  {
    VehicleInfoTmPtmSnapshot snapshot{};
    std::memcpy(&snapshot, buffer.data(), sizeof(snapshot));
    if (snapshot.magic == kVehicleInfoTmPtmSnapshotMagic)
    {
      vehicle_info_msg_.tm = snapshot.tm;
      vehicle_info_msg_.ptm = snapshot.ptm;
      fused_power_on_mileage_m_ = std::max(0.0, static_cast<double>(snapshot.ptm));
      last_tm_ = snapshot.tm;
      last_ptm_ = snapshot.ptm;
      return true;
    }
  }

  try
  {
    pixmoving_hmi_msgs::msg::VehicleInfo legacy_vehicle_info;
    rclcpp::Serialization<pixmoving_hmi_msgs::msg::VehicleInfo> serializer;
    rclcpp::SerializedMessage serialized_message(buffer.size());
    auto& rcl_message = serialized_message.get_rcl_serialized_message();
    std::memcpy(rcl_message.buffer, buffer.data(), buffer.size());
    rcl_message.buffer_length = buffer.size();
    serializer.deserialize_message(&serialized_message, &legacy_vehicle_info);

    vehicle_info_msg_.tm = legacy_vehicle_info.tm;
    vehicle_info_msg_.ptm = legacy_vehicle_info.ptm;
    fused_power_on_mileage_m_ = std::max(0.0, static_cast<double>(legacy_vehicle_info.ptm));
    last_tm_ = legacy_vehicle_info.tm;
    last_ptm_ = legacy_vehicle_info.ptm;
    return true;
  }
  catch (const std::exception& exception)
  {
    RCLCPP_WARN(this->get_logger(), "Failed to restore cached VehicleInfo tm/ptm snapshot: %s", exception.what());
    return false;
  }
}

void PixmovingChassisInterfaceNode::saveVehicleInfoSnapshot() const
{
  if (vehicle_info_snapshot_path_.empty())
  {
    return;
  }

  const VehicleInfoTmPtmSnapshot snapshot{
      kVehicleInfoTmPtmSnapshotMagic,
      vehicle_info_msg_.tm,
      vehicle_info_msg_.ptm,
  };

  const std::string tmp_path = vehicle_info_snapshot_path_ + ".tmp";
  std::ofstream output(tmp_path, std::ios::binary | std::ios::trunc);
  if (!output.is_open())
  {
    RCLCPP_WARN(this->get_logger(), "Failed to open VehicleInfo snapshot path: %s", tmp_path.c_str());
    return;
  }

  output.write(reinterpret_cast<const char*>(&snapshot), static_cast<std::streamsize>(sizeof(snapshot)));
  output.close();

  if (!output.good())
  {
    RCLCPP_WARN(this->get_logger(), "Failed to write VehicleInfo snapshot: %s", tmp_path.c_str());
    return;
  }

  if (std::rename(tmp_path.c_str(), vehicle_info_snapshot_path_.c_str()) != 0)
  {
    RCLCPP_WARN(this->get_logger(), "Failed to update VehicleInfo snapshot file: %s", vehicle_info_snapshot_path_.c_str());
  }
}

void PixmovingChassisInterfaceNode::markVehicleInfoLiveSource(std::uint32_t source_bit)
{
  vehicle_info_live_source_mask_ |= source_bit;
}

bool PixmovingChassisInterfaceNode::canPublishVehicleInfo() const
{
  return vehicle_info_snapshot_loaded_ ||
         (vehicle_info_live_source_mask_ & kVehicleInfoReadyMask) == kVehicleInfoReadyMask;
}

PixmovingChassisInterfaceNode::PixmovingChassisInterfaceNode(const rclcpp::NodeOptions& node_options)
  : Node("pixmoving_chassis_interface", node_options)
{
  // 初始化参数
  initParameters();
  // 初始化订阅
  initSubscriptions();
  // 初始化发布
  initPublishers();
  // 初始化定时器
  initTimers();

  // 加载站点并发布一次所有站点信息
  publishAllStationInfo();

  // 打印初始化完成
  RCLCPP_INFO_STREAM(this->get_logger(), "PixmovingChassisInterfaceNode initialized");
}

PixmovingChassisInterfaceNode::~PixmovingChassisInterfaceNode()
{
}

void PixmovingChassisInterfaceNode::initParameters()
{
  // 初始化参数
  localization_pose_received_time_ = this->now();
  emergency_report_received_time_ = this->now();
  mission_remaining_distance_time_received_time_ = this->now();
  operation_mode_state_ptr_ = std::make_shared<const autoware_adapi_v1_msgs::msg::OperationModeState>();

  vehicle_info_msg_.acc = -1;
  vehicle_info_msg_.gear = -1;
  vehicle_info_msg_.door = -1;
  vehicle_info_msg_.head_light = -1;
  vehicle_info_msg_.turn_light = -1;
  vehicle_info_msg_.in_lights = -1;
  vehicle_info_msg_.out_mood_lights = -1;
  vehicle_info_msg_.win = -1;
  vehicle_info_msg_.tm = -1;
  vehicle_info_msg_.ptm = -1;
  vehicle_info_msg_.rm = -1;
  vehicle_info_msg_.ste = -1;
  vehicle_info_msg_.brk = -1;
  vehicle_info_msg_.thr = -1;
  vehicle_info_msg_.air_con = -1;
  vehicle_info_msg_.in_temp = -100;
  vehicle_info_msg_.out_temp = -100;
  vehicle_info_msg_.smoke = -1;
  vehicle_info_msg_.co2 = -1;
  vehicle_info_msg_.seatbelt = -1;
  vehicle_info_msg_.spd = -1;
  vehicle_info_msg_.spd_l = -1;
  vehicle_info_msg_.p_l = -1;
  vehicle_info_msg_.p_v = -1;
  vehicle_info_msg_.p_c = -1;
  vehicle_info_msg_.p_ch = -1;
  vehicle_info_msg_.bat = -1;
  vehicle_info_msg_.mode = -1;
  vehicle_info_msg_.rc = -1;
  vehicle_info_msg_.aeb_status = 0;  // 默认未触发
  vehicle_info_msg_.seat_sta.assign(6, 0x22);
  vehicle_info_msg_.belt_sta.assign(6, 0x22);
  vehicle_info_msg_.seat_number.assign(6, -1);
  last_vehicle_info_snapshot_save_time_ = this->now();

  // 初始化里程边沿打印的历史值（与 VehicleInfo 初值保持一致）
  last_tm_ = vehicle_info_msg_.tm;
  last_ptm_ = vehicle_info_msg_.ptm;

  last_current_target_station_.x = 8;
  last_current_target_station_.y = 8;
  last_current_target_station_.z = 8;
  // paramter

  auto station_yaml_file_path = this->declare_parameter<std::string>("station_yaml_file_path", "");
  vehicle_info_snapshot_path_ = this->declare_parameter<std::string>(
      "vehicle_info_snapshot_path", "/tmp/pixmoving_chassis_interface_vehicle_info.bin");
  enable_fused_ptm_ = this->declare_parameter<bool>("enable_fused_ptm", true);
  ndt_pos_q_threshold_ = this->declare_parameter<double>("ndt_pos_q_threshold", 2.3);
  ndt_timeout_sec_ = this->declare_parameter<double>("ndt_timeout_sec", 1.0);
  gnss_timeout_sec_ = this->declare_parameter<double>("gnss_timeout_sec", 1.0);
  chassis_speed_timeout_sec_ = this->declare_parameter<double>("chassis_speed_timeout_sec", 0.5);
  standstill_speed_threshold_mps_ =
      this->declare_parameter<double>("standstill_speed_threshold_mps", 0.2);
  ndt_jump_reject_threshold_m_ =
      this->declare_parameter<double>("ndt_jump_reject_threshold_m", 5.0);
  gnss_jump_reject_threshold_m_ =
      this->declare_parameter<double>("gnss_jump_reject_threshold_m", 20.0);
  max_delta_ratio_ = this->declare_parameter<double>("max_delta_ratio", 2.5);
  raw_trip_sync_threshold_m_ =
      this->declare_parameter<double>("raw_trip_sync_threshold_m", 12.0);
  gnss_warmup_frames_ = this->declare_parameter<int>("gnss_warmup_frames", 3);
  estop_done_distance_threshold_m_ =
      this->declare_parameter<double>("estop_done_distance_threshold_m", 100.0);
  estop_done_hold_sec_ =
      this->declare_parameter<double>("estop_done_hold_sec", 0.5);
  // 声明并读取状态机驾驶模式参数
  this->declare_parameter("use_state_machine_drive_mode", true);
  use_state_machine_drive_mode_ = this->get_parameter("use_state_machine_drive_mode").as_bool();

  this->declare_parameter<double>("jerk_uncomfortable_threshold", 1.0);
  this->declare_parameter<double>("accel_limit", 3.0);
  this->declare_parameter<double>("comfort_jerk_clear_threshold", 0.8);
  this->declare_parameter<double>("comfort_accel_clear_limit", 2.4);
  this->declare_parameter<int>("comfort_bad_count_threshold", 3);
  this->declare_parameter<int>("comfort_good_count_threshold", 5);
  this->declare_parameter<double>("comfort_min_event_duration_sec", 0.5);
  this->declare_parameter<double>("near_miss_trigger_accel", 3.0);
  this->declare_parameter<double>("near_miss_clear_accel", 2.0);
  this->declare_parameter<double>("imu_timeout_sec", 1.0);
  this->declare_parameter<double>("stability_mean_limit", 0.3);
  this->declare_parameter<double>("frechet_limit", 0.5);
  this->declare_parameter<double>("local_disp_limit", 0.15);
  this->declare_parameter<double>("lookahead_max_limit", 0.5);
  this->declare_parameter<double>("stability_mean_clear_limit", 0.24);
  this->declare_parameter<double>("frechet_clear_limit", 0.4);
  this->declare_parameter<double>("local_disp_clear_limit", 0.12);
  this->declare_parameter<double>("lookahead_max_clear_limit", 0.4);
  this->declare_parameter<int>("stability_bad_count_threshold", 3);
  this->declare_parameter<int>("stability_good_count_threshold", 10);
  this->declare_parameter<double>("stability_min_event_duration_sec", 0.5);
  this->declare_parameter<bool>("stability_require_autonomous_mode", true);
  this->declare_parameter<bool>("stability_suppress_when_stopped", true);
  this->declare_parameter<double>("stability_standstill_speed_threshold_mps", 0.2);
  this->declare_parameter<bool>("stability_require_route_lane", true);
  this->declare_parameter<bool>("stability_require_auto_executing_mode", true);
  this->declare_parameter<bool>("comfort_require_auto_executing_mode", true);
  this->declare_parameter<bool>("comfort_suppress_on_brake_pedal", true);
  this->declare_parameter<double>("comfort_brake_release_suppression_sec", 10.0);
  // 舒适性相关
  thresholds_.jerk_uncomfortable_threshold = this->get_parameter("jerk_uncomfortable_threshold").as_double();
  thresholds_.accel_limit = this->get_parameter("accel_limit").as_double();
  thresholds_.comfort_jerk_clear_threshold = this->get_parameter("comfort_jerk_clear_threshold").as_double();
  thresholds_.comfort_accel_clear_limit = this->get_parameter("comfort_accel_clear_limit").as_double();
  thresholds_.comfort_bad_count_threshold = this->get_parameter("comfort_bad_count_threshold").as_int();
  thresholds_.comfort_good_count_threshold = this->get_parameter("comfort_good_count_threshold").as_int();
  thresholds_.comfort_min_event_duration_sec = this->get_parameter("comfort_min_event_duration_sec").as_double();
  thresholds_.near_miss_trigger_accel = this->get_parameter("near_miss_trigger_accel").as_double();
  thresholds_.near_miss_clear_accel = this->get_parameter("near_miss_clear_accel").as_double();
  thresholds_.imu_timeout_sec = this->get_parameter("imu_timeout_sec").as_double();
  // 稳定性相关
  thresholds_.stability_mean_limit = this->get_parameter("stability_mean_limit").as_double();
  thresholds_.frechet_limit = this->get_parameter("frechet_limit").as_double();
  thresholds_.local_disp_limit = this->get_parameter("local_disp_limit").as_double();
  thresholds_.lookahead_max_limit = this->get_parameter("lookahead_max_limit").as_double();
  thresholds_.stability_mean_clear_limit = this->get_parameter("stability_mean_clear_limit").as_double();
  thresholds_.frechet_clear_limit = this->get_parameter("frechet_clear_limit").as_double();
  thresholds_.local_disp_clear_limit = this->get_parameter("local_disp_clear_limit").as_double();
  thresholds_.lookahead_max_clear_limit = this->get_parameter("lookahead_max_clear_limit").as_double();
  thresholds_.stability_bad_count_threshold = this->get_parameter("stability_bad_count_threshold").as_int();
  thresholds_.stability_good_count_threshold = this->get_parameter("stability_good_count_threshold").as_int();
  thresholds_.stability_min_event_duration_sec = this->get_parameter("stability_min_event_duration_sec").as_double();
  thresholds_.stability_require_autonomous_mode = this->get_parameter("stability_require_autonomous_mode").as_bool();
  thresholds_.stability_suppress_when_stopped = this->get_parameter("stability_suppress_when_stopped").as_bool();
  thresholds_.stability_standstill_speed_threshold_mps =
      this->get_parameter("stability_standstill_speed_threshold_mps").as_double();
  thresholds_.stability_require_route_lane = this->get_parameter("stability_require_route_lane").as_bool();
  thresholds_.stability_require_auto_executing_mode =
      this->get_parameter("stability_require_auto_executing_mode").as_bool();
  thresholds_.comfort_require_auto_executing_mode =
      this->get_parameter("comfort_require_auto_executing_mode").as_bool();
  thresholds_.comfort_suppress_on_brake_pedal =
      this->get_parameter("comfort_suppress_on_brake_pedal").as_bool();
  thresholds_.comfort_brake_release_suppression_sec =
      this->get_parameter("comfort_brake_release_suppression_sec").as_double();

  // 根据参数初始化状态机
  if (use_state_machine_drive_mode_)
  {
    // 创建状态机管理器
    drive_mode_manager_ = std::make_unique<DriveModeManager>(this->get_logger());

    RCLCPP_WARN(this->get_logger(), "=================================================================");
    RCLCPP_WARN(this->get_logger(), "  Using HFSM2 STATE MACHINE for drive mode logic");
    RCLCPP_WARN(this->get_logger(), "  Features:");
    RCLCPP_WARN(this->get_logger(), "  - 13 states with clear transitions");
    RCLCPP_WARN(this->get_logger(), "  - No state override issues");
    RCLCPP_WARN(this->get_logger(), "  - Easy to maintain and extend");
    RCLCPP_WARN(this->get_logger(), "  - Publishing to /drive_mode/state_machine topic");
    RCLCPP_WARN(this->get_logger(), "  - State visualization support");
    RCLCPP_WARN(this->get_logger(), "  Original logic is preserved and can be restored by setting");
    RCLCPP_WARN(this->get_logger(), "  parameter 'use_state_machine_drive_mode' to false");
    RCLCPP_WARN(this->get_logger(), "=================================================================");
  }
  else
  {
    RCLCPP_INFO(this->get_logger(), "Using ORIGINAL drive mode logic (state machine disabled)");
    RCLCPP_INFO(this->get_logger(), "To enable state machine, set parameter 'use_state_machine_drive_mode' to true");
  }

  // 初始化规划指标监控器
  planning_metrics_monitor_ = std::make_unique<PlanningMetricsMonitor>(this);

  planning_metrics_monitor_->setThresholds(thresholds_);

  // Read station YAML file
  this->readStationYamlFile(station_yaml_file_path);
  v2d_current_station_info_msg_.current_station.id = 0;
  v2d_current_station_info_msg_.current_station.name = "";
  v2d_current_station_info_msg_.target_station.id = 0;
  v2d_current_station_info_msg_.target_station.name = "";

  vehicle_info_snapshot_loaded_ = loadVehicleInfoSnapshot();
  if (vehicle_info_snapshot_loaded_)
  {
    RCLCPP_WARN(this->get_logger(), "Restored cached VehicleInfo snapshot from %s", vehicle_info_snapshot_path_.c_str());
  }

  if (enable_fused_ptm_ && !vehicle_info_snapshot_loaded_)
  {
    fused_power_on_mileage_m_ = 0.0;
  }
  pending_raw_trip_sync_ = true;
}

void PixmovingChassisInterfaceNode::initSubscriptions()
{
  // 初始化订阅
  // 在多线程容器里强制串行执行本组件的所有回调，先消除共享状态并发访问。
  serialized_callback_group_ = this->create_callback_group(
      rclcpp::CallbackGroupType::MutuallyExclusive);

  // Autoware / planning 相关订阅
  {
    rclcpp::SubscriptionOptions options;
    options.callback_group = serialized_callback_group_;

    plan_goal_sub_ = this->create_subscription<geometry_msgs::msg::PoseStamped>(
        topics::PLANNING_GOAL, 1, std::bind(&PixmovingChassisInterfaceNode::onPlanGoal, this, std::placeholders::_1),
        options);

    localization_pose_sub_ = this->create_subscription<geometry_msgs::msg::PoseStamped>(
        topics::LOCALIZATION_POSE, 1,
        std::bind(&PixmovingChassisInterfaceNode::onLocalizationPose, this, std::placeholders::_1), options);

    // autoware_state_sub_ = this->create_subscription<autoware_system_msgs::msg::AutowareState>(
    //     topics::AUTOWARE_STATE, 10,
    //     std::bind(&PixmovingChassisInterfaceNode::onAutowareState, this, std::placeholders::_1), options);

    // Autoware 状态订阅 - 根据参数选择使用哪个版本
    if (use_state_machine_drive_mode_)
    {
      // 使用状态机版本
      autoware_state_sub_ = this->create_subscription<autoware_system_msgs::msg::AutowareState>(
          topics::AUTOWARE_STATE, rclcpp::QoS(10),
          std::bind(&PixmovingChassisInterfaceNode::onAutowareStateWithStateMachine, this, std::placeholders::_1),
          options);

      RCLCPP_INFO(this->get_logger(), "Subscribed to Autoware state (STATE MACHINE version)");
    }
    else
    {
      // 使用原版本（保持向后兼容）
      autoware_state_sub_ = this->create_subscription<autoware_system_msgs::msg::AutowareState>(
          topics::AUTOWARE_STATE, rclcpp::QoS(10),
          std::bind(&PixmovingChassisInterfaceNode::onAutowareState, this, std::placeholders::_1), options);

      RCLCPP_INFO(this->get_logger(), "Subscribed to Autoware state (ORIGINAL version)");
    }

    velocity_limit_sub_ = this->create_subscription<autoware_internal_planning_msgs::msg::VelocityLimit>(
        topics::VELOCITY_LIMIT, rclcpp::QoS(1).transient_local(),
        std::bind(&PixmovingChassisInterfaceNode::onVelocityLimit, this, std::placeholders::_1), options);

    mission_remaining_distance_time_sub_ =
        this->create_subscription<autoware_internal_msgs::msg::MissionRemainingDistanceTime>(
            topics::MISSION_REMAINING_DISTANCE_TIME, 10,
            std::bind(&PixmovingChassisInterfaceNode::onMissionRemainingDistanceTime, this, std::placeholders::_1),
            options);

    planner_route_sub_ = this->create_subscription<autoware_planning_msgs::msg::LaneletRoute>(
        topics::PLANNING_ROUTE, rclcpp::QoS(1).transient_local(),
        std::bind(&PixmovingChassisInterfaceNode::onLaneletRoute, this, std::placeholders::_1), options);

    velocity_report_sub_ = this->create_subscription<autoware_vehicle_msgs::msg::VelocityReport>(
        topics::VEHICLE_VELOCITY_REPORT, 1,
        std::bind(&PixmovingChassisInterfaceNode::onVelocityReport, this, std::placeholders::_1), options);

    local_transform_probability_sub_ = this->create_subscription<autoware_internal_debug_msgs::msg::Float32Stamped>(
        topics::LOCAL_TRANSFORM_PROBABILITY, 1,
        std::bind(&PixmovingChassisInterfaceNode::onLocalTransformProbability, this, std::placeholders::_1), options);

    emergency_report_sub_ = this->create_subscription<tier4_external_api_msgs::msg::Emergency>(
        topics::EMERGENCY_STATE, rclcpp::QoS(2),
        std::bind(&PixmovingChassisInterfaceNode::onEmergency, this, std::placeholders::_1), options);

    operation_mode_state_sub_ = this->create_subscription<autoware_adapi_v1_msgs::msg::OperationModeState>(
        topics::OPERATION_MODE_STATE, rclcpp::QoS(2),
        std::bind(&PixmovingChassisInterfaceNode::onOperationModeState, this, std::placeholders::_1), options);

    control_mode_report_sub_ = this->create_subscription<autoware_vehicle_msgs::msg::ControlModeReport>(
        topics::CONTROL_MODE_REPORT, rclcpp::QoS(1),
        std::bind(&PixmovingChassisInterfaceNode::onControlModeReport, this, std::placeholders::_1), options);
  }

  // 传感器相关订阅
  {
    rclcpp::SubscriptionOptions options;
    options.callback_group = serialized_callback_group_;

    sub_nav_sat_fix_report_ = this->create_subscription<sensor_msgs::msg::NavSatFix>(
        topics::GNSS_FIX, 1, std::bind(&PixmovingChassisInterfaceNode::onNavSatFix, this, std::placeholders::_1),
        options);

    sub_heading_report_ = this->create_subscription<std_msgs::msg::Float32>(
        topics::GNSS_HEADING, 1, std::bind(&PixmovingChassisInterfaceNode::onHeading, this, std::placeholders::_1),
        options);

    sub_satellites_number1_ = this->create_subscription<std_msgs::msg::UInt8>(
        topics::GNSS_MAIN_ANTENNA_SATELLITE_COUNT, 1,
        std::bind(&PixmovingChassisInterfaceNode::onSatellitesNumber1, this, std::placeholders::_1), options);

    sub_satellites_number2_ = this->create_subscription<std_msgs::msg::UInt8>(
        topics::GNSS_AUX_ANTENNA_SATELLITE_COUNT, 1,
        std::bind(&PixmovingChassisInterfaceNode::onSatellitesNumber2, this, std::placeholders::_1), options);
  }

  // Pix Robobus driver / 底盘相关订阅
  {
    rclcpp::SubscriptionOptions options;
    options.callback_group = serialized_callback_group_;

    BcmMessage4_sub_ = this->create_subscription<pix_robobus_driver_msgs::msg::BcmMessage4>(
        topics::BCM_MESSAGE4, rclcpp::QoS(1),
        std::bind(&PixmovingChassisInterfaceNode::onBcmMessage4, this, std::placeholders::_1), options);

    BcmMessage5_sub_ = this->create_subscription<pix_robobus_driver_msgs::msg::BcmMessage5>(
        topics::BCM_MESSAGE5, rclcpp::QoS(1),
        std::bind(&PixmovingChassisInterfaceNode::onBcmMessage5, this, std::placeholders::_1), options);

    VaDriveStaFb_sub_ = this->create_subscription<pix_robobus_driver_msgs::msg::VaDriveStaFb>(
        topics::VA_DRIVE_STA_FB, rclcpp::QoS(1),
        std::bind(&PixmovingChassisInterfaceNode::onVaDriveStaFb, this, std::placeholders::_1), options);

    VaBrakeStaFb_sub_ = this->create_subscription<pix_robobus_driver_msgs::msg::VaBrakeStaFb>(
        topics::VA_BRAKE_STA_FB, rclcpp::QoS(1),
        std::bind(&PixmovingChassisInterfaceNode::onVaBrakeStaFb, this, std::placeholders::_1), options);

    VaSteerStaFb_sub_ = this->create_subscription<pix_robobus_driver_msgs::msg::VaSteerStaFb>(
        topics::VA_STEER_STA_FB, rclcpp::QoS(1),
        std::bind(&PixmovingChassisInterfaceNode::onVaSteerStaFb, this, std::placeholders::_1), options);

    VaVehicleWorkStaFb_sub_ = this->create_subscription<pix_robobus_driver_msgs::msg::VaVehicleWorkStaFb>(
        topics::VA_VEHICLE_WORK_STA_FB, rclcpp::QoS(1),
        std::bind(&PixmovingChassisInterfaceNode::onVaVehicleWorkStaFb, this, std::placeholders::_1), options);

    VaPowerStaFb_sub_ = this->create_subscription<pix_robobus_driver_msgs::msg::VaPowerStaFb>(
        topics::VA_POWER_STA_FB, rclcpp::QoS(1),
        std::bind(&PixmovingChassisInterfaceNode::onVaPowerStaFb, this, std::placeholders::_1), options);

    VaVehicleStaFb_sub_ = this->create_subscription<pix_robobus_driver_msgs::msg::VaVehicleStaFb>(
        topics::VA_VEHICLE_STA_FB, rclcpp::QoS(1),
        std::bind(&PixmovingChassisInterfaceNode::onVaVehicleStaFb, this, std::placeholders::_1), options);

    VaChassisOdoFb_sub_ = this->create_subscription<pix_robobus_driver_msgs::msg::VaChassisOdoFb>(
        topics::VA_CHASSIS_ODO_FB, rclcpp::QoS(1),
        std::bind(&PixmovingChassisInterfaceNode::onVaChassisOdoFb, this, std::placeholders::_1), options);

    VaChassisWheelTirePressFb_sub_ = this->create_subscription<pix_robobus_driver_msgs::msg::VaChassisWheelTirePressFb>(
        topics::VA_CHASSIS_WHEEL_TIRE_PRESS_FB, rclcpp::QoS(1),
        std::bind(&PixmovingChassisInterfaceNode::onVaChassisWheelTirePressFb, this, std::placeholders::_1), options);

    VinResp1_sub_ = this->create_subscription<pix_robobus_driver_msgs::msg::VinResp1>(
        topics::VIN_RESP1, rclcpp::QoS(1),
        std::bind(&PixmovingChassisInterfaceNode::onVinResp1, this, std::placeholders::_1), options);

    VinResp2_sub_ = this->create_subscription<pix_robobus_driver_msgs::msg::VinResp2>(
        topics::VIN_RESP2, rclcpp::QoS(1),
        std::bind(&PixmovingChassisInterfaceNode::onVinResp2, this, std::placeholders::_1), options);

    VinResp3_sub_ = this->create_subscription<pix_robobus_driver_msgs::msg::VinResp3>(
        topics::VIN_RESP3, rclcpp::QoS(1),
        std::bind(&PixmovingChassisInterfaceNode::onVinResp3, this, std::placeholders::_1), options);

    VcuTransfer_sub_ = this->create_subscription<pix_robobus_driver_msgs::msg::VcuTransfer>(
        topics::VCU_TRANSFER, rclcpp::QoS(1),
        std::bind(&PixmovingChassisInterfaceNode::onVcuTransfer, this, std::placeholders::_1), options);

    VcuSoftVer_sub_ = this->create_subscription<pix_robobus_driver_msgs::msg::VcuSoftVer>(
        topics::VCU_SOFT_VER, rclcpp::QoS(1),
        std::bind(&PixmovingChassisInterfaceNode::onVcuSoftVer, this, std::placeholders::_1), options);

    VehicleErrcode1_sub_ = this->create_subscription<pix_robobus_driver_msgs::msg::VehicleErrcode1>(
        topics::VEHICLE_ERRCODE1, rclcpp::QoS(1),
        std::bind(&PixmovingChassisInterfaceNode::onVehicleErrcode1, this, std::placeholders::_1), options);

    AebInfoReport_sub_ = this->create_subscription<aeb_interfaces::msg::AebInfoReport>(
        topics::AEB_INFO_REPORT, rclcpp::QoS(10),
        std::bind(&PixmovingChassisInterfaceNode::onAebInfoReport, this, std::placeholders::_1), options);

    AebInfoShadow_sub_ = this->create_subscription<aeb_interfaces::msg::AebInfoShadow>(
    topics::AEB_INFO_SHADOW, rclcpp::QoS(10),
    std::bind(&PixmovingChassisInterfaceNode::onAebInfoShadow, this, std::placeholders::_1), options);
  }
}

void PixmovingChassisInterfaceNode::initPublishers()
{
  // 初始化发布
  // ROS Client
  this->planner_length_client_ = this->create_client<get_osm_info_msgs::srv::GetPrimitiveLength>(
      services::GET_PRIMITIVE_LENGTH, rmw_qos_profile_services_default, serialized_callback_group_);
  this->route_stations_client_ = this->create_client<get_osm_info_msgs::srv::GetRouteStations>(
      services::GET_ROUTE_STATIONS, rmw_qos_profile_services_default, serialized_callback_group_);
  // ROS Publisher
  this->v2d_vehicle_info_pub_ =
      this->create_publisher<pixmoving_hmi_msgs::msg::V2dVehicleInfo>(pub_topics::V2D_VEHICLE_INFO, 5);
  this->all_station_info_pub_ = this->create_publisher<pixmoving_hmi_msgs::msg::V2dAllStationInfo>(
      pub_topics::ALL_STATION_INFO, rclcpp::QoS(1).transient_local());
  this->current_station_info_pub_ = this->create_publisher<pixmoving_hmi_msgs::msg::V2dCurrentStationInfo>(
      pub_topics::CURRENT_STATION_INFO, rclcpp::QoS(1).transient_local());
  this->task_semantic_status_pub_ = this->create_publisher<pixmoving_hmi_msgs::msg::TaskSemanticStatus>(
      pub_topics::TASK_SEMANTIC_STATUS, rclcpp::QoS(1).transient_local());
  this->vehicle_info_pub_ =
      this->create_publisher<pixmoving_hmi_msgs::msg::VehicleInfo>(pub_topics::VEHICLE_STATUS, rclcpp::QoS(5));
  this->sensor_info_pub_ =
      this->create_publisher<pixmoving_hmi_msgs::msg::SensorInfo>(pub_topics::SENSOR_INFO, rclcpp::QoS(1));
  this->autoware_info_pub_ =
      this->create_publisher<pixmoving_hmi_msgs::msg::AutowareInfo>(pub_topics::AUTOWARE_STATE_INFO, rclcpp::QoS(1));
  this->nearby_finish_pub_ = this->create_publisher<std_msgs::msg::UInt8>(pub_topics::NEARBY_FINISH, rclcpp::QoS(1));
}

void PixmovingChassisInterfaceNode::initTimers()
{
  // 初始化定时器
  auto loop_rate = this->declare_parameter<float>("loop_rate", 10.0);
  timer_ = this->create_wall_timer(
      rclcpp::Rate(loop_rate).period(),
      std::bind(&PixmovingChassisInterfaceNode::onTimer, this),
      serialized_callback_group_);
}

void PixmovingChassisInterfaceNode::onTimer()
{
  // 定时器回调的实现
  all_station_info_pub_->publish(v2d_all_station_info_msg_);
  v2d_vehicle_info_pub_->publish(v2d_vehicle_info_msg_);
  sensor_info_pub_->publish(sensor_info_msg_);
  autoware_info_pub_->publish(autoware_info_msg_);
  refreshTaskSemanticStatusSummary();
  task_semantic_status_pub_->publish(task_semantic_status_msg_);
  updateFusedPowerOnMileage();

  if (canPublishVehicleInfo())
  {
    vehicle_info_pub_->publish(vehicle_info_msg_);

    if ((vehicle_info_live_source_mask_ & kVehicleInfoReadyMask) == kVehicleInfoReadyMask &&
        (this->now() - last_vehicle_info_snapshot_save_time_).seconds() >= 2.0)
    {
      saveVehicleInfoSnapshot();
      last_vehicle_info_snapshot_save_time_ = this->now();
      vehicle_info_snapshot_loaded_ = true;
    }
  }
  else
  {
    RCLCPP_WARN_THROTTLE(this->get_logger(), *this->get_clock(), 5000,
                         "VehicleInfo is not ready yet, suppressing placeholder publish");
  }

  const rclcpp::Time current_time = this->now();
  const double localization_pose_delta_time_s = (current_time - localization_pose_received_time_).seconds();

  if (localization_pose_delta_time_s > 1 || localization_pose_ptr_ == nullptr)
  {
    RCLCPP_ERROR_THROTTLE(this->get_logger(), *this->get_clock(), std::chrono::milliseconds(60000).count(),
                          "车辆定位数据过时%f", localization_pose_delta_time_s);
    return;
  }

  if (old_localization_pose_ptr_ == nullptr)
  {
    old_localization_pose_ptr_ = std::make_shared<geometry_msgs::msg::PoseStamped>(*localization_pose_ptr_);
    return;
  }

  rclcpp::Time old_time(old_localization_pose_ptr_->header.stamp);
  rclcpp::Time curr_time(localization_pose_ptr_->header.stamp);

  auto delta_time_s = (curr_time - old_time).seconds();
  if (delta_time_s > 1.0)
  {  // 两个定位数据时间差大于1s
    double x1 = old_localization_pose_ptr_->pose.position.x;
    double y1 = old_localization_pose_ptr_->pose.position.y;
    double z1 = old_localization_pose_ptr_->pose.position.z;

    double x2 = localization_pose_ptr_->pose.position.x;
    double y2 = localization_pose_ptr_->pose.position.y;
    double z2 = localization_pose_ptr_->pose.position.z;

    double distance = std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2) + std::pow(z2 - z1, 2));
    travel_distance_ = travel_distance_ + distance;
    old_localization_pose_ptr_ = std::make_shared<geometry_msgs::msg::PoseStamped>(*localization_pose_ptr_);
  }
}

}  // namespace interface
}  // namespace chassis
}  // namespace pixmoving

#include <rclcpp_components/register_node_macro.hpp>
RCLCPP_COMPONENTS_REGISTER_NODE(pixmoving::chassis::interface::PixmovingChassisInterfaceNode)
