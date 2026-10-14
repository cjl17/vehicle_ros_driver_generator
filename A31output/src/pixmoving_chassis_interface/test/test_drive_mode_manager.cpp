#include <gtest/gtest.h>

#include <cstdlib>
#include <memory>

#include <autoware_system_msgs/msg/autoware_state.hpp>
#include <rclcpp/rclcpp.hpp>

#include "pixmoving_chassis_interface/drive_mode_state_machine.hpp"

namespace pixmoving
{
namespace chassis
{
namespace interface
{

using AutowareState = autoware_system_msgs::msg::AutowareState;

class DriveModeManagerTest : public ::testing::Test
{
protected:
  static void SetUpTestSuite()
  {
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
    manager_ = std::make_unique<DriveModeManager>(rclcpp::get_logger("drive_mode_manager_test"));
    context_ = DriveModeContext{};
    context_.current_time = 100.0;
    context_.vehicle_speed_kmh = 10.0;
    context_.target_distance_m = 1000.0;
  }

  DriveMode Step(uint8_t autoware_state = 0)
  {
    context_.autoware_state = autoware_state;
    return manager_->update(autoware_state, context_);
  }

  void AdvanceTime(double delta_sec)
  {
    context_.current_time += delta_sec;
  }

  void EnterAutoStandby()
  {
    context_.decentralization = true;
    EXPECT_EQ(Step(), DriveMode::AUTO_STANDBY);
    EXPECT_EQ(manager_->getCurrentStateName(), "AutoStandby");
  }

  void EnterAutoExecuting()
  {
    EnterAutoStandby();
    EXPECT_EQ(Step(AutowareState::DRIVING), DriveMode::AUTO_EXECUTING);
    EXPECT_EQ(manager_->getCurrentStateName(), "AutoExecuting");
  }

  void EnterAutoTakeoverBrake()
  {
    EnterAutoExecuting();
    context_.vcu_brake_pedal_triggered = true;
    EXPECT_EQ(Step(AutowareState::DRIVING), DriveMode::AUTO_TAKEOVER_BRAKE);
    EXPECT_EQ(manager_->getCurrentStateName(), "AutoTakeoverBrake");
  }

  void EnterAutoTakeoverManual()
  {
    EnterAutoTakeoverBrake();
    context_.vcu_brake_pedal_triggered = false;
    EXPECT_EQ(Step(AutowareState::WAITING_FOR_ENGAGE), DriveMode::AUTO_TAKEOVER_MANUAL);
    EXPECT_EQ(manager_->getCurrentStateName(), "AutoTakeoverManual");
  }

