// 底盘 / Pix Robobus driver 相关回调全部集中在此文件，便于维护。

#include "pixmoving_chassis_interface/pixmoving_chassis_interface.hpp"

namespace pixmoving
{
namespace chassis
{
namespace interface
{

void PixmovingChassisInterfaceNode::onBcmMessage4(const pix_robobus_driver_msgs::msg::BcmMessage4::SharedPtr msg)
{
  // 处理BCM消息4的代码
  bool seatbelt_status_all_fastened = true;
  std::vector<int8_t> seat_number(6, 1);

  // 获取安全带状态和座椅状态
  bool safe_belt_sta[6] = { msg->safe_belt_sta1, msg->safe_belt_sta2, msg->safe_belt_sta3,
                            msg->safe_belt_sta4, msg->safe_belt_sta5, msg->safe_belt_sta6 };

  bool seat_sta[6] = { msg->seat_sta1, msg->seat_sta2, msg->seat_sta3, msg->seat_sta4, msg->seat_sta5, msg->seat_sta6 };

  vehicle_info_msg_.seat_sta.resize(6);
  vehicle_info_msg_.belt_sta.resize(6);
  for (int i = 0; i < 6; i++)
  {
    // 安全带状态 0插上
    safe_belt_sta[i] ? vehicle_info_msg_.seat_sta[i] = 0 : vehicle_info_msg_.seat_sta[i] = 1;

    // 座位压力状态 0空的
    seat_sta[i] ? vehicle_info_msg_.belt_sta[i] = 1 : vehicle_info_msg_.belt_sta[i] = 0;
  }

  // 检查安全带状态
  for (int i = 0; i < 6; ++i)
  {
    if (seat_sta[i] && safe_belt_sta[i])
    {
      seatbelt_status_all_fastened = false;
      seat_number[i] = 0;
      break;
    }
  }

  // 更新车辆信息消息
  v2d_vehicle_info_msg_.seatbelt_status_all_fastened = seatbelt_status_all_fastened;
  vehicle_info_msg_.seatbelt = !seatbelt_status_all_fastened;
  vehicle_info_msg_.seat_number = seat_number;
}

void PixmovingChassisInterfaceNode::onBcmMessage5(const pix_robobus_driver_msgs::msg::BcmMessage5::SharedPtr msg)
{
  // 烟雾传感器
  v2d_vehicle_info_msg_.smoke_concentration_voltage = std::round(msg->ad_volt_vin1);
  vehicle_info_msg_.co2 = std::round(msg->ad_volt_vin1);
  // co2传感器
  v2d_vehicle_info_msg_.co2_concentration_voltage = std::round(msg->ad_volt_vin2);
  vehicle_info_msg_.smoke = std::round(msg->ad_volt_vin2);
}

void PixmovingChassisInterfaceNode::onVaDriveStaFb(const pix_robobus_driver_msgs::msg::VaDriveStaFb::SharedPtr msg)
{
  markVehicleInfoLiveSource(kVehicleInfoSourceDrive);
  last_chassis_speed_mps_ = msg->vcu_chassis_speed_fb;
  last_chassis_speed_time_ = this->now();
  vehicle_info_msg_.thr = msg->vcu_chassis_throttle_pald_fb;
  vehicle_info_msg_.spd = msg->vcu_chassis_speed_fb / 0.2777;

  // 底盘 0:not used 1:D 2:N 3:R
  switch (msg->vcu_chassis_gear_fb)
  {
    case 1:  // D档
      v2d_vehicle_info_msg_.gear_status = 4;
      vehicle_info_msg_.gear = 4;
      break;
    case 2:  // N档
      v2d_vehicle_info_msg_.gear_status = 3;
      vehicle_info_msg_.gear = 3;
      break;
    case 3:  // R档
      v2d_vehicle_info_msg_.gear_status = 2;
      vehicle_info_msg_.gear = 2;
      break;
    default:  // 未知
      v2d_vehicle_info_msg_.gear_status = -1;
      vehicle_info_msg_.gear = -1;
      break;
  }

  if (is_park_)
  {
    v2d_vehicle_info_msg_.gear_status = 0;
    vehicle_info_msg_.gear = 0;
  }
}

void PixmovingChassisInterfaceNode::onVaBrakeStaFb(const pix_robobus_driver_msgs::msg::VaBrakeStaFb::SharedPtr msg)
{
  markVehicleInfoLiveSource(kVehicleInfoSourceBrake);
  if (msg->vcu_chassis_epb_fb == 1 || msg->vcu_chassis_epb_fb == 3)
  {
    // 驻车
    is_park_ = true;
  }
  else
  {
    // 没有驻车
    is_park_ = false;
  }
  vehicle_info_msg_.brk = msg->vcu_chassis_brake_padl_fb;
  // 保存刹车踏板请求状态，由 onAutowareState 统一处理驾驶模式
  vcu_brake_pedal_req_fb_ = (msg->vcu_brake_pedal_req_fb == 1);
}

void PixmovingChassisInterfaceNode::onVaSteerStaFb(const pix_robobus_driver_msgs::msg::VaSteerStaFb::SharedPtr msg)
{
  vehicle_info_msg_.ste = msg->vcu_chassis_steer_angle_fb;
  switch (msg->vcu_chassis_steer_mode_fb)
  {
    // 1:前后异向模式, 2:常规模式, 3:前后同向模式;
    case 1:  // 四轮同向
      vehicle_info_msg_.head_mode = 3;
      break;
    case 2:  // 四轮异向
      vehicle_info_msg_.head_mode = 1;
      break;
    case 3:                             // 后轮转向
      vehicle_info_msg_.head_mode = 2;  // 默认为常规2，云平台协议没有0值
      break;
    case 4:                             // 前后轮独立
      vehicle_info_msg_.head_mode = 2;  // 默认为常规2，云平台协议没有0值
      break;
    default:                            // 前轮转向
      vehicle_info_msg_.head_mode = 2;
      break;
  }
}

void PixmovingChassisInterfaceNode::onVaVehicleWorkStaFb(const pix_robobus_driver_msgs::msg::VaVehicleWorkStaFb::SharedPtr msg)
{
  markVehicleInfoLiveSource(kVehicleInfoSourceWork);
  v2d_vehicle_info_msg_.vehicle_operational_status = true;

  switch (msg->vcu_chassis_power_sta_fb)
  {
    case 1:  // no acc
      vehicle_info_msg_.acc = -1;
      break;
    case 2:  // 准备好的
      vehicle_info_msg_.acc = 1;
      break;
    case 3:  // acc off
      vehicle_info_msg_.acc = 0;
      break;
    default:
      vehicle_info_msg_.acc = -1;
      break;
  }

  switch (msg->vcu_chassis_e_stop_sta_fb)
  {
    // 1:车身急停, 2:遥控急停, 3:遥控断开急停, 4:自驾断开急停, 5:远控急停, 6:自驾急停, 7:碰撞急停
    case 0:  // 无急停
      vehicle_info_msg_.emg_sta = 0;
      break;
    case 1:  // 底盘开关驻车
      vehicle_info_msg_.emg_sta = 1;
      break;
    case 2:  // 遥控开关驻车
      vehicle_info_msg_.emg_sta = 2;
      break;
    case 3:  // 底盘故障驻车
      vehicle_info_msg_.emg_sta = 3;
      break;
    case 4:  // 遥控器loss驻车
      vehicle_info_msg_.emg_sta = 4;
      break;
    case 5:
      vehicle_info_msg_.emg_sta = 6;
      break;
    case 6:  // 崩溃驻车
      vehicle_info_msg_.emg_sta = 7;
      break;
    default:
      break;
  }

  // 小电池电压
  vehicle_info_msg_.bat = msg->vcu_chassis_low_power_volt_sta;

  if (msg->vcu_chassis_e_stop_sta_fb)
  {
    is_estop_ = true;
  }
  else
  {
    is_estop_ = false;
  }
}

void PixmovingChassisInterfaceNode::onVaPowerStaFb(const pix_robobus_driver_msgs::msg::VaPowerStaFb::SharedPtr msg)
{
  markVehicleInfoLiveSource(kVehicleInfoSourcePower);
  // 大电池电量
  v2d_vehicle_info_msg_.battery_percentage_remaining = msg->vcu_chassis_power_soc_fb;
  vehicle_info_msg_.p_l = msg->vcu_chassis_power_soc_fb;

  // 剩余里程数，就是电量
  v2d_vehicle_info_msg_.vehicle_remain_mileage_km = msg->vcu_chassis_power_soc_fb;
  vehicle_info_msg_.rm = msg->vcu_chassis_power_soc_fb;

  // 大电池电压
  vehicle_info_msg_.p_v = msg->vcu_chassis_power_volt_fb;
  // 大电池电流
  vehicle_info_msg_.p_c = msg->vcu_chassis_power_curr_fb;
  // 充电状态
  vehicle_info_msg_.p_ch = msg->vcu_chassis_power_charge_sock_sta;
}

void PixmovingChassisInterfaceNode::onVaVehicleStaFb(const pix_robobus_driver_msgs::msg::VaVehicleStaFb::SharedPtr msg)
{
  markVehicleInfoLiveSource(kVehicleInfoSourceVehicle);
  // vehicle_info_msg_ 0:关, 1:开, -1:未知; 2 开门中, 3 关门中 4 开门故障, 5 关门故障

  switch (msg->vcu_vehicle_door_sta_fb)
  {
    case 1:  // 开门中
      vehicle_info_msg_.door = 2;
      break;
    case 2:  // 关门中
      vehicle_info_msg_.door = 3;
      break;
    case 3:  // 开门完成
      vehicle_info_msg_.door = 1;
      break;
    case 4:  // 关门完成
      vehicle_info_msg_.door = 0;
      break;
    case 5:  // 开门超时
      vehicle_info_msg_.door = 4;
      break;
    case 6:  // 关门超时
      vehicle_info_msg_.door = 5;
      break;
    default:  // 其他
      vehicle_info_msg_.door = -1;
      break;
  }

  if (msg->vcu_vehicle_door_sta_fb == 1 || msg->vcu_vehicle_door_sta_fb == 3)
  {
    // open door
    vehicle_info_msg_.door = 1;
  }
  else if (msg->vcu_vehicle_door_sta_fb == 2 || msg->vcu_vehicle_door_sta_fb == 4)
  {
    // close door
    vehicle_info_msg_.door = 0;
  }
  else
  {
    vehicle_info_msg_.door = -1;
  }

  // 远近光灯状态
  auto getHeadLightState = [](bool highBeam, bool lowBeam) -> int {
    if (highBeam)
      return 1;  // 远光灯开
    if (lowBeam)
      return 2;  // 近光灯开
    return 0;    // 全关
  };

  vehicle_info_msg_.head_light = getHeadLightState(msg->vcu_vehicle_high_beam_fb, msg->vcu_vehicle_head_lamp_fb);

  // 转向灯双闪 0:关, 1:左转灯开, 2:右转灯开, 3:双闪开
  if (msg->vcu_vehicle_left_lamp_fb && msg->vcu_vehicle_right_lamp_fb)
  {
    vehicle_info_msg_.turn_light = 3;
  }
  if (msg->vcu_vehicle_left_lamp_fb && !msg->vcu_vehicle_right_lamp_fb)
  {
    vehicle_info_msg_.turn_light = 1;
  }
  if (!msg->vcu_vehicle_left_lamp_fb && msg->vcu_vehicle_right_lamp_fb)
  {
    vehicle_info_msg_.turn_light = 2;
  }
  if (!msg->vcu_vehicle_left_lamp_fb && !msg->vcu_vehicle_right_lamp_fb)
  {
    vehicle_info_msg_.turn_light = 0;
  }

  // 车外氛围灯状态反馈
  msg->vcu_vehicle_body_lamp_fb ? vehicle_info_msg_.in_lights = 1 : vehicle_info_msg_.in_lights = 0;

  // 车内灯光状态反馈
  msg->vcu_vehicle_read_lamp_fb ? vehicle_info_msg_.out_mood_lights = 1 : vehicle_info_msg_.out_mood_lights = 0;

  // 车窗
  if (msg->acu_vehicle_window_fb == 1 || msg->acu_vehicle_window_fb == 3)
  {
    vehicle_info_msg_.win = 1;
  }
  else if (msg->acu_vehicle_window_fb == 2 || msg->acu_vehicle_window_fb == 4)
  {
    vehicle_info_msg_.win = 0;
  }
  else
  {
    vehicle_info_msg_.win = -1;
  }
}

void PixmovingChassisInterfaceNode::onVaChassisOdoFb(const pix_robobus_driver_msgs::msg::VaChassisOdoFb::SharedPtr msg)
{
  markVehicleInfoLiveSource(kVehicleInfoSourceOdo);
  // 总里程数
  v2d_vehicle_info_msg_.vehicle_total_mileage_km = msg->vcu_vehicle_odo;
  latest_raw_can_trip_m_ = msg->vcu_vehicle_trip * 1000.0;

  const std::int32_t new_tm = static_cast<std::int32_t>(std::round(msg->vcu_vehicle_odo));
  const std::int32_t new_ptm = static_cast<std::int32_t>(std::round(msg->vcu_vehicle_trip * 1000.0));

  auto log_edge = [this](const char* field, std::int32_t old_v, std::int32_t new_v) {
    // 只在跨越 -1（未知）边界时打印一次：
    // - old == -1, new != -1  (未知 -> 有效)
    // - old != -1, new == -1  (有效 -> 未知)
    if (old_v != new_v && ((old_v == -1) != (new_v == -1)))
    {
      RCLCPP_INFO(this->get_logger(), "%s changed %d -> %d", field, old_v, new_v);
    }
  };

  log_edge("VehicleInfo.tm", last_tm_, new_tm);
  last_tm_ = new_tm;
  vehicle_info_msg_.tm = new_tm;

  if (!enable_fused_ptm_)
  {
    log_edge("VehicleInfo.ptm", last_ptm_, new_ptm);
    last_ptm_ = new_ptm;
    vehicle_info_msg_.ptm = new_ptm;
  }
}

void PixmovingChassisInterfaceNode::onVaChassisWheelTirePressFb(const pix_robobus_driver_msgs::msg::VaChassisWheelTirePressFb::SharedPtr msg)
{
  (void)msg;
}

void PixmovingChassisInterfaceNode::onVcuTransfer(const pix_robobus_driver_msgs::msg::VcuTransfer::SharedPtr msg)
{
  // 车内温度
  v2d_vehicle_info_msg_.temperature_inside_celsius = std::round(msg->ac_in_temp);
  // 车外温度
  v2d_vehicle_info_msg_.temperature_outside_celsius = std::round(msg->ac_out_temp);

  vehicle_info_msg_.in_temp = std::round(msg->ac_in_temp);
  vehicle_info_msg_.out_temp = std::round(msg->ac_out_temp);
}

void PixmovingChassisInterfaceNode::onVehicleErrcode1(const pix_robobus_driver_msgs::msg::VehicleErrcode1::SharedPtr msg)
{
  if (msg->rcu_network_fault)
  {
    // 反常
    vehicle_info_msg_.rc = 1;
    v2d_vehicle_info_msg_.controller_connected_status = false;
  }
  else
  {
    // 正常
    vehicle_info_msg_.rc = 0;
    v2d_vehicle_info_msg_.controller_connected_status = true;
  }
}

void PixmovingChassisInterfaceNode::onVcuSoftVer(const pix_robobus_driver_msgs::msg::VcuSoftVer::SharedPtr msg)
{
  vehicle_info_msg_.vcu_version = std::to_string(msg->version_year) + "_" + std::to_string(msg->version_month) + "_" +
                                  std::to_string(msg->version_day) + "-" + std::to_string(msg->version_main) + "." +
                                  std::to_string(msg->version_sub) + "." + std::to_string(msg->version_patch);
}

void PixmovingChassisInterfaceNode::onVinResp1(const pix_robobus_driver_msgs::msg::VinResp1::SharedPtr msg)
{
  std::string vcu_version1 = std::to_string(msg->vin_00) + std::to_string(msg->vin_01) + std::to_string(msg->vin_02) +
                             std::to_string(msg->vin_03) + std::to_string(msg->vin_04) + std::to_string(msg->vin_05) +
                             std::to_string(msg->vin_06) + std::to_string(msg->vin_07);
  vehicle_info_msg_.vin_unmber.resize(vcu_version1.size());
  vehicle_info_msg_.vin_unmber.insert(0, vcu_version1);
}

void PixmovingChassisInterfaceNode::onVinResp2(const pix_robobus_driver_msgs::msg::VinResp2::SharedPtr msg)
{
  std::string vcu_version2 = std::to_string(msg->vin_08) + std::to_string(msg->vin_09) + std::to_string(msg->vin_10) +
                             std::to_string(msg->vin_11) + std::to_string(msg->vin_12) + std::to_string(msg->vin_13) +
                             std::to_string(msg->vin_14) + std::to_string(msg->vin_15);
  vehicle_info_msg_.vin_unmber.resize(vcu_version2.size() + 8);
  vehicle_info_msg_.vin_unmber.insert(8, vcu_version2);
}

void PixmovingChassisInterfaceNode::onVinResp3(const pix_robobus_driver_msgs::msg::VinResp3::SharedPtr msg)
{
  std::string vcu_version3 = std::to_string(msg->vin_16);

  vehicle_info_msg_.vin_unmber.resize(vcu_version3.size() + 16);
  vehicle_info_msg_.vin_unmber.insert(16, vcu_version3);
}

void PixmovingChassisInterfaceNode::onAebInfoReport(const aeb_interfaces::msg::AebInfoReport::SharedPtr msg)
{
  // AebInfoReport.aeb_status: 0=OFF, 1=ON, 2=FAULT
  // VehicleInfo.aeb_status: 0=未触发, 1=触发, -1=未知
  // 映射逻辑：ON(1) 和 FAULT(2) 都视为触发状态(1)，OFF(0) 为未触发(0)
  // if (msg->aeb_status == aeb_interfaces::msg::AebInfoReport::ON ||
  //     msg->aeb_status == aeb_interfaces::msg::AebInfoReport::FAULT)
  // {
  //   vehicle_info_msg_.aeb_status = 1;  // 触发
  // }
  // else if (msg->aeb_status == aeb_interfaces::msg::AebInfoReport::OFF)
  // {
  //   vehicle_info_msg_.aeb_status = 0;  // 未触发
  // }
  // else
  // {
  //   vehicle_info_msg_.aeb_status = 0;  // 默认未触发
  // }
}

void PixmovingChassisInterfaceNode::onAebInfoShadow(
  const aeb_interfaces::msg::AebInfoShadow::SharedPtr msg)
{
  if (msg->aeb_req_no_filter != 0 || msg->aeb_req_filter != 0)
    vehicle_info_msg_.aeb_status = 1;
  else if (msg->fcw_req_no_filter != 0 || msg->fcw_req_filter != 0)
    vehicle_info_msg_.aeb_status = 2;
  else
    vehicle_info_msg_.aeb_status = 0;
}


}  // namespace interface
}  // namespace chassis
}  // namespace pixmoving
