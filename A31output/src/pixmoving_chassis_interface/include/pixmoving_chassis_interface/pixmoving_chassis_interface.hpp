#pragma once

#include "pixmoving_chassis_interface/chassis_interface_common.hpp"
#include "pixmoving_chassis_interface/drive_mode_state_machine.hpp"
#include "pixmoving_chassis_interface/planning_metrics_monitor.hpp"
#include <cstdint>
#include <limits>

namespace pixmoving
{
namespace chassis
{
namespace interface
{

/// @brief ROS 2 组件节点，对外提供车身/底盘状态给 HMI。
/// 订阅 Autoware 与车辆 CAN 话题，转换为 Pixmoving 专用消息，
/// 并发布整合的车辆状态与站点信息供前端展示。
class PixmovingChassisInterfaceNode : public rclcpp::Node
{
public:
  /// @brief 使用给定的 NodeOptions 构造节点。
  explicit PixmovingChassisInterfaceNode(const rclcpp::NodeOptions& node_options);

  /// @brief 析构函数。
  ~PixmovingChassisInterfaceNode();

private:
  enum class MileageSource : std::uint8_t
  {
    NONE = 0,
    NDT = 1,
    GNSS = 2,
    CHASSIS_SPEED = 3,
  };

  // helper functions
  /// @brief 从 YAML 文件加载站点列表。
  void readStationYamlFile(const std::string station_yaml_file_path);
  /// @brief 将全部站点信息发布到可视化话题。
  void publishAllStationInfo();
  /// @brief 比较两个四元数的偏航差是否在阈值内。
  bool calculateAngleBetweenQuaternions(const std::array<double, 4>& q1, const std::array<double, 4>& q2);
  /// @brief 检查两 3D 点距离是否小于阈值。
  bool calculateTwoPointsDistance(const std::array<double, 3>& p1, const std::array<double, 3>& p2);
  /// @brief 根据路由信息匹配站点索引。
  int8_t matchStationIndex(const geometry_msgs::msg::Pose route, const std::string info);
  /// @brief 根据距离与偏航阈值匹配最近站点。
  int8_t matchStationWithDistanceAndAngle(const geometry_msgs::msg::Pose& pose);
  /// @brief 判断当前任务是否到达目标。
  void isTaskGoal();
  void populateStationMsgFromYamlIndex(
      int station_index, const std::string& station_name, pixmoving_hmi_msgs::msg::Station& station_msg);
  void setDisplayStationsFromIndexes(
      int current_index, const std::string& current_name, int target_index, const std::string& target_name);
  void latchTaskSemantic(
      int current_index, const std::string& current_name, int target_index, const std::string& target_name);
  void applyLatchedTaskStationsToDisplay();
  bool shouldTreatAsNewTask(int route_target_station_index);
  void markTaskTerminal();
  void updateTaskSemanticStatusDebug(
      const std::string& lifecycle, const std::string& decision, const std::string& source,
      int inferred_current_index, const std::string& inferred_current_name,
      int inferred_target_index, const std::string& inferred_target_name, bool triggered_new_task_event);
  void refreshTaskSemanticStatusSummary();
  void updateRemainingDistanceAndEstimateTime();
  bool shouldRefreshRemainingDistanceForMode(DriveMode mode) const;

  /// @brief 初始化参数
  void initParameters();
  /// @brief 初始化订阅
  void initSubscriptions();
  /// @brief 初始化发布
  void initPublishers();
  /// @brief 初始化定时器
  void initTimers();
  /// @brief 初始化 PixRobobus 驱动（CAN）相关订阅。
  void initPixRobobusDriver();
  bool loadVehicleInfoSnapshot();
  void saveVehicleInfoSnapshot() const;
  void markVehicleInfoLiveSource(std::uint32_t source_bit);
  bool canPublishVehicleInfo() const;
  void updateFusedPowerOnMileage();
  MileageSource chooseMileageSource() const;
  bool isNdtReliable() const;
  bool isGnssReliable() const;
  bool isChassisSpeedReliable() const;
  void accumulateFromNdt();
  void accumulateFromGnss();
  void accumulateFromChassisSpeed();
  void resetMileageAnchorForSource(MileageSource source);
  void syncPowerCycleResetByRawTrip();
  bool shouldAcceptMileageDelta(double delta_m, double delta_time_s, double jump_threshold_m) const;
  double calcHaversineMeters(
      const sensor_msgs::msg::NavSatFix& from, const sensor_msgs::msg::NavSatFix& to) const;
  const char* mileageSourceToString(MileageSource source) const;