  std::unique_ptr<DriveModeManager> manager_;
  DriveModeContext context_;
};

TEST_F(DriveModeManagerTest, ManualToStandbyToExecuting)
{
  EnterAutoExecuting();
}

TEST_F(DriveModeManagerTest, ManualEmergencyStopMapsToMode3AndReturnsToManual)
{
  context_.is_estop = true;
  EXPECT_EQ(Step(), DriveMode::EMERGENCY_STOP);
  EXPECT_EQ(manager_->getCurrentStateName(), "ManualEmergencyStop");

  context_.is_estop = false;
  EXPECT_EQ(Step(), DriveMode::MANUAL_CONTROL);
  EXPECT_EQ(manager_->getCurrentStateName(), "ManualControl");
}

TEST_F(DriveModeManagerTest, AutoEmergencyStopMapsToMode3AndReturnsToStandby)
{
  EnterAutoExecuting();

  context_.is_estop = true;
  EXPECT_EQ(Step(AutowareState::WAITING_FOR_ENGAGE), DriveMode::EMERGENCY_STOP);
  EXPECT_EQ(manager_->getCurrentStateName(), "AutoEmergencyStop");

  context_.is_estop = false;
  context_.decentralization = true;
  EXPECT_EQ(Step(AutowareState::WAITING_FOR_ENGAGE), DriveMode::AUTO_STANDBY);
  EXPECT_EQ(manager_->getCurrentStateName(), "AutoStandby");
}

TEST_F(DriveModeManagerTest, AutoEmergencyStopReturnsToManualWhenDecentralizationLost)
{
  EnterAutoExecuting();

  context_.is_estop = true;
  EXPECT_EQ(Step(AutowareState::WAITING_FOR_ENGAGE), DriveMode::EMERGENCY_STOP);
  EXPECT_EQ(manager_->getCurrentStateName(), "AutoEmergencyStop");

  context_.is_estop = false;
  context_.decentralization = false;
  EXPECT_EQ(Step(AutowareState::WAITING_FOR_ENGAGE), DriveMode::MANUAL_CONTROL);
  EXPECT_EQ(manager_->getCurrentStateName(), "ManualControl");
}

TEST_F(DriveModeManagerTest, AutoDoneNormalPublishesOneCycleBeforeFallingBack)
{
  EnterAutoExecuting();

  EXPECT_EQ(Step(AutowareState::ARRIVED_GOAL), DriveMode::AUTO_DONE_NORMAL);
  EXPECT_EQ(manager_->getCurrentStateName(), "AutoDoneNormal");

  context_.decentralization = true;
  EXPECT_EQ(Step(AutowareState::WAITING_FOR_ENGAGE), DriveMode::AUTO_STANDBY);
  EXPECT_EQ(manager_->getCurrentStateName(), "AutoStandby");
}

TEST_F(DriveModeManagerTest, AutoDoneNearFromTakeoverManualFallsBackAfterHold)
{
  EnterAutoTakeoverManual();

  context_.vehicle_speed_kmh = 0.5;
  context_.target_distance_m = 30.0;
  EXPECT_EQ(Step(AutowareState::WAITING_FOR_ENGAGE), DriveMode::AUTO_DONE_NEAR);
  EXPECT_EQ(manager_->getCurrentStateName(), "AutoDoneNear");

  AdvanceTime(3.1);
  context_.decentralization = false;
  EXPECT_EQ(Step(AutowareState::WAITING_FOR_ENGAGE), DriveMode::MANUAL_CONTROL);
  EXPECT_EQ(manager_->getCurrentStateName(), "ManualControl");
}

TEST_F(DriveModeManagerTest, AutoDoneEstopNearFromTakeoverManualFallsBackToAutoEmergencyStop)
{
  EnterAutoTakeoverManual();

  context_.has_active_task = true;
  context_.is_estop = true;
  context_.vehicle_speed_kmh = 0.5;
  context_.target_distance_m = 20.0;
  EXPECT_EQ(Step(AutowareState::WAITING_FOR_ENGAGE), DriveMode::AUTO_DONE_ESTOP_NEAR);
  EXPECT_EQ(manager_->getCurrentStateName(), "AutoDoneEstopNear");

  AdvanceTime(0.6);
  EXPECT_EQ(Step(AutowareState::WAITING_FOR_ENGAGE), DriveMode::EMERGENCY_STOP);
  EXPECT_EQ(manager_->getCurrentStateName(), "AutoEmergencyStop");
}

TEST_F(DriveModeManagerTest, AutoDoneEstopNearCanBeTriggeredFromTakeoverBrake)
{
  EnterAutoTakeoverBrake();

  context_.has_active_task = true;
  context_.is_estop = true;
  context_.vehicle_speed_kmh = 0.5;
  context_.target_distance_m = 20.0;
  EXPECT_EQ(Step(AutowareState::DRIVING), DriveMode::AUTO_DONE_ESTOP_NEAR);
  EXPECT_EQ(manager_->getCurrentStateName(), "AutoDoneEstopNear");
}

TEST_F(DriveModeManagerTest, AutoCancelNewTaskFromExecutingFallsBackToStandbyAfterThreeTicks)
{
  EnterAutoExecuting();

  context_.new_task_received = true;
  EXPECT_EQ(Step(AutowareState::DRIVING), DriveMode::AUTO_CANCEL_NEW_TASK);
  EXPECT_EQ(manager_->getCurrentStateName(), "AutoCancelNewTask");
  EXPECT_EQ(context_.resend_cancel_count, 3);

  context_.new_task_received = false;
  EXPECT_EQ(Step(AutowareState::WAITING_FOR_ENGAGE), DriveMode::AUTO_CANCEL_NEW_TASK);
  EXPECT_EQ(context_.resend_cancel_count, 2);
  EXPECT_EQ(Step(AutowareState::WAITING_FOR_ENGAGE), DriveMode::AUTO_CANCEL_NEW_TASK);
  EXPECT_EQ(context_.resend_cancel_count, 1);
  EXPECT_EQ(Step(AutowareState::WAITING_FOR_ENGAGE), DriveMode::AUTO_STANDBY);
  EXPECT_EQ(context_.resend_cancel_count, 0);
  EXPECT_EQ(manager_->getCurrentStateName(), "AutoStandby");
}

TEST_F(DriveModeManagerTest, AutoCancelNewTaskFromTakeoverManualCanFallBackToManual)
{
  EnterAutoTakeoverManual();

  context_.new_task_received = true;
  EXPECT_EQ(Step(AutowareState::WAITING_FOR_ENGAGE), DriveMode::AUTO_CANCEL_NEW_TASK);
  EXPECT_EQ(manager_->getCurrentStateName(), "AutoCancelNewTask");
  EXPECT_EQ(context_.resend_cancel_count, 3);

  context_.new_task_received = false;
  context_.decentralization = false;
  EXPECT_EQ(Step(AutowareState::WAITING_FOR_ENGAGE), DriveMode::AUTO_CANCEL_NEW_TASK);
  EXPECT_EQ(Step(AutowareState::WAITING_FOR_ENGAGE), DriveMode::AUTO_CANCEL_NEW_TASK);
  EXPECT_EQ(Step(AutowareState::WAITING_FOR_ENGAGE), DriveMode::MANUAL_CONTROL);
  EXPECT_EQ(manager_->getCurrentStateName(), "ManualControl");
}

TEST_F(DriveModeManagerTest, TakeoverTimeoutTransitionsToCancelTakeoverAndThenStandbyWhenStillDecentralized)
{
  EnterAutoTakeoverManual();

  context_.current_time = context_.auto_last_time + 301.0;
  EXPECT_EQ(Step(AutowareState::WAITING_FOR_ENGAGE), DriveMode::AUTO_CANCEL_TAKEOVER);
  EXPECT_EQ(manager_->getCurrentStateName(), "AutoCancelTakeover");

  context_.current_time = context_.auto_last_time + 304.0;
  EXPECT_EQ(Step(AutowareState::WAITING_FOR_ENGAGE), DriveMode::AUTO_STANDBY);
  EXPECT_EQ(manager_->getCurrentStateName(), "AutoStandby");
}

TEST_F(DriveModeManagerTest, TakeoverTimeoutTransitionsToCancelTakeoverAndThenManualWhenDecentralizationLost)
{
  EnterAutoTakeoverManual();

  context_.current_time = context_.auto_last_time + 301.0;
  EXPECT_EQ(Step(AutowareState::WAITING_FOR_ENGAGE), DriveMode::AUTO_CANCEL_TAKEOVER);
  EXPECT_EQ(manager_->getCurrentStateName(), "AutoCancelTakeover");

  context_.current_time = context_.auto_last_time + 304.0;
  context_.decentralization = false;
  EXPECT_EQ(Step(AutowareState::WAITING_FOR_ENGAGE), DriveMode::MANUAL_CONTROL);
  EXPECT_EQ(manager_->getCurrentStateName(), "ManualControl");
}

TEST_F(DriveModeManagerTest, RemoteReleaseCanMoveManualControlToAutoStandbyForStateDefinition)
{
  context_.decentralization = true;
  EXPECT_EQ(manager_->processRemoteReleaseForTest(context_), DriveMode::AUTO_STANDBY);
  EXPECT_EQ(manager_->getCurrentStateName(), "AutoStandby");
}

TEST_F(DriveModeManagerTest, RemoteTakeoverCanMoveAutoStandbyToManualControlForStateDefinition)
{
  EnterAutoStandby();

  EXPECT_EQ(manager_->processRemoteTakeoverForTest(context_), DriveMode::MANUAL_CONTROL);
  EXPECT_EQ(manager_->getCurrentStateName(), "ManualControl");
}

TEST_F(DriveModeManagerTest, RemoteTakeoverCanMoveAutoExecutingToAutoTakeoverManualForStateDefinition)
{
  EnterAutoExecuting();

  EXPECT_EQ(manager_->processRemoteTakeoverForTest(context_), DriveMode::AUTO_TAKEOVER_MANUAL);
  EXPECT_EQ(manager_->getCurrentStateName(), "AutoTakeoverManual");
}

}  // namespace interface
}  // namespace chassis
}  // namespace pixmoving
