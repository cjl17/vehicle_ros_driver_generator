#pragma once

#include "pixmoving_chassis_interface/chassis_interface_common.hpp"
#include "pixmoving_chassis_interface/sml.hpp"
#include <autoware_system_msgs/msg/autoware_state.hpp>
#include <rclcpp/rclcpp.hpp>
#include <memory>
#include <string>

namespace pixmoving
{
namespace chassis
{
namespace interface
{

/// @brief 驾驶模式状态机的上下文数据
struct DriveModeContext
{
  // Autoware 状态
  uint8_t autoware_state = 0;
  
  // 车辆状态
  bool vcu_brake_pedal_triggered = false;
  double vehicle_speed_kmh = 0.0;
  double target_distance_m = 0.0;
  bool has_active_task = false;
  
  // 控制状态
  bool autonomous_driving = false;
  bool decentralization = false;  // 遥控器放权
  bool is_estop = false;
  
  // 时间相关
  double takeover_duration_sec = 0.0;
  double current_time = 0.0;
  double auto_last_time = 0.0;
  
  // 上一个模式
  DriveMode last_mode = DriveMode::UNKNOWN;
  
  // 站点信息
  double station_distance = 0.0;
  bool new_task_received = false;
  
  // 计数器
  uint8_t resend_cancel_count = 0;
  double near_done_hold_until_sec = 0.0;
  double estop_done_hold_until_sec = 0.0;
  double estop_done_distance_threshold_m = 100.0;
  double estop_done_hold_sec = 0.5;
  bool auto_done_normal_pending_publish = false;
  
  // 日志
  rclcpp::Logger* logger = nullptr;
};

/// @brief 驾驶模式状态机事件
struct DriveModeEvents
{
  // Autoware 状态事件
  struct AutowareDriving {};
  struct AutowareWaitingForEngage {};
  struct AutowareArrivedGoal {};
  struct AutowarePlanning {};
  struct AutowareInitializing {};
  struct AutowareOther {};
  
  // 车辆控制事件
  struct BrakePedalPressed {};
  struct BrakePedalReleased {};
  struct RemoteTakeover {};
  struct RemoteRelease {};
  
  // 时间事件
  struct TakeoverTimeout {};        // 300秒
  struct TakeoverCancelTimeout {};  // 303秒
  
  // 任务事件
  struct NewTaskReceived {};
  struct NearStationStopped {};
  struct EmergencyNearGoalTriggered {};
  
  // 紧急事件
  struct EmergencyTriggered {};
  struct EmergencyCleared {};
  
  // 计数器事件
  struct CancelCountTick {};
  struct NearDoneCountTick {};
  
  // 更新事件
  struct Update {};
};

/// @brief 驾驶模式状态机定义
struct DriveModeStateMachine
{
  // 状态定义
  struct ManualControl {};
  struct RemoteNetwork {};
  struct ManualEmergencyStop {};
  struct AutoStandby {};
  struct AutoExecuting {};
  struct AutoTakeoverManual {};
  struct AutoTakeoverBrake {};
  struct AutoDoneNormal {};
  struct AutoDoneNear {};
  struct AutoDoneEstopNear {};
  struct AutoCancelTakeover {};
  struct AutoCancelNewTask {};
  struct AutoEmergencyStop {};

  // ==================== SML 状态机定义 ====================
  //
  // 说明：
  // - 这里用 boost-ext/sml 的 “转移表” 描述所有转换
  // - 持续性条件检查（原 HFSM2 的 update/changeTo）通过 event<Update> 实现
  // - on_entry 行为通过 `on_entry` action 实现
  struct SmDef
  {
    explicit SmDef(DriveModeContext& ctx) : ctx_(ctx) {}