  // timer
  /// @brief 周期执行：发布状态并检查任务。
  void onTimer();

  // callbacks
  /// @brief 路由更新回调。
  void onLaneletRoute(const autoware_planning_msgs::msg::LaneletRoute::SharedPtr msg);
  /// @brief Autoware 操作模式（接管/解除）更新。
  void onOperationModeState(const autoware_adapi_v1_msgs::msg::OperationModeState::SharedPtr msg);
  /// @brief 规划速度上限更新。
  void onVelocityLimit(const autoware_internal_planning_msgs::msg::VelocityLimit::SharedPtr msg);
  /// @brief 任务剩余距离和时间更新。
  void onMissionRemainingDistanceTime(const autoware_internal_msgs::msg::MissionRemainingDistanceTime::SharedPtr msg);
  /// @brief 定位姿态更新。
  void onLocalizationPose(const geometry_msgs::msg::PoseStamped::SharedPtr msg);
  /// @brief 任务目标更新。
  void onPlanGoal(const geometry_msgs::msg::PoseStamped::SharedPtr msg);
  /// @brief 紧急状态（急停）更新。
  void onEmergency(const tier4_external_api_msgs::msg::Emergency::SharedPtr msg);
  /// @brief Autoware 高层状态更新。
  void onAutowareState(const autoware_system_msgs::msg::AutowareState::SharedPtr msg);
  /// @brief 使用 SML 状态机的 Autoware 状态回调
  void onAutowareStateWithStateMachine(const autoware_system_msgs::msg::AutowareState::SharedPtr msg);
  /// @brief 控制模式反馈（人工/自动）。
  void onControlModeReport(const autoware_vehicle_msgs::msg::ControlModeReport::SharedPtr msg);
  /// @brief 车速反馈。
  void onVelocityReport(const autoware_vehicle_msgs::msg::VelocityReport::SharedPtr msg);
  /// @brief 本地坐标变换可信度。
  void onLocalTransformProbability(const autoware_internal_debug_msgs::msg::Float32Stamped::SharedPtr msg);
  /// @brief GNSS 定位报告。
  void onNavSatFix(const sensor_msgs::msg::NavSatFix::ConstSharedPtr& msg);
  /// @brief 车头朝向（底层驱动）。
  void onHeading(const std_msgs::msg::Float32::ConstSharedPtr& msg);
  /// @brief GNSS 天线 1 卫星数。
  void onSatellitesNumber1(const std_msgs::msg::UInt8::ConstSharedPtr& msg);
  /// @brief GNSS 天线 2 卫星数。
  void onSatellitesNumber2(const std_msgs::msg::UInt8::ConstSharedPtr& msg);
  /// @brief 车身控制模块反馈帧 4。
  void onBcmMessage4(const pix_robobus_driver_msgs::msg::BcmMessage4::SharedPtr msg);
  /// @brief 车身控制模块反馈帧 5。
  void onBcmMessage5(const pix_robobus_driver_msgs::msg::BcmMessage5::SharedPtr msg);
  /// @brief 驱动状态反馈。
  void onVaDriveStaFb(const pix_robobus_driver_msgs::msg::VaDriveStaFb::SharedPtr msg);
  /// @brief 制动状态反馈。
  void onVaBrakeStaFb(const pix_robobus_driver_msgs::msg::VaBrakeStaFb::SharedPtr msg);
  /// @brief 转向状态反馈。
  void onVaSteerStaFb(const pix_robobus_driver_msgs::msg::VaSteerStaFb::SharedPtr msg);
  /// @brief 车辆工作状态反馈。
  void onVaVehicleWorkStaFb(const pix_robobus_driver_msgs::msg::VaVehicleWorkStaFb::SharedPtr msg);
  /// @brief 电源状态反馈。
  void onVaPowerStaFb(const pix_robobus_driver_msgs::msg::VaPowerStaFb::SharedPtr msg);
  /// @brief 车辆总体状态反馈。
  void onVaVehicleStaFb(const pix_robobus_driver_msgs::msg::VaVehicleStaFb::SharedPtr msg);
  /// @brief 里程计反馈。
  void onVaChassisOdoFb(const pix_robobus_driver_msgs::msg::VaChassisOdoFb::SharedPtr msg);
  /// @brief 轮胎气压反馈。
  void onVaChassisWheelTirePressFb(const pix_robobus_driver_msgs::msg::VaChassisWheelTirePressFb::SharedPtr msg);
  /// @brief VIN 响应（第 1 帧）。
  void onVinResp1(const pix_robobus_driver_msgs::msg::VinResp1::SharedPtr msg);
  /// @brief VIN 响应（第 2 帧）。
  void onVinResp2(const pix_robobus_driver_msgs::msg::VinResp2::SharedPtr msg);
  /// @brief VIN 响应（第 3 帧）。
  void onVinResp3(const pix_robobus_driver_msgs::msg::VinResp3::SharedPtr msg);
  /// @brief VCU 透传帧。
  void onVcuTransfer(const pix_robobus_driver_msgs::msg::VcuTransfer::SharedPtr msg);
  /// @brief VCU 软件版本反馈。
  void onVcuSoftVer(const pix_robobus_driver_msgs::msg::VcuSoftVer::SharedPtr msg);
  /// @brief 车辆故障码反馈（帧 1）。
  void onVehicleErrcode1(const pix_robobus_driver_msgs::msg::VehicleErrcode1::SharedPtr msg);
  /// @brief AEB 信息报告回调。
  void onAebInfoReport(const aeb_interfaces::msg::AebInfoReport::SharedPtr msg);
  void onAebInfoShadow(const aeb_interfaces::msg::AebInfoShadow::SharedPtr msg);

