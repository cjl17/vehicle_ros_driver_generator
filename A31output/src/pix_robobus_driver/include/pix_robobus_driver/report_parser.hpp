#pragma once

#include <string>
#include <memory>

#include <rclcpp/rclcpp.hpp>

#include <std_msgs/msg/bool.hpp>
#include <std_msgs/msg/header.hpp>

#include <can_msgs/msg/frame.hpp>


// pix_robobus_driver_msgs - include_msg_list
#include <pix_robobus_driver_msgs/msg/vcu_soft_ver.hpp>
#include <pix_robobus_driver_msgs/msg/ac_message1.hpp>
#include <pix_robobus_driver_msgs/msg/ac_message2.hpp>
#include <pix_robobus_driver_msgs/msg/vin_resp1.hpp>
#include <pix_robobus_driver_msgs/msg/vin_resp2.hpp>
#include <pix_robobus_driver_msgs/msg/vin_resp3.hpp>
#include <pix_robobus_driver_msgs/msg/vehicle_errcode1.hpp>
#include <pix_robobus_driver_msgs/msg/vehicle_errcode2.hpp>
#include <pix_robobus_driver_msgs/msg/historical_vehiclefailures1.hpp>
#include <pix_robobus_driver_msgs/msg/historical_vehiclefailures2.hpp>
#include <pix_robobus_driver_msgs/msg/va_drive_sta_fb.hpp>
#include <pix_robobus_driver_msgs/msg/va_brake_sta_fb.hpp>
#include <pix_robobus_driver_msgs/msg/va_steer_sta_fb.hpp>
#include <pix_robobus_driver_msgs/msg/va_vehicle_work_sta_fb.hpp>
#include <pix_robobus_driver_msgs/msg/va_power_sta_fb.hpp>
#include <pix_robobus_driver_msgs/msg/va_vehicle_sta_fb.hpp>
#include <pix_robobus_driver_msgs/msg/va_vehicle_flt_sta.hpp>
#include <pix_robobus_driver_msgs/msg/va_chassis_wheel_rpm_fb.hpp>
#include <pix_robobus_driver_msgs/msg/va_chassis_odo_fb.hpp>
#include <pix_robobus_driver_msgs/msg/vcu_transfer.hpp>
#include <pix_robobus_driver_msgs/msg/va_chassis_wheel_tire_press_fb.hpp>
#include <pix_robobus_driver_msgs/msg/va_chassis_wheel_angle_fb.hpp>
#include <pix_robobus_driver_msgs/msg/va_chassis_wheel_torque_fb.hpp>
#include <pix_robobus_driver_msgs/msg/bcm_message4.hpp>
#include <pix_robobus_driver_msgs/msg/bcm_message5.hpp>
#include <pix_robobus_driver_msgs/msg/dp_messgae4.hpp>
#include <pix_robobus_driver_msgs/msg/dp_messgae5.hpp>


// protocol libs - include_hpp_list
#include <libs/vcu_soft_ver.hpp>
#include <libs/ac_message1.hpp>
#include <libs/ac_message2.hpp>
#include <libs/vin_resp1.hpp>
#include <libs/vin_resp2.hpp>
#include <libs/vin_resp3.hpp>
#include <libs/vehicle_errcode1.hpp>
#include <libs/vehicle_errcode2.hpp>
#include <libs/historical_vehiclefailures1.hpp>
#include <libs/historical_vehiclefailures2.hpp>
#include <libs/va_drive_sta_fb.hpp>
#include <libs/va_brake_sta_fb.hpp>
#include <libs/va_steer_sta_fb.hpp>
#include <libs/va_vehicle_work_sta_fb.hpp>
#include <libs/va_power_sta_fb.hpp>
#include <libs/va_vehicle_sta_fb.hpp>
#include <libs/va_vehicle_flt_sta.hpp>
#include <libs/va_chassis_wheel_rpm_fb.hpp>
#include <libs/va_chassis_odo_fb.hpp>
#include <libs/vcu_transfer.hpp>
#include <libs/va_chassis_wheel_tire_press_fb.hpp>
#include <libs/va_chassis_wheel_angle_fb.hpp>
#include <libs/va_chassis_wheel_torque_fb.hpp>
#include <libs/bcm_message4.hpp>
#include <libs/bcm_message5.hpp>
#include <libs/dp_messgae4.hpp>
#include <libs/dp_messgae5.hpp>


namespace pix_robobus_driver
{
namespace report_parser
{

/**
 * @brief param structure of report parser node
 * @param base_frame_id frame id of vehicle
 * @param loop_rate loop rate of publishers in hz
 */
struct Param
{
  std::string base_frame_id;
  double loop_rate;
};

class ReportParser : public rclcpp::Node
{
private:
  // parameters of node
  Param param_;

  // subscribers from socketcan interface
  rclcpp::Subscription<can_msgs::msg::Frame>::SharedPtr can_frame_sub_;