    // actions
    void enter_auto_executing() const
    {
      ctx_.autonomous_driving = true;
      ctx_.auto_last_time = ctx_.current_time;
      ctx_.auto_done_normal_pending_publish = false;
      if (ctx_.logger) { RCLCPP_INFO(*ctx_.logger, "Entered AutoExecuting state (autonomous driving active)"); }
    }
    void enter_auto_done_normal() const
    {
      ctx_.autonomous_driving = false;
      ctx_.auto_done_normal_pending_publish = true;
      if (ctx_.logger) { RCLCPP_INFO(*ctx_.logger, "Task completed normally (arrived at goal)"); }
    }
    void dec_resend_cancel_count() const { if (ctx_.resend_cancel_count > 0) { ctx_.resend_cancel_count--; } }
    void mark_new_task_cancel() const
    {
      ctx_.autonomous_driving = false;
      ctx_.resend_cancel_count = 3;
      ctx_.auto_done_normal_pending_publish = false;
    }
    void mark_near_station_done() const
    {
      ctx_.autonomous_driving = false;
      ctx_.near_done_hold_until_sec = ctx_.current_time + 3.0;
      ctx_.auto_done_normal_pending_publish = false;
      if (ctx_.logger) {
        RCLCPP_INFO(
          *ctx_.logger,
          "Near station completion: distance=%.1fm, speed=%.1fkm/h, hold_until=%.1f",
          ctx_.target_distance_m, ctx_.vehicle_speed_kmh, ctx_.near_done_hold_until_sec);
      }
    }
    void mark_estop_near_done() const
    {
      ctx_.autonomous_driving = false;
      ctx_.estop_done_hold_until_sec = ctx_.current_time + ctx_.estop_done_hold_sec;
      ctx_.auto_done_normal_pending_publish = false;
      if (ctx_.logger) {
        RCLCPP_INFO(
          *ctx_.logger,
          "Near-goal estop completion: distance=%.1fm, speed=%.1fkm/h, hold_until=%.1f",
          ctx_.target_distance_m, ctx_.vehicle_speed_kmh, ctx_.estop_done_hold_until_sec);
      }
    }
    void clear_autonomous() const
    {
      ctx_.autonomous_driving = false;
      ctx_.auto_done_normal_pending_publish = false;
    }

    // guards
    bool g_to_auto_standby_from_manual() const { return ctx_.decentralization && !ctx_.is_estop; }
    bool g_to_manual_from_standby() const { return !ctx_.decentralization && !ctx_.is_estop; }
    bool g_autodone_near_complete() const { return ctx_.current_time >= ctx_.near_done_hold_until_sec; }
    bool g_autodone_estop_near_complete() const
    {
      return ctx_.current_time >= ctx_.estop_done_hold_until_sec;
    }
    bool g_cancel_new_task_complete() const { return ctx_.resend_cancel_count == 0; }
    bool g_autotakeoverbrake_back_to_auto() const
    {
      using AutowareState = autoware_system_msgs::msg::AutowareState;
      return ctx_.autoware_state == AutowareState::DRIVING;
    }