  // 单一互斥回调组：即使放在 component_container_mt 中，也按单线程顺序执行本组件回调。
  rclcpp::CallbackGroup::SharedPtr serialized_callback_group_;

  // ros2 client
  rclcpp::Client<get_osm_info_msgs::srv::GetPrimitiveLength>::SharedPtr planner_length_client_;
  rclcpp::Client<get_osm_info_msgs::srv::GetRouteStations>::SharedPtr route_stations_client_;

  // ros2 publisher
  rclcpp::Publisher<pixmoving_hmi_msgs::msg::V2dVehicleInfo>::SharedPtr v2d_vehicle_info_pub_;
  rclcpp::Publisher<pixmoving_hmi_msgs::msg::V2dAllStationInfo>::SharedPtr all_station_info_pub_;
  rclcpp::Publisher<pixmoving_hmi_msgs::msg::V2dCurrentStationInfo>::SharedPtr current_station_info_pub_;
  rclcpp::Publisher<pixmoving_hmi_msgs::msg::TaskSemanticStatus>::SharedPtr task_semantic_status_pub_;
  rclcpp::Publisher<pixmoving_hmi_msgs::msg::VehicleInfo>::SharedPtr vehicle_info_pub_;
  rclcpp::Publisher<pixmoving_hmi_msgs::msg::SensorInfo>::SharedPtr sensor_info_pub_;
  rclcpp::Publisher<pixmoving_hmi_msgs::msg::AutowareInfo>::SharedPtr autoware_info_pub_;
  rclcpp::Publisher<std_msgs::msg::UInt8>::SharedPtr nearby_finish_pub_;

