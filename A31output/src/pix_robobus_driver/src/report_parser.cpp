#include <pix_robobus_driver/report_parser.hpp>

namespace pix_robobus_driver
{
namespace report_parser
{
ReportParser::ReportParser(const rclcpp::NodeOptions & node_option) 
: Node("report_parser", node_option)
{
  // ros params
  param_.base_frame_id = declare_parameter("base_frame_id", "base_link");
  param_.loop_rate = declare_parameter("loop_rate", 50.0);

  using std::placeholders::_1;

  /* subscriber */
  {
    // from pix driver autoware interface
    can_frame_sub_ = create_subscription<can_msgs::msg::Frame>(
      "input/can_rx", 500, std::bind(&ReportParser::callbackCan, this, _1));
  }

  /* publisher - publisher_instance_list*/
  {
    vcu_soft_ver_pub_ = create_publisher<pix_robobus_driver_msgs::msg::VcuSoftVer>("/pix_robobus/vcu_soft_ver", rclcpp::QoS{10});
    ac_message1_pub_ = create_publisher<pix_robobus_driver_msgs::msg::AcMessage1>("/pix_robobus/ac_message1", rclcpp::QoS{10});
    ac_message2_pub_ = create_publisher<pix_robobus_driver_msgs::msg::AcMessage2>("/pix_robobus/ac_message2", rclcpp::QoS{10});
    vin_resp1_pub_ = create_publisher<pix_robobus_driver_msgs::msg::VinResp1>("/pix_robobus/vin_resp1", rclcpp::QoS{10});
    vin_resp2_pub_ = create_publisher<pix_robobus_driver_msgs::msg::VinResp2>("/pix_robobus/vin_resp2", rclcpp::QoS{10});
    vin_resp3_pub_ = create_publisher<pix_robobus_driver_msgs::msg::VinResp3>("/pix_robobus/vin_resp3", rclcpp::QoS{10});
    vehicle_errcode1_pub_ = create_publisher<pix_robobus_driver_msgs::msg::VehicleErrcode1>("/pix_robobus/vehicle_errcode1", rclcpp::QoS{10});
    vehicle_errcode2_pub_ = create_publisher<pix_robobus_driver_msgs::msg::VehicleErrcode2>("/pix_robobus/vehicle_errcode2", rclcpp::QoS{10});
    historical_vehiclefailures1_pub_ = create_publisher<pix_robobus_driver_msgs::msg::HistoricalVehiclefailures1>("/pix_robobus/historical_vehiclefailures1", rclcpp::QoS{10});
    historical_vehiclefailures2_pub_ = create_publisher<pix_robobus_driver_msgs::msg::HistoricalVehiclefailures2>("/pix_robobus/historical_vehiclefailures2", rclcpp::QoS{10});
    va_drive_sta_fb_pub_ = create_publisher<pix_robobus_driver_msgs::msg::VaDriveStaFb>("/pix_robobus/va_drive_sta_fb", rclcpp::QoS{10});
    va_brake_sta_fb_pub_ = create_publisher<pix_robobus_driver_msgs::msg::VaBrakeStaFb>("/pix_robobus/va_brake_sta_fb", rclcpp::QoS{10});
    va_steer_sta_fb_pub_ = create_publisher<pix_robobus_driver_msgs::msg::VaSteerStaFb>("/pix_robobus/va_steer_sta_fb", rclcpp::QoS{10});
    va_vehicle_work_sta_fb_pub_ = create_publisher<pix_robobus_driver_msgs::msg::VaVehicleWorkStaFb>("/pix_robobus/va_vehicle_work_sta_fb", rclcpp::QoS{10});
    va_power_sta_fb_pub_ = create_publisher<pix_robobus_driver_msgs::msg::VaPowerStaFb>("/pix_robobus/va_power_sta_fb", rclcpp::QoS{10});
    va_vehicle_sta_fb_pub_ = create_publisher<pix_robobus_driver_msgs::msg::VaVehicleStaFb>("/pix_robobus/va_vehicle_sta_fb", rclcpp::QoS{10});
    va_vehicle_flt_sta_pub_ = create_publisher<pix_robobus_driver_msgs::msg::VaVehicleFltSta>("/pix_robobus/va_vehicle_flt_sta", rclcpp::QoS{10});
    va_chassis_wheel_rpm_fb_pub_ = create_publisher<pix_robobus_driver_msgs::msg::VaChassisWheelRpmFb>("/pix_robobus/va_chassis_wheel_rpm_fb", rclcpp::QoS{10});
    va_chassis_odo_fb_pub_ = create_publisher<pix_robobus_driver_msgs::msg::VaChassisOdoFb>("/pix_robobus/va_chassis_odo_fb", rclcpp::QoS{10});
    vcu_transfer_pub_ = create_publisher<pix_robobus_driver_msgs::msg::VcuTransfer>("/pix_robobus/vcu_transfer", rclcpp::QoS{10});
    va_chassis_wheel_tire_press_fb_pub_ = create_publisher<pix_robobus_driver_msgs::msg::VaChassisWheelTirePressFb>("/pix_robobus/va_chassis_wheel_tire_press_fb", rclcpp::QoS{10});
    va_chassis_wheel_angle_fb_pub_ = create_publisher<pix_robobus_driver_msgs::msg::VaChassisWheelAngleFb>("/pix_robobus/va_chassis_wheel_angle_fb", rclcpp::QoS{10});
    va_chassis_wheel_torque_fb_pub_ = create_publisher<pix_robobus_driver_msgs::msg::VaChassisWheelTorqueFb>("/pix_robobus/va_chassis_wheel_torque_fb", rclcpp::QoS{10});
    bcm_message4_pub_ = create_publisher<pix_robobus_driver_msgs::msg::BcmMessage4>("/pix_robobus/bcm_message4", rclcpp::QoS{10});
    bcm_message5_pub_ = create_publisher<pix_robobus_driver_msgs::msg::BcmMessage5>("/pix_robobus/bcm_message5", rclcpp::QoS{10});
    dp_messgae4_pub_ = create_publisher<pix_robobus_driver_msgs::msg::DpMessgae4>("/pix_robobus/dp_messgae4", rclcpp::QoS{10});
    dp_messgae5_pub_ = create_publisher<pix_robobus_driver_msgs::msg::DpMessgae5>("/pix_robobus/dp_messgae5", rclcpp::QoS{10});
 
  }
}

// callback can
void ReportParser::callbackCan(const can_msgs::msg::Frame::ConstSharedPtr & msg)
{
  std_msgs::msg::Header header;
  header.frame_id = param_.base_frame_id;
  header.stamp = msg->header.stamp;

  // pix_msg  - report_msg_list
  pix_robobus_driver_msgs::msg::VcuSoftVer vcu_soft_ver_msg;
  pix_robobus_driver_msgs::msg::AcMessage1 ac_message1_msg;
  pix_robobus_driver_msgs::msg::AcMessage2 ac_message2_msg;
  pix_robobus_driver_msgs::msg::VinResp1 vin_resp1_msg;
  pix_robobus_driver_msgs::msg::VinResp2 vin_resp2_msg;
  pix_robobus_driver_msgs::msg::VinResp3 vin_resp3_msg;
  pix_robobus_driver_msgs::msg::VehicleErrcode1 vehicle_errcode1_msg;
  pix_robobus_driver_msgs::msg::VehicleErrcode2 vehicle_errcode2_msg;
  pix_robobus_driver_msgs::msg::HistoricalVehiclefailures1 historical_vehiclefailures1_msg;
  pix_robobus_driver_msgs::msg::HistoricalVehiclefailures2 historical_vehiclefailures2_msg;
  pix_robobus_driver_msgs::msg::VaDriveStaFb va_drive_sta_fb_msg;
  pix_robobus_driver_msgs::msg::VaBrakeStaFb va_brake_sta_fb_msg;
  pix_robobus_driver_msgs::msg::VaSteerStaFb va_steer_sta_fb_msg;
  pix_robobus_driver_msgs::msg::VaVehicleWorkStaFb va_vehicle_work_sta_fb_msg;
  pix_robobus_driver_msgs::msg::VaPowerStaFb va_power_sta_fb_msg;
  pix_robobus_driver_msgs::msg::VaVehicleStaFb va_vehicle_sta_fb_msg;
  pix_robobus_driver_msgs::msg::VaVehicleFltSta va_vehicle_flt_sta_msg;
  pix_robobus_driver_msgs::msg::VaChassisWheelRpmFb va_chassis_wheel_rpm_fb_msg;
  pix_robobus_driver_msgs::msg::VaChassisOdoFb va_chassis_odo_fb_msg;
  pix_robobus_driver_msgs::msg::VcuTransfer vcu_transfer_msg;
  pix_robobus_driver_msgs::msg::VaChassisWheelTirePressFb va_chassis_wheel_tire_press_fb_msg;
  pix_robobus_driver_msgs::msg::VaChassisWheelAngleFb va_chassis_wheel_angle_fb_msg;
  pix_robobus_driver_msgs::msg::VaChassisWheelTorqueFb va_chassis_wheel_torque_fb_msg;
  pix_robobus_driver_msgs::msg::BcmMessage4 bcm_message4_msg;
  pix_robobus_driver_msgs::msg::BcmMessage5 bcm_message5_msg;
  pix_robobus_driver_msgs::msg::DpMessgae4 dp_messgae4_msg;
  pix_robobus_driver_msgs::msg::DpMessgae5 dp_messgae5_msg;


  // can - parser_case_code_list
  uint8_t byte_temp[8];
  switch (msg->id)
  {

  case VcuSoftVer::ID:
    for(uint i=0;i<8;i++)
    {
      byte_temp[i] = msg->data[i];
    }
    vcu_soft_ver_parser_.update_bytes(byte_temp);
    vcu_soft_ver_parser_.Parse();

    vcu_soft_ver_msg.header = header;
    vcu_soft_ver_msg.vehicle_parameter = vcu_soft_ver_parser_.vehicle_parameter_;
    vcu_soft_ver_msg.reserve10_f2 = vcu_soft_ver_parser_.reserve10_f2_;
    vcu_soft_ver_msg.version_year = vcu_soft_ver_parser_.version_year_;
    vcu_soft_ver_msg.version_month = vcu_soft_ver_parser_.version_month_;
    vcu_soft_ver_msg.version_day = vcu_soft_ver_parser_.version_day_;
    vcu_soft_ver_msg.version_main = vcu_soft_ver_parser_.version_main_;
    vcu_soft_ver_msg.version_sub = vcu_soft_ver_parser_.version_sub_;
    vcu_soft_ver_msg.version_patch = vcu_soft_ver_parser_.version_patch_;

    vcu_soft_ver_pub_->publish(vcu_soft_ver_msg);
    break;
    
  case AcMessage1::ID:
    for(uint i=0;i<8;i++)
    {
      byte_temp[i] = msg->data[i];
    }
    ac_message1_parser_.update_bytes(byte_temp);
    ac_message1_parser_.Parse();

    ac_message1_msg.header = header;
    ac_message1_msg.defrost_fdk = ac_message1_parser_.defrost_fdk_;
    ac_message1_msg.air_cod_sta = ac_message1_parser_.air_cod_sta_;
    ac_message1_msg.air_cod_gear_sta = ac_message1_parser_.air_cod_gear_sta_;
    ac_message1_msg.air_cod_mod_sta = ac_message1_parser_.air_cod_mod_sta_;
    ac_message1_msg.air_cod_temp_sta = ac_message1_parser_.air_cod_temp_sta_;
    ac_message1_msg.in_loop_mod_sta = ac_message1_parser_.in_loop_mod_sta_;
    ac_message1_msg.reserve = ac_message1_parser_.reserve_;

    ac_message1_pub_->publish(ac_message1_msg);
    break;
    
  case AcMessage2::ID:
    for(uint i=0;i<8;i++)
    {
      byte_temp[i] = msg->data[i];
    }
    ac_message2_parser_.update_bytes(byte_temp);
    ac_message2_parser_.Parse();

    ac_message2_msg.header = header;
    ac_message2_msg.reserve = ac_message2_parser_.reserve_;
    ac_message2_msg.fan_temp = ac_message2_parser_.fan_temp_;
    ac_message2_msg.ac_out_temp = ac_message2_parser_.ac_out_temp_;
    ac_message2_msg.ac_in_temp = ac_message2_parser_.ac_in_temp_;
    ac_message2_msg.ac_hardware = ac_message2_parser_.ac_hardware_;
    ac_message2_msg.ac_software = ac_message2_parser_.ac_software_;

    ac_message2_pub_->publish(ac_message2_msg);
    break;
    
  case VinResp1::ID:
    for(uint i=0;i<8;i++)
    {
      byte_temp[i] = msg->data[i];
    }
    vin_resp1_parser_.update_bytes(byte_temp);
    vin_resp1_parser_.Parse();

    vin_resp1_msg.header = header;
    vin_resp1_msg.vin_00 = vin_resp1_parser_.vin_00_;
    vin_resp1_msg.vin_01 = vin_resp1_parser_.vin_01_;
    vin_resp1_msg.vin_02 = vin_resp1_parser_.vin_02_;
    vin_resp1_msg.vin_03 = vin_resp1_parser_.vin_03_;
    vin_resp1_msg.vin_04 = vin_resp1_parser_.vin_04_;
    vin_resp1_msg.vin_05 = vin_resp1_parser_.vin_05_;
    vin_resp1_msg.vin_06 = vin_resp1_parser_.vin_06_;
    vin_resp1_msg.vin_07 = vin_resp1_parser_.vin_07_;

    vin_resp1_pub_->publish(vin_resp1_msg);
    break;
    
  case VinResp2::ID:
    for(uint i=0;i<8;i++)
    {
      byte_temp[i] = msg->data[i];
    }
    vin_resp2_parser_.update_bytes(byte_temp);
    vin_resp2_parser_.Parse();

    vin_resp2_msg.header = header;
    vin_resp2_msg.vin_08 = vin_resp2_parser_.vin_08_;
    vin_resp2_msg.vin_09 = vin_resp2_parser_.vin_09_;
    vin_resp2_msg.vin_10 = vin_resp2_parser_.vin_10_;
    vin_resp2_msg.vin_11 = vin_resp2_parser_.vin_11_;
    vin_resp2_msg.vin_12 = vin_resp2_parser_.vin_12_;
    vin_resp2_msg.vin_13 = vin_resp2_parser_.vin_13_;
    vin_resp2_msg.vin_14 = vin_resp2_parser_.vin_14_;
    vin_resp2_msg.vin_15 = vin_resp2_parser_.vin_15_;

    vin_resp2_pub_->publish(vin_resp2_msg);
    break;
    
  case VinResp3::ID:
    for(uint i=0;i<8;i++)
    {
      byte_temp[i] = msg->data[i];
    }
    vin_resp3_parser_.update_bytes(byte_temp);
    vin_resp3_parser_.Parse();

    vin_resp3_msg.header = header;
    vin_resp3_msg.vin_16 = vin_resp3_parser_.vin_16_;

    vin_resp3_pub_->publish(vin_resp3_msg);
    break;
    
  case VehicleErrcode1::ID:
    for(uint i=0;i<8;i++)
    {
      byte_temp[i] = msg->data[i];
    }
    vehicle_errcode1_parser_.update_bytes(byte_temp);
    vehicle_errcode1_parser_.Parse();

    vehicle_errcode1_msg.header = header;
    vehicle_errcode1_msg.flmc_hardware_fault = vehicle_errcode1_parser_.flmc_hardware_fault_;
    vehicle_errcode1_msg.flmc_tem_fault = vehicle_errcode1_parser_.flmc_tem_fault_;
    vehicle_errcode1_msg.flm_tem_fault = vehicle_errcode1_parser_.flm_tem_fault_;
    vehicle_errcode1_msg.rlmc_hardware_fault = vehicle_errcode1_parser_.rlmc_hardware_fault_;
    vehicle_errcode1_msg.rlmc_tem_fault = vehicle_errcode1_parser_.rlmc_tem_fault_;
    vehicle_errcode1_msg.rlm_tem_fault = vehicle_errcode1_parser_.rlm_tem_fault_;
    vehicle_errcode1_msg.frmc_hardware_fault = vehicle_errcode1_parser_.frmc_hardware_fault_;
    vehicle_errcode1_msg.frmc_tem_fault = vehicle_errcode1_parser_.frmc_tem_fault_;
    vehicle_errcode1_msg.frm_tem_fault = vehicle_errcode1_parser_.frm_tem_fault_;
    vehicle_errcode1_msg.rrmc_hardware_fault = vehicle_errcode1_parser_.rrmc_hardware_fault_;
    vehicle_errcode1_msg.rrmc_tem_fault = vehicle_errcode1_parser_.rrmc_tem_fault_;
    vehicle_errcode1_msg.rrm_tem_fault = vehicle_errcode1_parser_.rrm_tem_fault_;
    vehicle_errcode1_msg.flmc_network_fault = vehicle_errcode1_parser_.flmc_network_fault_;
    vehicle_errcode1_msg.frmc_network_fault = vehicle_errcode1_parser_.frmc_network_fault_;
    vehicle_errcode1_msg.rlmc_network_fault = vehicle_errcode1_parser_.rlmc_network_fault_;
    vehicle_errcode1_msg.rrmc_network_fault = vehicle_errcode1_parser_.rrmc_network_fault_;
    vehicle_errcode1_msg.fr_steer_hardware_fault = vehicle_errcode1_parser_.fr_steer_hardware_fault_;
    vehicle_errcode1_msg.rr_steer_hardware_fault = vehicle_errcode1_parser_.rr_steer_hardware_fault_;
    vehicle_errcode1_msg.fr_steer_network_fault = vehicle_errcode1_parser_.fr_steer_network_fault_;
    vehicle_errcode1_msg.rr_steer_network_fault = vehicle_errcode1_parser_.rr_steer_network_fault_;
    vehicle_errcode1_msg.brake_hardware_fault = vehicle_errcode1_parser_.brake_hardware_fault_;
    vehicle_errcode1_msg.brake_high_tem_fault = vehicle_errcode1_parser_.brake_high_tem_fault_;
    vehicle_errcode1_msg.brake_luid_level_low = vehicle_errcode1_parser_.brake_luid_level_low_;
    vehicle_errcode1_msg.brake_network_fault = vehicle_errcode1_parser_.brake_network_fault_;
    vehicle_errcode1_msg.park_hardware_fault = vehicle_errcode1_parser_.park_hardware_fault_;
    vehicle_errcode1_msg.park_network_fault = vehicle_errcode1_parser_.park_network_fault_;
    vehicle_errcode1_msg.rcu_network_fault = vehicle_errcode1_parser_.rcu_network_fault_;
    vehicle_errcode1_msg.rcu_weak_signal = vehicle_errcode1_parser_.rcu_weak_signal_;
    vehicle_errcode1_msg.rcu_elec_low_alarm = vehicle_errcode1_parser_.rcu_elec_low_alarm_;
    vehicle_errcode1_msg.spare1 = vehicle_errcode1_parser_.spare1_;
    vehicle_errcode1_msg.spare2 = vehicle_errcode1_parser_.spare2_;
    vehicle_errcode1_msg.bms_network_fault = vehicle_errcode1_parser_.bms_network_fault_;
    vehicle_errcode1_msg.bms_insulation_fault = vehicle_errcode1_parser_.bms_insulation_fault_;
    vehicle_errcode1_msg.bms_ocv_cell = vehicle_errcode1_parser_.bms_ocv_cell_;
    vehicle_errcode1_msg.bms_odv_cell = vehicle_errcode1_parser_.bms_odv_cell_;
    vehicle_errcode1_msg.bms_ocv_batt = vehicle_errcode1_parser_.bms_ocv_batt_;
    vehicle_errcode1_msg.bms_odv_batt = vehicle_errcode1_parser_.bms_odv_batt_;
    vehicle_errcode1_msg.bms_cell_volt_diff = vehicle_errcode1_parser_.bms_cell_volt_diff_;
    vehicle_errcode1_msg.bms_temp_h = vehicle_errcode1_parser_.bms_temp_h_;
    vehicle_errcode1_msg.bms_temp_l = vehicle_errcode1_parser_.bms_temp_l_;
    vehicle_errcode1_msg.bms_temp_diff = vehicle_errcode1_parser_.bms_temp_diff_;
    vehicle_errcode1_msg.bms_war_chg_overcurrent = vehicle_errcode1_parser_.bms_war_chg_overcurrent_;
    vehicle_errcode1_msg.bms_soc_h = vehicle_errcode1_parser_.bms_soc_h_;
    vehicle_errcode1_msg.bms_soc_l = vehicle_errcode1_parser_.bms_soc_l_;
    vehicle_errcode1_msg.bms_time_of_heating_too_long = vehicle_errcode1_parser_.bms_time_of_heating_too_long_;
    vehicle_errcode1_msg.bms_soc_break = vehicle_errcode1_parser_.bms_soc_break_;
    vehicle_errcode1_msg.bms_dis_char_over_cur = vehicle_errcode1_parser_.bms_dis_char_over_cur_;
    vehicle_errcode1_msg.bms_char_over_cur_slow = vehicle_errcode1_parser_.bms_char_over_cur_slow_;
    vehicle_errcode1_msg.bms_fast_char_over_cur = vehicle_errcode1_parser_.bms_fast_char_over_cur_;
    vehicle_errcode1_msg.bms_alm_sense_cell = vehicle_errcode1_parser_.bms_alm_sense_cell_;
    vehicle_errcode1_msg.bms_alm_sense_temp = vehicle_errcode1_parser_.bms_alm_sense_temp_;
    vehicle_errcode1_msg.bms_alm_sense_curr = vehicle_errcode1_parser_.bms_alm_sense_curr_;
    vehicle_errcode1_msg.bms_hvil = vehicle_errcode1_parser_.bms_hvil_;
    vehicle_errcode1_msg.bms_war_in_can_fault = vehicle_errcode1_parser_.bms_war_in_can_fault_;
    vehicle_errcode1_msg.bms_lst_com_with_obc = vehicle_errcode1_parser_.bms_lst_com_with_obc_;
    vehicle_errcode1_msg.bms_lst_com_with_vcu = vehicle_errcode1_parser_.bms_lst_com_with_vcu_;
    vehicle_errcode1_msg.bms_precharger_fault = vehicle_errcode1_parser_.bms_precharger_fault_;
    vehicle_errcode1_msg.bms_pos_relay_conglutination = vehicle_errcode1_parser_.bms_pos_relay_conglutination_;
    vehicle_errcode1_msg.bms_neg_relay_conglutination = vehicle_errcode1_parser_.bms_neg_relay_conglutination_;
    vehicle_errcode1_msg.spare3 = vehicle_errcode1_parser_.spare3_;
    vehicle_errcode1_msg.spare4 = vehicle_errcode1_parser_.spare4_;
    vehicle_errcode1_msg.dcdc_high_tem_alarm = vehicle_errcode1_parser_.dcdc_high_tem_alarm_;
    vehicle_errcode1_msg.dcdc_hardware_fault = vehicle_errcode1_parser_.dcdc_hardware_fault_;
    vehicle_errcode1_msg.dcdc_network_fault = vehicle_errcode1_parser_.dcdc_network_fault_;

    vehicle_errcode1_pub_->publish(vehicle_errcode1_msg);
    break;
    
  case VehicleErrcode2::ID:
    for(uint i=0;i<8;i++)
    {
      byte_temp[i] = msg->data[i];
    }
    vehicle_errcode2_parser_.update_bytes(byte_temp);
    vehicle_errcode2_parser_.Parse();

    vehicle_errcode2_msg.header = header;
    vehicle_errcode2_msg.obc_network_fault = vehicle_errcode2_parser_.obc_network_fault_;
    vehicle_errcode2_msg.obc_hardware_fault = vehicle_errcode2_parser_.obc_hardware_fault_;
    vehicle_errcode2_msg.spare5 = vehicle_errcode2_parser_.spare5_;
    vehicle_errcode2_msg.spare6 = vehicle_errcode2_parser_.spare6_;
    vehicle_errcode2_msg.spare7 = vehicle_errcode2_parser_.spare7_;
    vehicle_errcode2_msg.spare8 = vehicle_errcode2_parser_.spare8_;
    vehicle_errcode2_msg.dp_hardware_fault = vehicle_errcode2_parser_.dp_hardware_fault_;
    vehicle_errcode2_msg.dp_network_fault = vehicle_errcode2_parser_.dp_network_fault_;
    vehicle_errcode2_msg.spare9 = vehicle_errcode2_parser_.spare9_;
    vehicle_errcode2_msg.spare10 = vehicle_errcode2_parser_.spare10_;
    vehicle_errcode2_msg.spare11 = vehicle_errcode2_parser_.spare11_;
    vehicle_errcode2_msg.spare12 = vehicle_errcode2_parser_.spare12_;
    vehicle_errcode2_msg.spare13 = vehicle_errcode2_parser_.spare13_;
    vehicle_errcode2_msg.spare14 = vehicle_errcode2_parser_.spare14_;
    vehicle_errcode2_msg.bcm_hardware_fault = vehicle_errcode2_parser_.bcm_hardware_fault_;
    vehicle_errcode2_msg.bcm_network_fault = vehicle_errcode2_parser_.bcm_network_fault_;
    vehicle_errcode2_msg.spare15 = vehicle_errcode2_parser_.spare15_;
    vehicle_errcode2_msg.spare16 = vehicle_errcode2_parser_.spare16_;
    vehicle_errcode2_msg.spare17 = vehicle_errcode2_parser_.spare17_;
    vehicle_errcode2_msg.spare18 = vehicle_errcode2_parser_.spare18_;
    vehicle_errcode2_msg.spare19 = vehicle_errcode2_parser_.spare19_;
    vehicle_errcode2_msg.spare20 = vehicle_errcode2_parser_.spare20_;
    vehicle_errcode2_msg.dcu_network_fault = vehicle_errcode2_parser_.dcu_network_fault_;
    vehicle_errcode2_msg.dcu_hardware_fault = vehicle_errcode2_parser_.dcu_hardware_fault_;
    vehicle_errcode2_msg.spare21 = vehicle_errcode2_parser_.spare21_;
    vehicle_errcode2_msg.avas_network_fault = vehicle_errcode2_parser_.avas_network_fault_;
    vehicle_errcode2_msg.avas_hardware_fault = vehicle_errcode2_parser_.avas_hardware_fault_;
    vehicle_errcode2_msg.spare22 = vehicle_errcode2_parser_.spare22_;
    vehicle_errcode2_msg.spare23 = vehicle_errcode2_parser_.spare23_;
    vehicle_errcode2_msg.iis_hardware_fault = vehicle_errcode2_parser_.iis_hardware_fault_;
    vehicle_errcode2_msg.iis_network_fault = vehicle_errcode2_parser_.iis_network_fault_;
    vehicle_errcode2_msg.spare24 = vehicle_errcode2_parser_.spare24_;
    vehicle_errcode2_msg.spare25 = vehicle_errcode2_parser_.spare25_;
    vehicle_errcode2_msg.spare26 = vehicle_errcode2_parser_.spare26_;
    vehicle_errcode2_msg.spare27 = vehicle_errcode2_parser_.spare27_;
    vehicle_errcode2_msg.spare28 = vehicle_errcode2_parser_.spare28_;
    vehicle_errcode2_msg.spare29 = vehicle_errcode2_parser_.spare29_;
    vehicle_errcode2_msg.spare30 = vehicle_errcode2_parser_.spare30_;
    vehicle_errcode2_msg.ac_hardware_fault = vehicle_errcode2_parser_.ac_hardware_fault_;
    vehicle_errcode2_msg.ac_network_fault = vehicle_errcode2_parser_.ac_network_fault_;
    vehicle_errcode2_msg.spare31 = vehicle_errcode2_parser_.spare31_;
    vehicle_errcode2_msg.spare32 = vehicle_errcode2_parser_.spare32_;
    vehicle_errcode2_msg.spare33 = vehicle_errcode2_parser_.spare33_;
    vehicle_errcode2_msg.spare34 = vehicle_errcode2_parser_.spare34_;
    vehicle_errcode2_msg.spare35 = vehicle_errcode2_parser_.spare35_;
    vehicle_errcode2_msg.spare36 = vehicle_errcode2_parser_.spare36_;
    vehicle_errcode2_msg.lv_battery_low_voltage_fault = vehicle_errcode2_parser_.lv_battery_low_voltage_fault_;
    vehicle_errcode2_msg.lv_battery_high_voltage_fault = vehicle_errcode2_parser_.lv_battery_high_voltage_fault_;
    vehicle_errcode2_msg.spare37 = vehicle_errcode2_parser_.spare37_;
    vehicle_errcode2_msg.spare38 = vehicle_errcode2_parser_.spare38_;
    vehicle_errcode2_msg.spare39 = vehicle_errcode2_parser_.spare39_;
    vehicle_errcode2_msg.spare40 = vehicle_errcode2_parser_.spare40_;
    vehicle_errcode2_msg.spare41 = vehicle_errcode2_parser_.spare41_;
    vehicle_errcode2_msg.spare42 = vehicle_errcode2_parser_.spare42_;
    vehicle_errcode2_msg.spare43 = vehicle_errcode2_parser_.spare43_;
    vehicle_errcode2_msg.spare44 = vehicle_errcode2_parser_.spare44_;
    vehicle_errcode2_msg.spare45 = vehicle_errcode2_parser_.spare45_;
    vehicle_errcode2_msg.spare46 = vehicle_errcode2_parser_.spare46_;
    vehicle_errcode2_msg.spare47 = vehicle_errcode2_parser_.spare47_;
    vehicle_errcode2_msg.spare48 = vehicle_errcode2_parser_.spare48_;
    vehicle_errcode2_msg.spare49 = vehicle_errcode2_parser_.spare49_;
    vehicle_errcode2_msg.spare50 = vehicle_errcode2_parser_.spare50_;
    vehicle_errcode2_msg.spare51 = vehicle_errcode2_parser_.spare51_;
    vehicle_errcode2_msg.spare52 = vehicle_errcode2_parser_.spare52_;

    vehicle_errcode2_pub_->publish(vehicle_errcode2_msg);
    break;
    
  case HistoricalVehiclefailures1::ID:
    for(uint i=0;i<8;i++)
    {
      byte_temp[i] = msg->data[i];
    }
    historical_vehiclefailures1_parser_.update_bytes(byte_temp);
    historical_vehiclefailures1_parser_.Parse();

    historical_vehiclefailures1_msg.header = header;
    historical_vehiclefailures1_msg.flmc_hardware_fault51_c = historical_vehiclefailures1_parser_.flmc_hardware_fault51_c_;
    historical_vehiclefailures1_msg.flmc_tem_fault51_c = historical_vehiclefailures1_parser_.flmc_tem_fault51_c_;
    historical_vehiclefailures1_msg.flm_tem_fault51_c = historical_vehiclefailures1_parser_.flm_tem_fault51_c_;
    historical_vehiclefailures1_msg.rlmc_hardware_fault51_c = historical_vehiclefailures1_parser_.rlmc_hardware_fault51_c_;
    historical_vehiclefailures1_msg.rlmc_tem_fault51_c = historical_vehiclefailures1_parser_.rlmc_tem_fault51_c_;
    historical_vehiclefailures1_msg.rlm_tem_fault51_c = historical_vehiclefailures1_parser_.rlm_tem_fault51_c_;
    historical_vehiclefailures1_msg.frmc_hardware_fault51_c = historical_vehiclefailures1_parser_.frmc_hardware_fault51_c_;
    historical_vehiclefailures1_msg.frmc_tem_fault51_c = historical_vehiclefailures1_parser_.frmc_tem_fault51_c_;
    historical_vehiclefailures1_msg.frm_tem_fault51_c = historical_vehiclefailures1_parser_.frm_tem_fault51_c_;
    historical_vehiclefailures1_msg.rrmc_hardware_fault51_c = historical_vehiclefailures1_parser_.rrmc_hardware_fault51_c_;
    historical_vehiclefailures1_msg.rrmc_tem_fault51_c = historical_vehiclefailures1_parser_.rrmc_tem_fault51_c_;
    historical_vehiclefailures1_msg.rrm_tem_fault51_c = historical_vehiclefailures1_parser_.rrm_tem_fault51_c_;
    historical_vehiclefailures1_msg.flmc_network_fault51_c = historical_vehiclefailures1_parser_.flmc_network_fault51_c_;
    historical_vehiclefailures1_msg.frmc_network_fault51_c = historical_vehiclefailures1_parser_.frmc_network_fault51_c_;
    historical_vehiclefailures1_msg.rlmc_network_fault51_c = historical_vehiclefailures1_parser_.rlmc_network_fault51_c_;
    historical_vehiclefailures1_msg.rrmc_network_fault51_c = historical_vehiclefailures1_parser_.rrmc_network_fault51_c_;
    historical_vehiclefailures1_msg.fr_steer_hardware_fault51_c = historical_vehiclefailures1_parser_.fr_steer_hardware_fault51_c_;
    historical_vehiclefailures1_msg.rr_steer_hardware_fault51_c = historical_vehiclefailures1_parser_.rr_steer_hardware_fault51_c_;
    historical_vehiclefailures1_msg.fr_steer_network_fault51_c = historical_vehiclefailures1_parser_.fr_steer_network_fault51_c_;
    historical_vehiclefailures1_msg.rr_steer_network_fault51_c = historical_vehiclefailures1_parser_.rr_steer_network_fault51_c_;
    historical_vehiclefailures1_msg.brake_hardware_fault51_c = historical_vehiclefailures1_parser_.brake_hardware_fault51_c_;
    historical_vehiclefailures1_msg.brake_high_tem_fault51_c = historical_vehiclefailures1_parser_.brake_high_tem_fault51_c_;
    historical_vehiclefailures1_msg.brake_luid_level_low51_c = historical_vehiclefailures1_parser_.brake_luid_level_low51_c_;
    historical_vehiclefailures1_msg.brake_network_fault51_c = historical_vehiclefailures1_parser_.brake_network_fault51_c_;
    historical_vehiclefailures1_msg.park_hardware_fault51_c = historical_vehiclefailures1_parser_.park_hardware_fault51_c_;
    historical_vehiclefailures1_msg.park_network_fault51_c = historical_vehiclefailures1_parser_.park_network_fault51_c_;
    historical_vehiclefailures1_msg.rcu_network_fault51_c = historical_vehiclefailures1_parser_.rcu_network_fault51_c_;
    historical_vehiclefailures1_msg.rcu_weak_signal51_c = historical_vehiclefailures1_parser_.rcu_weak_signal51_c_;
    historical_vehiclefailures1_msg.rcu_elec_low_alarm51_c = historical_vehiclefailures1_parser_.rcu_elec_low_alarm51_c_;
    historical_vehiclefailures1_msg.spare151_c = historical_vehiclefailures1_parser_.spare151_c_;
    historical_vehiclefailures1_msg.spare251_c = historical_vehiclefailures1_parser_.spare251_c_;
    historical_vehiclefailures1_msg.bms_network_fault51_c = historical_vehiclefailures1_parser_.bms_network_fault51_c_;
    historical_vehiclefailures1_msg.bms_insulation_fault51_c = historical_vehiclefailures1_parser_.bms_insulation_fault51_c_;
    historical_vehiclefailures1_msg.bms_ocv_cell51_c = historical_vehiclefailures1_parser_.bms_ocv_cell51_c_;
    historical_vehiclefailures1_msg.bms_odv_cell51_c = historical_vehiclefailures1_parser_.bms_odv_cell51_c_;
    historical_vehiclefailures1_msg.bms_ocv_batt51_c = historical_vehiclefailures1_parser_.bms_ocv_batt51_c_;
    historical_vehiclefailures1_msg.bms_odv_batt51_c = historical_vehiclefailures1_parser_.bms_odv_batt51_c_;
    historical_vehiclefailures1_msg.bms_cell_volt_diff51_c = historical_vehiclefailures1_parser_.bms_cell_volt_diff51_c_;
    historical_vehiclefailures1_msg.bms_temp_h51_c = historical_vehiclefailures1_parser_.bms_temp_h51_c_;
    historical_vehiclefailures1_msg.bms_temp_l51_c = historical_vehiclefailures1_parser_.bms_temp_l51_c_;
    historical_vehiclefailures1_msg.bms_temp_diff51_c = historical_vehiclefailures1_parser_.bms_temp_diff51_c_;
    historical_vehiclefailures1_msg.bms_war_chg_overcurrent51_c = historical_vehiclefailures1_parser_.bms_war_chg_overcurrent51_c_;
    historical_vehiclefailures1_msg.bms_soc_h51_c = historical_vehiclefailures1_parser_.bms_soc_h51_c_;
    historical_vehiclefailures1_msg.bms_soc_l51_c = historical_vehiclefailures1_parser_.bms_soc_l51_c_;
    historical_vehiclefailures1_msg.bms_time_of_heating_too_long51_c = historical_vehiclefailures1_parser_.bms_time_of_heating_too_long51_c_;
    historical_vehiclefailures1_msg.bms_soc_break51_c = historical_vehiclefailures1_parser_.bms_soc_break51_c_;
    historical_vehiclefailures1_msg.bms_dis_char_over_cur51_c = historical_vehiclefailures1_parser_.bms_dis_char_over_cur51_c_;
    historical_vehiclefailures1_msg.bms_char_over_cur_slow51_c = historical_vehiclefailures1_parser_.bms_char_over_cur_slow51_c_;
    historical_vehiclefailures1_msg.bms_fast_char_over_cur51_c = historical_vehiclefailures1_parser_.bms_fast_char_over_cur51_c_;
    historical_vehiclefailures1_msg.bms_alm_sense_cell51_c = historical_vehiclefailures1_parser_.bms_alm_sense_cell51_c_;
    historical_vehiclefailures1_msg.bms_alm_sense_temp51_c = historical_vehiclefailures1_parser_.bms_alm_sense_temp51_c_;
    historical_vehiclefailures1_msg.bms_alm_sense_curr51_c = historical_vehiclefailures1_parser_.bms_alm_sense_curr51_c_;
    historical_vehiclefailures1_msg.bms_hvil51_c = historical_vehiclefailures1_parser_.bms_hvil51_c_;
    historical_vehiclefailures1_msg.bms_war_in_can_fault51_c = historical_vehiclefailures1_parser_.bms_war_in_can_fault51_c_;
    historical_vehiclefailures1_msg.bms_lst_com_with_obc51_c = historical_vehiclefailures1_parser_.bms_lst_com_with_obc51_c_;
    historical_vehiclefailures1_msg.bms_lst_com_with_vcu51_c = historical_vehiclefailures1_parser_.bms_lst_com_with_vcu51_c_;
    historical_vehiclefailures1_msg.bms_precharger_fault51_c = historical_vehiclefailures1_parser_.bms_precharger_fault51_c_;
    historical_vehiclefailures1_msg.bms_pos_relay_conglutination51_c = historical_vehiclefailures1_parser_.bms_pos_relay_conglutination51_c_;
    historical_vehiclefailures1_msg.bms_neg_relay_conglutination51_c = historical_vehiclefailures1_parser_.bms_neg_relay_conglutination51_c_;
    historical_vehiclefailures1_msg.spare351_c = historical_vehiclefailures1_parser_.spare351_c_;
    historical_vehiclefailures1_msg.spare451_c = historical_vehiclefailures1_parser_.spare451_c_;
    historical_vehiclefailures1_msg.dcdc_high_tem_alarm51_c = historical_vehiclefailures1_parser_.dcdc_high_tem_alarm51_c_;
    historical_vehiclefailures1_msg.dcdc_hardware_fault51_c = historical_vehiclefailures1_parser_.dcdc_hardware_fault51_c_;
    historical_vehiclefailures1_msg.dcdc_network_fault51_c = historical_vehiclefailures1_parser_.dcdc_network_fault51_c_;

    historical_vehiclefailures1_pub_->publish(historical_vehiclefailures1_msg);
    break;
    
  case HistoricalVehiclefailures2::ID:
    for(uint i=0;i<8;i++)
    {
      byte_temp[i] = msg->data[i];
    }
    historical_vehiclefailures2_parser_.update_bytes(byte_temp);
    historical_vehiclefailures2_parser_.Parse();

    historical_vehiclefailures2_msg.header = header;
    historical_vehiclefailures2_msg.obc_network_fault51_d = historical_vehiclefailures2_parser_.obc_network_fault51_d_;
    historical_vehiclefailures2_msg.obc_hardware_fault51_d = historical_vehiclefailures2_parser_.obc_hardware_fault51_d_;
    historical_vehiclefailures2_msg.spare551_d = historical_vehiclefailures2_parser_.spare551_d_;
    historical_vehiclefailures2_msg.spare651_d = historical_vehiclefailures2_parser_.spare651_d_;
    historical_vehiclefailures2_msg.spare751_d = historical_vehiclefailures2_parser_.spare751_d_;
    historical_vehiclefailures2_msg.spare851_d = historical_vehiclefailures2_parser_.spare851_d_;
    historical_vehiclefailures2_msg.dp_hardware_fault51_d = historical_vehiclefailures2_parser_.dp_hardware_fault51_d_;
    historical_vehiclefailures2_msg.dp_network_fault51_d = historical_vehiclefailures2_parser_.dp_network_fault51_d_;
    historical_vehiclefailures2_msg.spare951_d = historical_vehiclefailures2_parser_.spare951_d_;
    historical_vehiclefailures2_msg.spare1051_d = historical_vehiclefailures2_parser_.spare1051_d_;
    historical_vehiclefailures2_msg.spare1151_d = historical_vehiclefailures2_parser_.spare1151_d_;
    historical_vehiclefailures2_msg.spare1251_d = historical_vehiclefailures2_parser_.spare1251_d_;
    historical_vehiclefailures2_msg.spare1351_d = historical_vehiclefailures2_parser_.spare1351_d_;
    historical_vehiclefailures2_msg.spare1451_d = historical_vehiclefailures2_parser_.spare1451_d_;
    historical_vehiclefailures2_msg.bcm_hardware_fault51_d = historical_vehiclefailures2_parser_.bcm_hardware_fault51_d_;
    historical_vehiclefailures2_msg.bcm_network_fault51_d = historical_vehiclefailures2_parser_.bcm_network_fault51_d_;
    historical_vehiclefailures2_msg.spare1551_d = historical_vehiclefailures2_parser_.spare1551_d_;
    historical_vehiclefailures2_msg.spare1651_d = historical_vehiclefailures2_parser_.spare1651_d_;
    historical_vehiclefailures2_msg.spare1751_d = historical_vehiclefailures2_parser_.spare1751_d_;
    historical_vehiclefailures2_msg.spare1851_d = historical_vehiclefailures2_parser_.spare1851_d_;
    historical_vehiclefailures2_msg.spare1951_d = historical_vehiclefailures2_parser_.spare1951_d_;
    historical_vehiclefailures2_msg.spare2051_d = historical_vehiclefailures2_parser_.spare2051_d_;
    historical_vehiclefailures2_msg.dcu_network_fault51_d = historical_vehiclefailures2_parser_.dcu_network_fault51_d_;
    historical_vehiclefailures2_msg.dcu_hardware_fault51_d = historical_vehiclefailures2_parser_.dcu_hardware_fault51_d_;
    historical_vehiclefailures2_msg.spare2151_d = historical_vehiclefailures2_parser_.spare2151_d_;
    historical_vehiclefailures2_msg.avas_network_fault51_d = historical_vehiclefailures2_parser_.avas_network_fault51_d_;
    historical_vehiclefailures2_msg.avas_hardware_fault51_d = historical_vehiclefailures2_parser_.avas_hardware_fault51_d_;
    historical_vehiclefailures2_msg.spare2251_d = historical_vehiclefailures2_parser_.spare2251_d_;
    historical_vehiclefailures2_msg.spare2351_d = historical_vehiclefailures2_parser_.spare2351_d_;
    historical_vehiclefailures2_msg.iis_hardware_fault51_d = historical_vehiclefailures2_parser_.iis_hardware_fault51_d_;
    historical_vehiclefailures2_msg.iis_network_fault51_d = historical_vehiclefailures2_parser_.iis_network_fault51_d_;
    historical_vehiclefailures2_msg.spare2451_d = historical_vehiclefailures2_parser_.spare2451_d_;
    historical_vehiclefailures2_msg.spare2551_d = historical_vehiclefailures2_parser_.spare2551_d_;
    historical_vehiclefailures2_msg.spare2651_d = historical_vehiclefailures2_parser_.spare2651_d_;
    historical_vehiclefailures2_msg.spare2751_d = historical_vehiclefailures2_parser_.spare2751_d_;
    historical_vehiclefailures2_msg.spare2851_d = historical_vehiclefailures2_parser_.spare2851_d_;
    historical_vehiclefailures2_msg.spare2951_d = historical_vehiclefailures2_parser_.spare2951_d_;
    historical_vehiclefailures2_msg.spare3051_d = historical_vehiclefailures2_parser_.spare3051_d_;
    historical_vehiclefailures2_msg.ac_hardware_fault51_d = historical_vehiclefailures2_parser_.ac_hardware_fault51_d_;
    historical_vehiclefailures2_msg.ac_network_fault51_d = historical_vehiclefailures2_parser_.ac_network_fault51_d_;
    historical_vehiclefailures2_msg.spare3151_d = historical_vehiclefailures2_parser_.spare3151_d_;
    historical_vehiclefailures2_msg.spare3251_d = historical_vehiclefailures2_parser_.spare3251_d_;
    historical_vehiclefailures2_msg.spare3351_d = historical_vehiclefailures2_parser_.spare3351_d_;
    historical_vehiclefailures2_msg.spare3451_d = historical_vehiclefailures2_parser_.spare3451_d_;
    historical_vehiclefailures2_msg.spare3551_d = historical_vehiclefailures2_parser_.spare3551_d_;
    historical_vehiclefailures2_msg.spare3651_d = historical_vehiclefailures2_parser_.spare3651_d_;
    historical_vehiclefailures2_msg.lv_battery_low_voltage_fault51_d = historical_vehiclefailures2_parser_.lv_battery_low_voltage_fault51_d_;
    historical_vehiclefailures2_msg.lv_battery_high_voltage_fault51_d = historical_vehiclefailures2_parser_.lv_battery_high_voltage_fault51_d_;
    historical_vehiclefailures2_msg.spare3751_d = historical_vehiclefailures2_parser_.spare3751_d_;
    historical_vehiclefailures2_msg.spare3851_d = historical_vehiclefailures2_parser_.spare3851_d_;
    historical_vehiclefailures2_msg.spare3951_d = historical_vehiclefailures2_parser_.spare3951_d_;
    historical_vehiclefailures2_msg.spare4051_d = historical_vehiclefailures2_parser_.spare4051_d_;
    historical_vehiclefailures2_msg.spare4151_d = historical_vehiclefailures2_parser_.spare4151_d_;
    historical_vehiclefailures2_msg.spare4251_d = historical_vehiclefailures2_parser_.spare4251_d_;
    historical_vehiclefailures2_msg.spare4351_d = historical_vehiclefailures2_parser_.spare4351_d_;
    historical_vehiclefailures2_msg.spare4451_d = historical_vehiclefailures2_parser_.spare4451_d_;
    historical_vehiclefailures2_msg.spare4551_d = historical_vehiclefailures2_parser_.spare4551_d_;
    historical_vehiclefailures2_msg.spare4651_d = historical_vehiclefailures2_parser_.spare4651_d_;
    historical_vehiclefailures2_msg.spare4751_d = historical_vehiclefailures2_parser_.spare4751_d_;
    historical_vehiclefailures2_msg.spare4851_d = historical_vehiclefailures2_parser_.spare4851_d_;
    historical_vehiclefailures2_msg.spare4951_d = historical_vehiclefailures2_parser_.spare4951_d_;
    historical_vehiclefailures2_msg.spare5051_d = historical_vehiclefailures2_parser_.spare5051_d_;
    historical_vehiclefailures2_msg.spare5151_d = historical_vehiclefailures2_parser_.spare5151_d_;
    historical_vehiclefailures2_msg.spare5251_d = historical_vehiclefailures2_parser_.spare5251_d_;

    historical_vehiclefailures2_pub_->publish(historical_vehiclefailures2_msg);
    break;
    
  case VaDriveStaFb::ID:
    for(uint i=0;i<8;i++)
    {
      byte_temp[i] = msg->data[i];
    }
    va_drive_sta_fb_parser_.update_bytes(byte_temp);
    va_drive_sta_fb_parser_.Parse();

    va_drive_sta_fb_msg.header = header;
    va_drive_sta_fb_msg.vcu_chassis_driver_en_sta = va_drive_sta_fb_parser_.vcu_chassis_driver_en_sta_;
    va_drive_sta_fb_msg.vcu_chassis_diver_slopover = va_drive_sta_fb_parser_.vcu_chassis_diver_slopover_;
    va_drive_sta_fb_msg.vcu_chassis_driver_mode_sta = va_drive_sta_fb_parser_.vcu_chassis_driver_mode_sta_;
    va_drive_sta_fb_msg.vcu_chassis_gear_fb = va_drive_sta_fb_parser_.vcu_chassis_gear_fb_;
    va_drive_sta_fb_msg.vcu_chassis4_wd_mode_fb = va_drive_sta_fb_parser_.vcu_chassis4_wd_mode_fb_;
    va_drive_sta_fb_msg.vcu_chassis_speed_fb = va_drive_sta_fb_parser_.vcu_chassis_speed_fb_;
    va_drive_sta_fb_msg.vcu_chassis_throttle_pald_fb = va_drive_sta_fb_parser_.vcu_chassis_throttle_pald_fb_;
    va_drive_sta_fb_msg.vcu_chassis_throttle_pedal_req_fb = va_drive_sta_fb_parser_.vcu_chassis_throttle_pedal_req_fb_;
    va_drive_sta_fb_msg.vcu_chassis_acceleration_fb = va_drive_sta_fb_parser_.vcu_chassis_acceleration_fb_;
    va_drive_sta_fb_msg.vcu_drive_life = va_drive_sta_fb_parser_.vcu_drive_life_;
    va_drive_sta_fb_msg.vcu_drive_check_sta = va_drive_sta_fb_parser_.vcu_drive_check_sta_;

    va_drive_sta_fb_pub_->publish(va_drive_sta_fb_msg);
    break;
    
  case VaBrakeStaFb::ID:
    for(uint i=0;i<8;i++)
    {
      byte_temp[i] = msg->data[i];
    }
    va_brake_sta_fb_parser_.update_bytes(byte_temp);
    va_brake_sta_fb_parser_.Parse();

    va_brake_sta_fb_msg.header = header;
    va_brake_sta_fb_msg.vcu_chassis_brake_en_sta = va_brake_sta_fb_parser_.vcu_chassis_brake_en_sta_;
    va_brake_sta_fb_msg.vcu_vehicle_brake_lamp_fb = va_brake_sta_fb_parser_.vcu_vehicle_brake_lamp_fb_;
    va_brake_sta_fb_msg.vcu_chassis_epb_fb = va_brake_sta_fb_parser_.vcu_chassis_epb_fb_;
    va_brake_sta_fb_msg.vcu_chassis_brake_communication_lost = va_brake_sta_fb_parser_.vcu_chassis_brake_communication_lost_;
    va_brake_sta_fb_msg.vcu_chassis_brake_padl_fb = va_brake_sta_fb_parser_.vcu_chassis_brake_padl_fb_;
    va_brake_sta_fb_msg.vcu_brake_pedal_req_fb = va_brake_sta_fb_parser_.vcu_brake_pedal_req_fb_;
    va_brake_sta_fb_msg.vcu_aeb_en_sta_fb = va_brake_sta_fb_parser_.vcu_aeb_en_sta_fb_;
    va_brake_sta_fb_msg.vcu_aeb_trigger_sta_fb = va_brake_sta_fb_parser_.vcu_aeb_trigger_sta_fb_;
    va_brake_sta_fb_msg.vcu_chassis_brake_pressure_fb = va_brake_sta_fb_parser_.vcu_chassis_brake_pressure_fb_;
    va_brake_sta_fb_msg.vcu_brake_life = va_brake_sta_fb_parser_.vcu_brake_life_;
    va_brake_sta_fb_msg.vcu_brake_check_sta = va_brake_sta_fb_parser_.vcu_brake_check_sta_;
    va_brake_sta_fb_msg.vcu_energy_recovery_sta_fb = va_brake_sta_fb_parser_.vcu_energy_recovery_sta_fb_;
    va_brake_sta_fb_msg.vcu_energy_recovery_tor_fb = va_brake_sta_fb_parser_.vcu_energy_recovery_tor_fb_;

    va_brake_sta_fb_pub_->publish(va_brake_sta_fb_msg);
    break;
    
  case VaSteerStaFb::ID:
    for(uint i=0;i<8;i++)
    {
      byte_temp[i] = msg->data[i];
    }
    va_steer_sta_fb_parser_.update_bytes(byte_temp);
    va_steer_sta_fb_parser_.Parse();

    va_steer_sta_fb_msg.header = header;
    va_steer_sta_fb_msg.vcu_chassis_steer_en_sta = va_steer_sta_fb_parser_.vcu_chassis_steer_en_sta_;
    va_steer_sta_fb_msg.vcu_chassis_steer_slopover = va_steer_sta_fb_parser_.vcu_chassis_steer_slopover_;
    va_steer_sta_fb_msg.vcu_chassis_steer_work_mode = va_steer_sta_fb_parser_.vcu_chassis_steer_work_mode_;
    va_steer_sta_fb_msg.vcu_chassis_steer_mode_fb = va_steer_sta_fb_parser_.vcu_chassis_steer_mode_fb_;
    va_steer_sta_fb_msg.vcu_chassis_steer_communication_lost = va_steer_sta_fb_parser_.vcu_chassis_steer_communication_lost_;
    va_steer_sta_fb_msg.vcu_chassis_steer_angle_fb = va_steer_sta_fb_parser_.vcu_chassis_steer_angle_fb_;
    va_steer_sta_fb_msg.vcu_chassis_steer_angle_rear_fb = va_steer_sta_fb_parser_.vcu_chassis_steer_angle_rear_fb_;
    va_steer_sta_fb_msg.vcu_chassis_steer_angle_speed_fb = va_steer_sta_fb_parser_.vcu_chassis_steer_angle_speed_fb_;
    va_steer_sta_fb_msg.vcu_steer_life = va_steer_sta_fb_parser_.vcu_steer_life_;
    va_steer_sta_fb_msg.vcu_steer_check_sta = va_steer_sta_fb_parser_.vcu_steer_check_sta_;

    va_steer_sta_fb_pub_->publish(va_steer_sta_fb_msg);
    break;
    
  case VaVehicleWorkStaFb::ID:
    for(uint i=0;i<8;i++)
    {
      byte_temp[i] = msg->data[i];
    }
    va_vehicle_work_sta_fb_parser_.update_bytes(byte_temp);
    va_vehicle_work_sta_fb_parser_.Parse();

    va_vehicle_work_sta_fb_msg.header = header;
    va_vehicle_work_sta_fb_msg.vcu_driving_mode_fb = va_vehicle_work_sta_fb_parser_.vcu_driving_mode_fb_;
    va_vehicle_work_sta_fb_msg.vcu_chassis_power_sta_fb = va_vehicle_work_sta_fb_parser_.vcu_chassis_power_sta_fb_;
    va_vehicle_work_sta_fb_msg.vcu_chassis_power_dc_sta = va_vehicle_work_sta_fb_parser_.vcu_chassis_power_dc_sta_;
    va_vehicle_work_sta_fb_msg.vcu_chassis_speed_limited_mode_fb = va_vehicle_work_sta_fb_parser_.vcu_chassis_speed_limited_mode_fb_;
    va_vehicle_work_sta_fb_msg.vcu_chassis_power_limite_sta = va_vehicle_work_sta_fb_parser_.vcu_chassis_power_limite_sta_;
    va_vehicle_work_sta_fb_msg.vcu_sys_eco_mode = va_vehicle_work_sta_fb_parser_.vcu_sys_eco_mode_;
    va_vehicle_work_sta_fb_msg.vcu_chassis_speed_limited_val_fb = va_vehicle_work_sta_fb_parser_.vcu_chassis_speed_limited_val_fb_;
    va_vehicle_work_sta_fb_msg.vcu_chassis_low_power_volt_sta = va_vehicle_work_sta_fb_parser_.vcu_chassis_low_power_volt_sta_;
    va_vehicle_work_sta_fb_msg.vcu_chassis_e_stop_sta_fb = va_vehicle_work_sta_fb_parser_.vcu_chassis_e_stop_sta_fb_;
    va_vehicle_work_sta_fb_msg.vcu_crash_front_sta = va_vehicle_work_sta_fb_parser_.vcu_crash_front_sta_;
    va_vehicle_work_sta_fb_msg.vcu_crash_rear_sta = va_vehicle_work_sta_fb_parser_.vcu_crash_rear_sta_;
    va_vehicle_work_sta_fb_msg.vcu_crash_left_sta = va_vehicle_work_sta_fb_parser_.vcu_crash_left_sta_;
    va_vehicle_work_sta_fb_msg.vcu_crash_right_sta = va_vehicle_work_sta_fb_parser_.vcu_crash_right_sta_;
    va_vehicle_work_sta_fb_msg.vcu_life = va_vehicle_work_sta_fb_parser_.vcu_life_;
    va_vehicle_work_sta_fb_msg.vcu_check_sum = va_vehicle_work_sta_fb_parser_.vcu_check_sum_;

    va_vehicle_work_sta_fb_pub_->publish(va_vehicle_work_sta_fb_msg);
    break;
    
  case VaPowerStaFb::ID:
    for(uint i=0;i<8;i++)
    {
      byte_temp[i] = msg->data[i];
    }
    va_power_sta_fb_parser_.update_bytes(byte_temp);
    va_power_sta_fb_parser_.Parse();

    va_power_sta_fb_msg.header = header;
    va_power_sta_fb_msg.vcu_chassis_bms_reserved1 = va_power_sta_fb_parser_.vcu_chassis_bms_reserved1_;
    va_power_sta_fb_msg.vcu_chassis_power_charge_sta = va_power_sta_fb_parser_.vcu_chassis_power_charge_sta_;
    va_power_sta_fb_msg.vcu_chassis_power_charge_sock_sta = va_power_sta_fb_parser_.vcu_chassis_power_charge_sock_sta_;
    va_power_sta_fb_msg.vcu_chassis_power_soc_fb = va_power_sta_fb_parser_.vcu_chassis_power_soc_fb_;
    va_power_sta_fb_msg.vcu_chassis_power_volt_fb = va_power_sta_fb_parser_.vcu_chassis_power_volt_fb_;
    va_power_sta_fb_msg.vcu_chassis_power_curr_fb = va_power_sta_fb_parser_.vcu_chassis_power_curr_fb_;
    va_power_sta_fb_msg.vcu_chassis_bms_max_temp = va_power_sta_fb_parser_.vcu_chassis_bms_max_temp_;
    va_power_sta_fb_msg.vcu_chassis_bms_reserved2 = va_power_sta_fb_parser_.vcu_chassis_bms_reserved2_;

    va_power_sta_fb_pub_->publish(va_power_sta_fb_msg);
    break;
    
  case VaVehicleStaFb::ID:
    for(uint i=0;i<8;i++)
    {
      byte_temp[i] = msg->data[i];
    }
    va_vehicle_sta_fb_parser_.update_bytes(byte_temp);
    va_vehicle_sta_fb_parser_.Parse();

    va_vehicle_sta_fb_msg.header = header;
    va_vehicle_sta_fb_msg.vcu_vehicle_pos_lamp_fb = va_vehicle_sta_fb_parser_.vcu_vehicle_pos_lamp_fb_;
    va_vehicle_sta_fb_msg.vcu_vehicle_head_lamp_fb = va_vehicle_sta_fb_parser_.vcu_vehicle_head_lamp_fb_;
    va_vehicle_sta_fb_msg.vcu_vehicle_left_lamp_fb = va_vehicle_sta_fb_parser_.vcu_vehicle_left_lamp_fb_;
    va_vehicle_sta_fb_msg.vcu_vehicle_right_lamp_fb = va_vehicle_sta_fb_parser_.vcu_vehicle_right_lamp_fb_;
    va_vehicle_sta_fb_msg.vcu_vehicle_high_beam_fb = va_vehicle_sta_fb_parser_.vcu_vehicle_high_beam_fb_;
    va_vehicle_sta_fb_msg.vcu_vehicle_fog_lamp_fb = va_vehicle_sta_fb_parser_.vcu_vehicle_fog_lamp_fb_;
    va_vehicle_sta_fb_msg.vcu_vehicle_hazard_war_lamp_fb = va_vehicle_sta_fb_parser_.vcu_vehicle_hazard_war_lamp_fb_;
    va_vehicle_sta_fb_msg.vcu_vehicle_body_lamp_fb = va_vehicle_sta_fb_parser_.vcu_vehicle_body_lamp_fb_;
    va_vehicle_sta_fb_msg.vcu_vehicle_read_lamp_fb = va_vehicle_sta_fb_parser_.vcu_vehicle_read_lamp_fb_;
    va_vehicle_sta_fb_msg.vcu_vehicle_horn_st_fb = va_vehicle_sta_fb_parser_.vcu_vehicle_horn_st_fb_;
    va_vehicle_sta_fb_msg.acu_vehicle_window_fb = va_vehicle_sta_fb_parser_.acu_vehicle_window_fb_;
    va_vehicle_sta_fb_msg.acu_vehicle_door_req_sig_fb = va_vehicle_sta_fb_parser_.acu_vehicle_door_req_sig_fb_;
    va_vehicle_sta_fb_msg.vcu_vehicle_door_sta_fb = va_vehicle_sta_fb_parser_.vcu_vehicle_door_sta_fb_;
    va_vehicle_sta_fb_msg.vcu_vehicle_wipers_sta_fb = va_vehicle_sta_fb_parser_.vcu_vehicle_wipers_sta_fb_;
    va_vehicle_sta_fb_msg.vcu_vehicle_safety_belt1 = va_vehicle_sta_fb_parser_.vcu_vehicle_safety_belt1_;
    va_vehicle_sta_fb_msg.vcu_vehicle_safety_belt2 = va_vehicle_sta_fb_parser_.vcu_vehicle_safety_belt2_;
    va_vehicle_sta_fb_msg.vcu_vehicle_safety_belt3 = va_vehicle_sta_fb_parser_.vcu_vehicle_safety_belt3_;
    va_vehicle_sta_fb_msg.vcu_vehicle_safety_belt4 = va_vehicle_sta_fb_parser_.vcu_vehicle_safety_belt4_;
    va_vehicle_sta_fb_msg.vcu_vehicle_safety_belt5 = va_vehicle_sta_fb_parser_.vcu_vehicle_safety_belt5_;
    va_vehicle_sta_fb_msg.vcu_vehicle_safety_belt6 = va_vehicle_sta_fb_parser_.vcu_vehicle_safety_belt6_;
    va_vehicle_sta_fb_msg.vcu_vehicle_reserve_warning = va_vehicle_sta_fb_parser_.vcu_vehicle_reserve_warning_;
    va_vehicle_sta_fb_msg.vcu_vehicle_display_speed = va_vehicle_sta_fb_parser_.vcu_vehicle_display_speed_;

    va_vehicle_sta_fb_pub_->publish(va_vehicle_sta_fb_msg);
    break;
    
  case VaVehicleFltSta::ID:
    for(uint i=0;i<8;i++)
    {
      byte_temp[i] = msg->data[i];
    }
    va_vehicle_flt_sta_parser_.update_bytes(byte_temp);
    va_vehicle_flt_sta_parser_.Parse();

    va_vehicle_flt_sta_msg.header = header;
    va_vehicle_flt_sta_msg.vcu_sys_motor_over_temp_sta = va_vehicle_flt_sta_parser_.vcu_sys_motor_over_temp_sta_;
    va_vehicle_flt_sta_msg.vcu_sys_bms_over_temp_sta = va_vehicle_flt_sta_parser_.vcu_sys_bms_over_temp_sta_;
    va_vehicle_flt_sta_msg.vcu_sys_brake_over_temp_sta = va_vehicle_flt_sta_parser_.vcu_sys_brake_over_temp_sta_;
    va_vehicle_flt_sta_msg.vcu_sys_steer_over_temp_sta = va_vehicle_flt_sta_parser_.vcu_sys_steer_over_temp_sta_;
    va_vehicle_flt_sta_msg.vcu_sys_under_volt = va_vehicle_flt_sta_parser_.vcu_sys_under_volt_;
    va_vehicle_flt_sta_msg.vcu_sys_flt = va_vehicle_flt_sta_parser_.vcu_sys_flt_;
    va_vehicle_flt_sta_msg.vcu_sys_brake_flt = va_vehicle_flt_sta_parser_.vcu_sys_brake_flt_;
    va_vehicle_flt_sta_msg.vcu_sys_parking_flt = va_vehicle_flt_sta_parser_.vcu_sys_parking_flt_;
    va_vehicle_flt_sta_msg.vcu_sys_steer_front_flt = va_vehicle_flt_sta_parser_.vcu_sys_steer_front_flt_;
    va_vehicle_flt_sta_msg.vcu_sys_steer_back_flt = va_vehicle_flt_sta_parser_.vcu_sys_steer_back_flt_;
    va_vehicle_flt_sta_msg.vcu_sys_motor_lf_flt = va_vehicle_flt_sta_parser_.vcu_sys_motor_lf_flt_;
    va_vehicle_flt_sta_msg.vcu_sys_motor_rf_flt = va_vehicle_flt_sta_parser_.vcu_sys_motor_rf_flt_;
    va_vehicle_flt_sta_msg.vcu_sys_motor_lr_flt = va_vehicle_flt_sta_parser_.vcu_sys_motor_lr_flt_;
    va_vehicle_flt_sta_msg.vcu_sys_motor_rr_flt = va_vehicle_flt_sta_parser_.vcu_sys_motor_rr_flt_;
    va_vehicle_flt_sta_msg.vcu_sys_bms_flt = va_vehicle_flt_sta_parser_.vcu_sys_bms_flt_;
    va_vehicle_flt_sta_msg.vcu_sys_dc_flt = va_vehicle_flt_sta_parser_.vcu_sys_dc_flt_;
    va_vehicle_flt_sta_msg.vcu_sys_door_flt = va_vehicle_flt_sta_parser_.vcu_sys_door_flt_;
    va_vehicle_flt_sta_msg.vcu_sys_dpm_flt = va_vehicle_flt_sta_parser_.vcu_sys_dpm_flt_;
    va_vehicle_flt_sta_msg.vcu_sys_bcm_flt = va_vehicle_flt_sta_parser_.vcu_sys_bcm_flt_;
    va_vehicle_flt_sta_msg.vcu_vehicle_flt_level = va_vehicle_flt_sta_parser_.vcu_vehicle_flt_level_;
    va_vehicle_flt_sta_msg.vcu_sys_flt_reserve1 = va_vehicle_flt_sta_parser_.vcu_sys_flt_reserve1_;

    va_vehicle_flt_sta_pub_->publish(va_vehicle_flt_sta_msg);
    break;
    
  case VaChassisWheelRpmFb::ID:
    for(uint i=0;i<8;i++)
    {
      byte_temp[i] = msg->data[i];
    }
    va_chassis_wheel_rpm_fb_parser_.update_bytes(byte_temp);
    va_chassis_wheel_rpm_fb_parser_.Parse();

    va_chassis_wheel_rpm_fb_msg.header = header;
    va_chassis_wheel_rpm_fb_msg.vcu_chassis_wheel_rpm_lf = va_chassis_wheel_rpm_fb_parser_.vcu_chassis_wheel_rpm_lf_;
    va_chassis_wheel_rpm_fb_msg.vcu_chassis_wheel_rpm_rf = va_chassis_wheel_rpm_fb_parser_.vcu_chassis_wheel_rpm_rf_;
    va_chassis_wheel_rpm_fb_msg.vcu_chassis_wheel_rpm_lr = va_chassis_wheel_rpm_fb_parser_.vcu_chassis_wheel_rpm_lr_;
    va_chassis_wheel_rpm_fb_msg.vcu_chassis_wheel_rpm_rr = va_chassis_wheel_rpm_fb_parser_.vcu_chassis_wheel_rpm_rr_;

    va_chassis_wheel_rpm_fb_pub_->publish(va_chassis_wheel_rpm_fb_msg);
    break;
    
  case VaChassisOdoFb::ID:
    for(uint i=0;i<8;i++)
    {
      byte_temp[i] = msg->data[i];
    }
    va_chassis_odo_fb_parser_.update_bytes(byte_temp);
    va_chassis_odo_fb_parser_.Parse();

    va_chassis_odo_fb_msg.header = header;
    va_chassis_odo_fb_msg.vcu_vehicle_odo = va_chassis_odo_fb_parser_.vcu_vehicle_odo_;
    va_chassis_odo_fb_msg.vcu_vehicle_trip = va_chassis_odo_fb_parser_.vcu_vehicle_trip_;
    va_chassis_odo_fb_msg.vcu_vehicle_remaining_range = va_chassis_odo_fb_parser_.vcu_vehicle_remaining_range_;

    va_chassis_odo_fb_pub_->publish(va_chassis_odo_fb_msg);
    break;
    
  case VcuTransfer::ID:
    for(uint i=0;i<8;i++)
    {
      byte_temp[i] = msg->data[i];
    }
    vcu_transfer_parser_.update_bytes(byte_temp);
    vcu_transfer_parser_.Parse();

    vcu_transfer_msg.header = header;
    vcu_transfer_msg.vcu_pad_auto_start = vcu_transfer_parser_.vcu_pad_auto_start_;
    vcu_transfer_msg.ac_out_temp = vcu_transfer_parser_.ac_out_temp_;
    vcu_transfer_msg.ac_in_temp = vcu_transfer_parser_.ac_in_temp_;

    vcu_transfer_pub_->publish(vcu_transfer_msg);
    break;
    
  case VaChassisWheelTirePressFb::ID:
    for(uint i=0;i<8;i++)
    {
      byte_temp[i] = msg->data[i];
    }
    va_chassis_wheel_tire_press_fb_parser_.update_bytes(byte_temp);
    va_chassis_wheel_tire_press_fb_parser_.Parse();

    va_chassis_wheel_tire_press_fb_msg.header = header;
    va_chassis_wheel_tire_press_fb_msg.vcu_chassis_wheel_tire_press_lf = va_chassis_wheel_tire_press_fb_parser_.vcu_chassis_wheel_tire_press_lf_;
    va_chassis_wheel_tire_press_fb_msg.vcu_chassis_wheel_tire_press_rf = va_chassis_wheel_tire_press_fb_parser_.vcu_chassis_wheel_tire_press_rf_;
    va_chassis_wheel_tire_press_fb_msg.vcu_chassis_wheel_tire_press_lr = va_chassis_wheel_tire_press_fb_parser_.vcu_chassis_wheel_tire_press_lr_;
    va_chassis_wheel_tire_press_fb_msg.vcu_chassis_wheel_tire_press_rr = va_chassis_wheel_tire_press_fb_parser_.vcu_chassis_wheel_tire_press_rr_;

    va_chassis_wheel_tire_press_fb_pub_->publish(va_chassis_wheel_tire_press_fb_msg);
    break;
    
  case VaChassisWheelAngleFb::ID:
    for(uint i=0;i<8;i++)
    {
      byte_temp[i] = msg->data[i];
    }
    va_chassis_wheel_angle_fb_parser_.update_bytes(byte_temp);
    va_chassis_wheel_angle_fb_parser_.Parse();

    va_chassis_wheel_angle_fb_msg.header = header;
    va_chassis_wheel_angle_fb_msg.vcu_chassis_wheel_angle_lf = va_chassis_wheel_angle_fb_parser_.vcu_chassis_wheel_angle_lf_;
    va_chassis_wheel_angle_fb_msg.vcu_chassis_wheel_angle_rf = va_chassis_wheel_angle_fb_parser_.vcu_chassis_wheel_angle_rf_;
    va_chassis_wheel_angle_fb_msg.vcu_chassis_wheel_angle_lr = va_chassis_wheel_angle_fb_parser_.vcu_chassis_wheel_angle_lr_;
    va_chassis_wheel_angle_fb_msg.vcu_chassis_wheel_angle_rr = va_chassis_wheel_angle_fb_parser_.vcu_chassis_wheel_angle_rr_;

    va_chassis_wheel_angle_fb_pub_->publish(va_chassis_wheel_angle_fb_msg);
    break;
    
  case VaChassisWheelTorqueFb::ID:
    for(uint i=0;i<8;i++)
    {
      byte_temp[i] = msg->data[i];
    }
    va_chassis_wheel_torque_fb_parser_.update_bytes(byte_temp);
    va_chassis_wheel_torque_fb_parser_.Parse();

    va_chassis_wheel_torque_fb_msg.header = header;
    va_chassis_wheel_torque_fb_msg.vcu_chassis_torque_lf = va_chassis_wheel_torque_fb_parser_.vcu_chassis_torque_lf_;
    va_chassis_wheel_torque_fb_msg.vcu_chassis_torque_rf = va_chassis_wheel_torque_fb_parser_.vcu_chassis_torque_rf_;
    va_chassis_wheel_torque_fb_msg.vcu_chassis_torque_lr = va_chassis_wheel_torque_fb_parser_.vcu_chassis_torque_lr_;
    va_chassis_wheel_torque_fb_msg.vcu_chassis_torque_rr = va_chassis_wheel_torque_fb_parser_.vcu_chassis_torque_rr_;

    va_chassis_wheel_torque_fb_pub_->publish(va_chassis_wheel_torque_fb_msg);
    break;
    
  case BcmMessage4::ID:
    for(uint i=0;i<8;i++)
    {
      byte_temp[i] = msg->data[i];
    }
    bcm_message4_parser_.update_bytes(byte_temp);
    bcm_message4_parser_.Parse();

    bcm_message4_msg.header = header;
    bcm_message4_msg.ltemp = bcm_message4_parser_.ltemp_;
    bcm_message4_msg.ntemp = bcm_message4_parser_.ntemp_;
    bcm_message4_msg.safe_belt_sta1 = bcm_message4_parser_.safe_belt_sta1_;
    bcm_message4_msg.safe_belt_sta2 = bcm_message4_parser_.safe_belt_sta2_;
    bcm_message4_msg.safe_belt_sta3 = bcm_message4_parser_.safe_belt_sta3_;
    bcm_message4_msg.safe_belt_sta4 = bcm_message4_parser_.safe_belt_sta4_;
    bcm_message4_msg.safe_belt_sta5 = bcm_message4_parser_.safe_belt_sta5_;
    bcm_message4_msg.safe_belt_sta6 = bcm_message4_parser_.safe_belt_sta6_;
    bcm_message4_msg.seat_sta1 = bcm_message4_parser_.seat_sta1_;
    bcm_message4_msg.seat_sta2 = bcm_message4_parser_.seat_sta2_;
    bcm_message4_msg.seat_sta3 = bcm_message4_parser_.seat_sta3_;
    bcm_message4_msg.seat_sta4 = bcm_message4_parser_.seat_sta4_;
    bcm_message4_msg.seat_sta5 = bcm_message4_parser_.seat_sta5_;
    bcm_message4_msg.seat_sta6 = bcm_message4_parser_.seat_sta6_;

    bcm_message4_pub_->publish(bcm_message4_msg);
    break;
    
  case BcmMessage5::ID:
    for(uint i=0;i<8;i++)
    {
      byte_temp[i] = msg->data[i];
    }
    bcm_message5_parser_.update_bytes(byte_temp);
    bcm_message5_parser_.Parse();

    bcm_message5_msg.header = header;
    bcm_message5_msg.ad_volt_vin1 = bcm_message5_parser_.ad_volt_vin1_;
    bcm_message5_msg.ad_volt_vin2 = bcm_message5_parser_.ad_volt_vin2_;

    bcm_message5_pub_->publish(bcm_message5_msg);
    break;
    
  case DpMessgae4::ID:
    for(uint i=0;i<8;i++)
    {
      byte_temp[i] = msg->data[i];
    }
    dp_messgae4_parser_.update_bytes(byte_temp);
    dp_messgae4_parser_.Parse();

    dp_messgae4_msg.header = header;
    dp_messgae4_msg.pdu_total_cur = dp_messgae4_parser_.pdu_total_cur_;
    dp_messgae4_msg.dp_low_bat_vol = dp_messgae4_parser_.dp_low_bat_vol_;
    dp_messgae4_msg.pdu_temp = dp_messgae4_parser_.pdu_temp_;
    dp_messgae4_msg.auto_current1 = dp_messgae4_parser_.auto_current1_;
    dp_messgae4_msg.dp_error_code = dp_messgae4_parser_.dp_error_code_;
    dp_messgae4_msg.on_sta = dp_messgae4_parser_.on_sta_;
    dp_messgae4_msg.auto_current2 = dp_messgae4_parser_.auto_current2_;

    dp_messgae4_pub_->publish(dp_messgae4_msg);
    break;
    
  case DpMessgae5::ID:
    for(uint i=0;i<8;i++)
    {
      byte_temp[i] = msg->data[i];
    }
    dp_messgae5_parser_.update_bytes(byte_temp);
    dp_messgae5_parser_.Parse();

    dp_messgae5_msg.header = header;
    dp_messgae5_msg.pwm_red_sta = dp_messgae5_parser_.pwm_red_sta_;
    dp_messgae5_msg.pwm_green_sta = dp_messgae5_parser_.pwm_green_sta_;
    dp_messgae5_msg.pwm_blue_sta = dp_messgae5_parser_.pwm_blue_sta_;
    dp_messgae5_msg.atmospherelightbrightness = dp_messgae5_parser_.atmospherelightbrightness_;

    dp_messgae5_pub_->publish(dp_messgae5_msg);
    break;
    
  default:
    break;
  }
}

} // namespace report_parser
} // namespace pix_robobus_driver
#include "rclcpp_components/register_node_macro.hpp"
RCLCPP_COMPONENTS_REGISTER_NODE(pix_robobus_driver::report_parser::ReportParser)