    // state-machine transition table
    auto operator()() const
    {
      namespace sml = boost::ext::sml;
      using namespace sml;

      // Guards: avoid `[[` token sequence (can be parsed as attributes by GCC)
      const auto g_manual_to_standby = [this] { return g_to_auto_standby_from_manual(); };
      const auto g_standby_to_manual = [this] { return g_to_manual_from_standby(); };
      const auto g_brake_to_auto = [this] { return g_autotakeoverbrake_back_to_auto(); };
      const auto g_done_normal_to_standby = [this] { return ctx_.decentralization; };
      const auto g_done_near_to_standby = [this] { return g_autodone_near_complete() && ctx_.decentralization; };
      const auto g_done_near_to_manual = [this] { return g_autodone_near_complete() && !ctx_.decentralization; };
      const auto g_done_estop_near_to_estop = [this] {
        return g_autodone_estop_near_complete() && ctx_.is_estop;
      };
      const auto g_done_estop_near_to_standby = [this] {
        return g_autodone_estop_near_complete() && !ctx_.is_estop && ctx_.decentralization;
      };
      const auto g_done_estop_near_to_manual = [this] {
        return g_autodone_estop_near_complete() && !ctx_.is_estop && !ctx_.decentralization;
      };
      const auto g_cancel_new_task_to_standby = [this] { return g_cancel_new_task_complete() && ctx_.decentralization; };
      const auto g_cancel_new_task_to_manual = [this] { return g_cancel_new_task_complete() && !ctx_.decentralization; };
      const auto g_estop_clear_to_standby = [this] { return ctx_.decentralization; };
      // NOTE: 用于把 RemoteNetwork 显式纳入 SML 的状态集合（避免查询 is(state<RemoteNetwork>) 编译失败）
      // 当前没有上层信号触发进入 RemoteNetwork，因此先用恒 false 的 guard 保留该状态，不改变现有行为。
      const auto g_never = [] { return false; };

      return make_transition_table(
        // initial state
        *state<DriveModeStateMachine::ManualControl> + event<DriveModeEvents::Update> [g_manual_to_standby] = state<DriveModeStateMachine::AutoStandby>,
         state<DriveModeStateMachine::ManualControl> + event<DriveModeEvents::RemoteRelease> = state<DriveModeStateMachine::AutoStandby>,
         state<DriveModeStateMachine::ManualControl> + event<DriveModeEvents::EmergencyTriggered> = state<DriveModeStateMachine::ManualEmergencyStop>,
         state<DriveModeStateMachine::ManualControl> + event<DriveModeEvents::AutowareOther> [g_never] = state<DriveModeStateMachine::RemoteNetwork>,
         state<DriveModeStateMachine::RemoteNetwork> + event<DriveModeEvents::Update> = state<DriveModeStateMachine::ManualControl>,

        // ManualEmergencyStop
         state<DriveModeStateMachine::ManualEmergencyStop> + event<DriveModeEvents::EmergencyCleared> = state<DriveModeStateMachine::ManualControl>,

        // AutoStandby
         state<DriveModeStateMachine::AutoStandby> + event<DriveModeEvents::Update> [g_standby_to_manual] = state<DriveModeStateMachine::ManualControl>,
         state<DriveModeStateMachine::AutoStandby> + event<DriveModeEvents::AutowareDriving> / [this] { enter_auto_executing(); } = state<DriveModeStateMachine::AutoExecuting>,
         state<DriveModeStateMachine::AutoStandby> + event<DriveModeEvents::RemoteTakeover> = state<DriveModeStateMachine::ManualControl>,
         state<DriveModeStateMachine::AutoStandby> + event<DriveModeEvents::EmergencyTriggered> = state<DriveModeStateMachine::AutoEmergencyStop>,

        // AutoExecuting
         state<DriveModeStateMachine::AutoExecuting> + event<DriveModeEvents::BrakePedalPressed> = state<DriveModeStateMachine::AutoTakeoverBrake>,
         state<DriveModeStateMachine::AutoExecuting> + event<DriveModeEvents::RemoteTakeover> = state<DriveModeStateMachine::AutoTakeoverManual>,
         state<DriveModeStateMachine::AutoExecuting> + event<DriveModeEvents::AutowareArrivedGoal> / [this] { enter_auto_done_normal(); } = state<DriveModeStateMachine::AutoDoneNormal>,
         state<DriveModeStateMachine::AutoExecuting> + event<DriveModeEvents::NewTaskReceived> / [this] { mark_new_task_cancel(); } = state<DriveModeStateMachine::AutoCancelNewTask>,
         state<DriveModeStateMachine::AutoExecuting> + event<DriveModeEvents::EmergencyTriggered> = state<DriveModeStateMachine::AutoEmergencyStop>,

        // AutoTakeoverManual
         state<DriveModeStateMachine::AutoTakeoverManual> + event<DriveModeEvents::AutowareDriving> / [this] { enter_auto_executing(); } = state<DriveModeStateMachine::AutoExecuting>,
         state<DriveModeStateMachine::AutoTakeoverManual> + event<DriveModeEvents::TakeoverTimeout> = state<DriveModeStateMachine::AutoCancelTakeover>,
         state<DriveModeStateMachine::AutoTakeoverManual> + event<DriveModeEvents::NewTaskReceived> / [this] { mark_new_task_cancel(); } = state<DriveModeStateMachine::AutoCancelNewTask>,
         state<DriveModeStateMachine::AutoTakeoverManual> + event<DriveModeEvents::NearStationStopped> / [this] { mark_near_station_done(); } = state<DriveModeStateMachine::AutoDoneNear>,
         state<DriveModeStateMachine::AutoTakeoverManual> + event<DriveModeEvents::EmergencyNearGoalTriggered> / [this] { mark_estop_near_done(); } = state<DriveModeStateMachine::AutoDoneEstopNear>,
         state<DriveModeStateMachine::AutoTakeoverManual> + event<DriveModeEvents::EmergencyTriggered> = state<DriveModeStateMachine::AutoEmergencyStop>,

        // AutoTakeoverBrake
         state<DriveModeStateMachine::AutoTakeoverBrake> + event<DriveModeEvents::BrakePedalReleased> [g_brake_to_auto] / [this] { enter_auto_executing(); } = state<DriveModeStateMachine::AutoExecuting>,
         state<DriveModeStateMachine::AutoTakeoverBrake> + event<DriveModeEvents::BrakePedalReleased> = state<DriveModeStateMachine::AutoTakeoverManual>,
         state<DriveModeStateMachine::AutoTakeoverBrake> + event<DriveModeEvents::AutowareWaitingForEngage> = state<DriveModeStateMachine::AutoTakeoverManual>,
         state<DriveModeStateMachine::AutoTakeoverBrake> + event<DriveModeEvents::NewTaskReceived> / [this] { mark_new_task_cancel(); } = state<DriveModeStateMachine::AutoCancelNewTask>,
         state<DriveModeStateMachine::AutoTakeoverBrake> + event<DriveModeEvents::EmergencyNearGoalTriggered> / [this] { mark_estop_near_done(); } = state<DriveModeStateMachine::AutoDoneEstopNear>,
         state<DriveModeStateMachine::AutoTakeoverBrake> + event<DriveModeEvents::EmergencyTriggered> = state<DriveModeStateMachine::AutoEmergencyStop>,

        // AutoDoneNormal
         state<DriveModeStateMachine::AutoDoneNormal> + event<DriveModeEvents::Update> [g_done_normal_to_standby] = state<DriveModeStateMachine::AutoStandby>,
         state<DriveModeStateMachine::AutoDoneNormal> + event<DriveModeEvents::EmergencyTriggered> = state<DriveModeStateMachine::AutoEmergencyStop>,
         state<DriveModeStateMachine::AutoDoneNormal> + event<DriveModeEvents::Update> = state<DriveModeStateMachine::ManualControl>,

        // AutoDoneNear
         state<DriveModeStateMachine::AutoDoneNear> + event<DriveModeEvents::Update> [g_done_near_to_standby] = state<DriveModeStateMachine::AutoStandby>,
         state<DriveModeStateMachine::AutoDoneNear> + event<DriveModeEvents::EmergencyTriggered> = state<DriveModeStateMachine::AutoEmergencyStop>,
         state<DriveModeStateMachine::AutoDoneNear> + event<DriveModeEvents::Update> [g_done_near_to_manual] = state<DriveModeStateMachine::ManualControl>,

        // AutoDoneEstopNear
         state<DriveModeStateMachine::AutoDoneEstopNear> + event<DriveModeEvents::Update> [g_done_estop_near_to_estop] = state<DriveModeStateMachine::AutoEmergencyStop>,
         state<DriveModeStateMachine::AutoDoneEstopNear> + event<DriveModeEvents::EmergencyTriggered> = state<DriveModeStateMachine::AutoEmergencyStop>,
         state<DriveModeStateMachine::AutoDoneEstopNear> + event<DriveModeEvents::Update> [g_done_estop_near_to_standby] = state<DriveModeStateMachine::AutoStandby>,
         state<DriveModeStateMachine::AutoDoneEstopNear> + event<DriveModeEvents::Update> [g_done_estop_near_to_manual] = state<DriveModeStateMachine::ManualControl>,

        // AutoCancelTakeover
         state<DriveModeStateMachine::AutoCancelTakeover> + event<DriveModeEvents::EmergencyTriggered> = state<DriveModeStateMachine::AutoEmergencyStop>,
         state<DriveModeStateMachine::AutoCancelTakeover> + event<DriveModeEvents::TakeoverCancelTimeout> / [this] { clear_autonomous(); } = state<DriveModeStateMachine::ManualControl>,

        // AutoCancelNewTask
         state<DriveModeStateMachine::AutoCancelNewTask> + event<DriveModeEvents::CancelCountTick> / [this] { dec_resend_cancel_count(); } = state<DriveModeStateMachine::AutoCancelNewTask>,
         state<DriveModeStateMachine::AutoCancelNewTask> + event<DriveModeEvents::Update> [g_cancel_new_task_to_standby] = state<DriveModeStateMachine::AutoStandby>,
         state<DriveModeStateMachine::AutoCancelNewTask> + event<DriveModeEvents::EmergencyTriggered> = state<DriveModeStateMachine::AutoEmergencyStop>,
         state<DriveModeStateMachine::AutoCancelNewTask> + event<DriveModeEvents::Update> [g_cancel_new_task_to_manual] = state<DriveModeStateMachine::ManualControl>,

        // AutoEmergencyStop
         state<DriveModeStateMachine::AutoEmergencyStop> + event<DriveModeEvents::EmergencyCleared> [g_estop_clear_to_standby] = state<DriveModeStateMachine::AutoStandby>,
         state<DriveModeStateMachine::AutoEmergencyStop> + event<DriveModeEvents::EmergencyCleared> = state<DriveModeStateMachine::ManualControl>
      );
    }