  // ros2 timer
  rclcpp::TimerBase::SharedPtr timer_;

  // ros2 subscriptions
  rclcpp::Subscription<autoware_planning_msgs::msg::LaneletRoute>::SharedPtr planner_route_sub_;
  rclcpp::Subscription<autoware_adapi_v1_msgs::msg::OperationModeState>::SharedPtr operation_mode_state_sub_;
  rclcpp::Subscription<autoware_internal_planning_msgs::msg::VelocityLimit>::SharedPtr velocity_limit_sub_;
  rclcpp::Subscription<autoware_internal_msgs::msg::MissionRemainingDistanceTime>::SharedPtr mission_remaining_distance_time_sub_;
  rclcpp::Subscription<geometry_msgs::msg::PoseStamped>::SharedPtr localization_pose_sub_;
  rclcpp::Subscription<geometry_msgs::msg::PoseStamped>::SharedPtr plan_goal_sub_;
  rclcpp::Subscription<tier4_external_api_msgs::msg::Emergency>::SharedPtr emergency_report_sub_;
  rclcpp::Subscription<autoware_system_msgs::msg::AutowareState>::SharedPtr autoware_state_sub_;
  rclcpp::Subscription<autoware_vehicle_msgs::msg::ControlModeReport>::SharedPtr control_mode_report_sub_;
  rclcpp::Subscription<autoware_vehicle_msgs::msg::VelocityReport>::SharedPtr velocity_report_sub_;
  rclcpp::Subscription<autoware_internal_debug_msgs::msg::Float32Stamped>::SharedPtr local_transform_probability_sub_;
  rclcpp::Subscription<sensor_msgs::msg::NavSatFix>::SharedPtr sub_nav_sat_fix_report_;
  rclcpp::Subscription<std_msgs::msg::Float32>::SharedPtr sub_heading_report_;
  rclcpp::Subscription<std_msgs::msg::UInt8>::SharedPtr sub_satellites_number1_;
  rclcpp::Subscription<std_msgs::msg::UInt8>::SharedPtr sub_satellites_number2_;
  rclcpp::Subscription<pix_robobus_driver_msgs::msg::BcmMessage4>::SharedPtr BcmMessage4_sub_;
  rclcpp::Subscription<pix_robobus_driver_msgs::msg::BcmMessage5>::SharedPtr BcmMessage5_sub_;
  rclcpp::Subscription<pix_robobus_driver_msgs::msg::VaDriveStaFb>::SharedPtr VaDriveStaFb_sub_;
  rclcpp::Subscription<pix_robobus_driver_msgs::msg::VaBrakeStaFb>::SharedPtr VaBrakeStaFb_sub_;
  rclcpp::Subscription<pix_robobus_driver_msgs::msg::VaSteerStaFb>::SharedPtr VaSteerStaFb_sub_;
  rclcpp::Subscription<pix_robobus_driver_msgs::msg::VaVehicleWorkStaFb>::SharedPtr VaVehicleWorkStaFb_sub_;
  rclcpp::Subscription<pix_robobus_driver_msgs::msg::VaPowerStaFb>::SharedPtr VaPowerStaFb_sub_;
  rclcpp::Subscription<pix_robobus_driver_msgs::msg::VaVehicleStaFb>::SharedPtr VaVehicleStaFb_sub_;
  rclcpp::Subscription<pix_robobus_driver_msgs::msg::VaChassisOdoFb>::SharedPtr VaChassisOdoFb_sub_;
  rclcpp::Subscription<pix_robobus_driver_msgs::msg::VaChassisWheelTirePressFb>::SharedPtr
      VaChassisWheelTirePressFb_sub_;
  rclcpp::Subscription<pix_robobus_driver_msgs::msg::VinResp1>::SharedPtr VinResp1_sub_;
  rclcpp::Subscription<pix_robobus_driver_msgs::msg::VinResp2>::SharedPtr VinResp2_sub_;
  rclcpp::Subscription<pix_robobus_driver_msgs::msg::VinResp3>::SharedPtr VinResp3_sub_;
  rclcpp::Subscription<pix_robobus_driver_msgs::msg::VcuTransfer>::SharedPtr VcuTransfer_sub_;
  rclcpp::Subscription<pix_robobus_driver_msgs::msg::VcuSoftVer>::SharedPtr VcuSoftVer_sub_;
  rclcpp::Subscription<pix_robobus_driver_msgs::msg::VehicleErrcode1>::SharedPtr VehicleErrcode1_sub_;
  rclcpp::Subscription<aeb_interfaces::msg::AebInfoReport>::SharedPtr AebInfoReport_sub_;
  rclcpp::Subscription<aeb_interfaces::msg::AebInfoShadow>::SharedPtr AebInfoShadow_sub_;