  // publishers - publisher_list
  rclcpp::Publisher<pix_robobus_driver_msgs::msg::VcuSoftVer>::SharedPtr vcu_soft_ver_pub_;
  rclcpp::Publisher<pix_robobus_driver_msgs::msg::AcMessage1>::SharedPtr ac_message1_pub_;
  rclcpp::Publisher<pix_robobus_driver_msgs::msg::AcMessage2>::SharedPtr ac_message2_pub_;
  rclcpp::Publisher<pix_robobus_driver_msgs::msg::VinResp1>::SharedPtr vin_resp1_pub_;
  rclcpp::Publisher<pix_robobus_driver_msgs::msg::VinResp2>::SharedPtr vin_resp2_pub_;
  rclcpp::Publisher<pix_robobus_driver_msgs::msg::VinResp3>::SharedPtr vin_resp3_pub_;
  rclcpp::Publisher<pix_robobus_driver_msgs::msg::VehicleErrcode1>::SharedPtr vehicle_errcode1_pub_;
  rclcpp::Publisher<pix_robobus_driver_msgs::msg::VehicleErrcode2>::SharedPtr vehicle_errcode2_pub_;
  rclcpp::Publisher<pix_robobus_driver_msgs::msg::HistoricalVehiclefailures1>::SharedPtr historical_vehiclefailures1_pub_;
  rclcpp::Publisher<pix_robobus_driver_msgs::msg::HistoricalVehiclefailures2>::SharedPtr historical_vehiclefailures2_pub_;
  rclcpp::Publisher<pix_robobus_driver_msgs::msg::VaDriveStaFb>::SharedPtr va_drive_sta_fb_pub_;
  rclcpp::Publisher<pix_robobus_driver_msgs::msg::VaBrakeStaFb>::SharedPtr va_brake_sta_fb_pub_;
  rclcpp::Publisher<pix_robobus_driver_msgs::msg::VaSteerStaFb>::SharedPtr va_steer_sta_fb_pub_;
  rclcpp::Publisher<pix_robobus_driver_msgs::msg::VaVehicleWorkStaFb>::SharedPtr va_vehicle_work_sta_fb_pub_;
  rclcpp::Publisher<pix_robobus_driver_msgs::msg::VaPowerStaFb>::SharedPtr va_power_sta_fb_pub_;
  rclcpp::Publisher<pix_robobus_driver_msgs::msg::VaVehicleStaFb>::SharedPtr va_vehicle_sta_fb_pub_;
  rclcpp::Publisher<pix_robobus_driver_msgs::msg::VaVehicleFltSta>::SharedPtr va_vehicle_flt_sta_pub_;
  rclcpp::Publisher<pix_robobus_driver_msgs::msg::VaChassisWheelRpmFb>::SharedPtr va_chassis_wheel_rpm_fb_pub_;
  rclcpp::Publisher<pix_robobus_driver_msgs::msg::VaChassisOdoFb>::SharedPtr va_chassis_odo_fb_pub_;
  rclcpp::Publisher<pix_robobus_driver_msgs::msg::VcuTransfer>::SharedPtr vcu_transfer_pub_;
  rclcpp::Publisher<pix_robobus_driver_msgs::msg::VaChassisWheelTirePressFb>::SharedPtr va_chassis_wheel_tire_press_fb_pub_;
  rclcpp::Publisher<pix_robobus_driver_msgs::msg::VaChassisWheelAngleFb>::SharedPtr va_chassis_wheel_angle_fb_pub_;
  rclcpp::Publisher<pix_robobus_driver_msgs::msg::VaChassisWheelTorqueFb>::SharedPtr va_chassis_wheel_torque_fb_pub_;
  rclcpp::Publisher<pix_robobus_driver_msgs::msg::BcmMessage4>::SharedPtr bcm_message4_pub_;
  rclcpp::Publisher<pix_robobus_driver_msgs::msg::BcmMessage5>::SharedPtr bcm_message5_pub_;
  rclcpp::Publisher<pix_robobus_driver_msgs::msg::DpMessgae4>::SharedPtr dp_messgae4_pub_;
  rclcpp::Publisher<pix_robobus_driver_msgs::msg::DpMessgae5>::SharedPtr dp_messgae5_pub_;


  // can frame entities - publisher_msg_list
  VcuSoftVer vcu_soft_ver_parser_;
  AcMessage1 ac_message1_parser_;
  AcMessage2 ac_message2_parser_;
  VinResp1 vin_resp1_parser_;
  VinResp2 vin_resp2_parser_;
  VinResp3 vin_resp3_parser_;
  VehicleErrcode1 vehicle_errcode1_parser_;
  VehicleErrcode2 vehicle_errcode2_parser_;
  HistoricalVehiclefailures1 historical_vehiclefailures1_parser_;
  HistoricalVehiclefailures2 historical_vehiclefailures2_parser_;
  VaDriveStaFb va_drive_sta_fb_parser_;
  VaBrakeStaFb va_brake_sta_fb_parser_;
  VaSteerStaFb va_steer_sta_fb_parser_;
  VaVehicleWorkStaFb va_vehicle_work_sta_fb_parser_;
  VaPowerStaFb va_power_sta_fb_parser_;
  VaVehicleStaFb va_vehicle_sta_fb_parser_;
  VaVehicleFltSta va_vehicle_flt_sta_parser_;
  VaChassisWheelRpmFb va_chassis_wheel_rpm_fb_parser_;
  VaChassisOdoFb va_chassis_odo_fb_parser_;
  VcuTransfer vcu_transfer_parser_;
  VaChassisWheelTirePressFb va_chassis_wheel_tire_press_fb_parser_;
  VaChassisWheelAngleFb va_chassis_wheel_angle_fb_parser_;
  VaChassisWheelTorqueFb va_chassis_wheel_torque_fb_parser_;
  BcmMessage4 bcm_message4_parser_;
  BcmMessage5 bcm_message5_parser_;
  DpMessgae4 dp_messgae4_parser_;
  DpMessgae5 dp_messgae5_parser_;

  
public:
  ReportParser(const rclcpp::NodeOptions & node_option);

  // callback
  /// @brief callback function of can Frame msgs, to store the data to member variable
  void callbackCan(const can_msgs::msg::Frame::ConstSharedPtr & msg);
};
} // report_parser
} // pix_robobus_driver