    DriveModeContext& ctx_;
  };
};

/// @brief 驾驶模式管理器（封装状态机）
class DriveModeManager
{
public:
  explicit DriveModeManager(rclcpp::Logger logger);
  
  /// @brief 更新状态机（处理 Autoware 状态变化）
  /// @param autoware_state Autoware 状态
  /// @param context 上下文数据
  /// @return 当前驾驶模式
  DriveMode update(uint8_t autoware_state, DriveModeContext& context);
  
  /// @brief 获取当前驾驶模式
  DriveMode getCurrentMode() const { return current_mode_; }
  
  /// @brief 获取当前状态名称（用于调试）
  std::string getCurrentStateName() const;
  
  /// @brief 重置状态机
  void reset();

  /// @brief 仅供测试使用：注入 RemoteRelease 事件
  DriveMode processRemoteReleaseForTest(DriveModeContext& context);

  /// @brief 仅供测试使用：注入 RemoteTakeover 事件
  DriveMode processRemoteTakeoverForTest(DriveModeContext& context);

private:
  DriveModeContext context_;
  using Sm = boost::ext::sml::sm<DriveModeStateMachine::SmDef>;
  std::unique_ptr<Sm> sm_;
  DriveMode current_mode_;
  rclcpp::Logger logger_;
  
  /// @brief 根据状态机当前状态获取驾驶模式
  DriveMode getMode() const;

  /// @brief 从外部上下文同步到状态机内部上下文
  void syncContextFromInput(uint8_t autoware_state, const DriveModeContext& new_context);

  /// @brief 从状态机内部上下文同步回外部上下文
  void syncContextToOutput(DriveModeContext& context) const;

  /// @brief 根据当前状态更新 current_mode_
  void refreshCurrentMode();

  /// @brief 是否处于手动域急停态
  bool isManualEmergencyStopState() const;

  /// @brief 是否处于自动域急停态
  bool isAutoEmergencyStopState() const;

  /// @brief 是否处于任一急停态
  bool isEmergencyStopState() const;
  
  /// @brief 处理 Autoware 状态事件
  void processAutowareState(uint8_t autoware_state);
  
  /// @brief 检查并触发时间相关事件
  void checkTimeEvents();
  
  /// @brief 检查并触发车辆状态事件
  void checkVehicleEvents();
};

}  // namespace interface
}  // namespace chassis
}  // namespace pixmoving