  YAML::Node station_yaml_list_obj_;
  pixmoving_hmi_msgs::msg::V2dVehicleInfo v2d_vehicle_info_msg_;
  pixmoving_hmi_msgs::msg::V2dAllStationInfo v2d_all_station_info_msg_;
  pixmoving_hmi_msgs::msg::V2dCurrentStationInfo v2d_current_station_info_msg_;
  pixmoving_hmi_msgs::msg::TaskSemanticStatus task_semantic_status_msg_;
  pixmoving_hmi_msgs::msg::VehicleInfo vehicle_info_msg_;
  pixmoving_hmi_msgs::msg::SensorInfo sensor_info_msg_;
  pixmoving_hmi_msgs::msg::AutowareInfo autoware_info_msg_;

  static constexpr std::uint32_t kVehicleInfoSourceDrive = 1u << 0;
  static constexpr std::uint32_t kVehicleInfoSourceBrake = 1u << 1;
  static constexpr std::uint32_t kVehicleInfoSourceWork = 1u << 2;
  static constexpr std::uint32_t kVehicleInfoSourcePower = 1u << 3;
  static constexpr std::uint32_t kVehicleInfoSourceVehicle = 1u << 4;
  static constexpr std::uint32_t kVehicleInfoSourceOdo = 1u << 5;
  static constexpr std::uint32_t kVehicleInfoReadyMask = kVehicleInfoSourceOdo;

  std::string vehicle_info_snapshot_path_;
  std::uint32_t vehicle_info_live_source_mask_{0};
  bool vehicle_info_snapshot_loaded_{false};
  rclcpp::Time last_vehicle_info_snapshot_save_time_;
  bool enable_fused_ptm_{true};
  double fused_power_on_mileage_m_{0.0};
  MileageSource current_mileage_source_{MileageSource::NONE};
  geometry_msgs::msg::PoseStamped::ConstSharedPtr last_ndt_pose_for_mileage_;
  rclcpp::Time last_ndt_pose_time_for_mileage_;
  sensor_msgs::msg::NavSatFix::ConstSharedPtr latest_valid_gnss_fix_ptr_;
  sensor_msgs::msg::NavSatFix::ConstSharedPtr last_gnss_fix_for_mileage_;
  rclcpp::Time last_gnss_fix_time_;
  rclcpp::Time last_gnss_fix_time_for_mileage_;
  bool last_gnss_fix_valid_{false};
  std::size_t gnss_valid_streak_{0};
  double last_chassis_speed_mps_{0.0};
  rclcpp::Time last_chassis_speed_time_;
  rclcpp::Time last_chassis_speed_integration_time_;
  double latest_raw_can_trip_m_{-1.0};
  double last_raw_can_trip_m_{-1.0};
  bool pending_raw_trip_sync_{true};
  double latest_ndt_pos_q_{std::numeric_limits<double>::infinity()};
  rclcpp::Time last_ndt_pos_q_time_;

  double ndt_pos_q_threshold_{2.3};
  double ndt_timeout_sec_{1.0};
  double gnss_timeout_sec_{1.0};
  double chassis_speed_timeout_sec_{0.5};
  double standstill_speed_threshold_mps_{0.2};
  double ndt_jump_reject_threshold_m_{5.0};
  double gnss_jump_reject_threshold_m_{20.0};
  double max_delta_ratio_{2.5};
  double raw_trip_sync_threshold_m_{12.0};
  int gnss_warmup_frames_{3};

  // 用于里程字段的边沿打印（-1 <-> 非-1）：
  // -1 表示未知。只在跨越未知边界时打印一次，避免每帧刷屏。
  std::int32_t last_tm_{-1};
  std::int32_t last_ptm_{-1};

  autoware_adapi_v1_msgs::msg::OperationModeState::ConstSharedPtr operation_mode_state_ptr_;
  geometry_msgs::msg::PoseStamped::ConstSharedPtr old_localization_pose_ptr_;
  geometry_msgs::msg::PoseStamped::ConstSharedPtr localization_pose_ptr_;
  tier4_external_api_msgs::msg::Emergency::ConstSharedPtr emergency_report_ptr_;

  rclcpp::Time localization_pose_received_time_;
  rclcpp::Time emergency_report_received_time_;

  TaskStationInfoTemp task_station_info_temp_;
  geometry_msgs::msg::Point current_target_station_{};
  geometry_msgs::msg::Point last_current_target_station_;

  float planning_speed_mph_{0.1F};
  float travel_distance_{0.0F};

  // 从 /planning/mission_remaining_distance_time 话题接收的剩余距离和时间
  double mission_remaining_distance_ = 0.0;
  double mission_remaining_time_ = 0.0;
  rclcpp::Time mission_remaining_distance_time_received_time_;

  uint8_t last_autoware_state_ = 0;
  uint8_t autoware_state_ = 0;
  uint8_t last_autoware_mode_ = 0;
  uint8_t last_pixmoving_mode_ = 0;
  std::uint64_t route_station_request_seq_ = 0;
  std::uint64_t route_length_request_seq_ = 0;
  uint8_t resend_cancle_count_ = 0;
  uint8_t near_done_count_ = 0;
  uint8_t estop_done_count_ = 0;
  double near_done_hold_until_sec_ = 0.0;
  double estop_done_hold_until_sec_ = 0.0;
  double estop_done_distance_threshold_m_ = 100.0;
  double estop_done_hold_sec_ = 0.5;
  double auto_last_time_ = 0;

  bool is_park_ = false;
  bool is_estop_ = false;
  bool autonomous_driving_ = false;
  bool decentralization_ = false;
  bool plan_status_ = true;
  bool vcu_brake_pedal_req_fb_ = false;  // 刹车踏板请求状态
  std::string last_staion_name;
  std::mutex task_semantic_mutex_;
  bool has_task_semantic_ = false;
  bool task_terminal_ = true;
  bool pending_new_task_event_ = false;
  int semantic_origin_station_index_ = -1;
  int semantic_target_station_index_ = -1;
  int last_inferred_current_station_index_ = -1;
  int last_inferred_target_station_index_ = -1;
  std::string last_inferred_current_station_name_;
  std::string last_inferred_target_station_name_;
  std::string last_task_lifecycle_ = "idle";
  std::string last_task_route_decision_ = "none";
  std::string last_task_station_source_ = "none";
  bool last_triggered_new_task_event_ = false;

  /// @brief 控制是否使用状态机驾驶模式逻辑
  bool use_state_machine_drive_mode_ = false;
  
  /// @brief 驾驶模式状态机管理器
  /// @note 使用 unique_ptr 管理生命周期，仅在启用状态机时创建
  std::unique_ptr<DriveModeManager> drive_mode_manager_;
  
  /// @brief 规划指标监控器
  /// @note 用于监控驾驶舒适性和轨迹稳定性指标
  std::unique_ptr<PlanningMetricsMonitor> planning_metrics_monitor_;

  MetricsThresholds thresholds_;
};

}  // namespace interface
}  // namespace chassis
}  // namespace pixmoving
