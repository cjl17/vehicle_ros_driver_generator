#include <libs/va_steer_sta_fb.hpp>


VaSteerStaFb::VaSteerStaFb() {}

void VaSteerStaFb::update_bytes(uint8_t bytes_data[8])
{
  for(uint i=0;i<8;i++)
  {
    bytes[i] = bytes_data[i];
  }
}

void VaSteerStaFb::Parse() {
  vcu_chassis_steer_en_sta_ = vcuchassissteerensta();
  vcu_chassis_steer_slopover_ = vcuchassissteerslopover();
  vcu_chassis_steer_work_mode_ = vcuchassissteerworkmode();
  vcu_chassis_steer_mode_fb_ = vcuchassissteermodefb();
  vcu_chassis_steer_communication_lost_ = vcuchassissteercommunicationlost();
  vcu_chassis_steer_angle_fb_ = vcuchassissteeranglefb();
  vcu_chassis_steer_angle_rear_fb_ = vcuchassissteeranglerearfb();
  vcu_chassis_steer_angle_speed_fb_ = vcuchassissteeranglespeedfb();
  vcu_steer_life_ = vcusteerlife();
  vcu_steer_check_sta_ = vcusteerchecksta();
}


// config detail: {'bit': 0, 'description': '转向使能状态', 'enum': {0: 'VCU_CHASSIS_STEER_EN_STA_DISABLE', 1: 'VCU_CHASSIS_STEER_EN_STA_ENABLE'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu_chassis_steer_en_sta', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VaSteerStaFb::vcuchassissteerensta() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(0, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 1, 'description': '转向控制越界提醒', 'enum': {0: 'VCU_CHASSIS_STEER_SLOPOVER_NORMAL', 1: 'VCU_CHASSIS_STEER_SLOPOVER_OVERSLOP'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu_chassis_steer_slopover', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VaSteerStaFb::vcuchassissteerslopover() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(1, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 2, 'description': '转向线控模式反馈', 'enum': {0: 'VCU_CHASSIS_STEER_WORK_MODE_MACHINE', 1: 'VCU_CHASSIS_STEER_WORK_MODE_WIRE', 2: 'VCU_CHASSIS_STEER_WORK_MODE_POWER'}, 'is_signed_var': False, 'len': 2, 'name': 'vcu_chassis_steer_work_mode', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|2]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VaSteerStaFb::vcuchassissteerworkmode() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(2, 2);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 4, 'description': '转向模式反馈', 'enum': {0: 'VCU_CHASSIS_STEER_MODE_FB_FRONTACKERMAN', 1: 'VCU_CHASSIS_STEER_MODE_FB_SAMEFRONTANDBACK', 2: 'VCU_CHASSIS_STEER_MODE_FB_FRONTDIFFERENTBACK', 3: 'VCU_CHASSIS_STEER_MODE_FB_BACKACKRMAN', 4: 'VCU_CHASSIS_STEER_MODE_FB_FRONTBACK'}, 'is_signed_var': False, 'len': 3, 'name': 'vcu_chassis_steer_mode_fb', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|4]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VaSteerStaFb::vcuchassissteermodefb() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(4, 3);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 7, 'description': '转向控制报文中断提醒', 'enum': {0: 'VCU_CHASSIS_STEER_COMMUNICATION_LOST_NORMAL', 1: 'VCU_CHASSIS_STEER_COMMUNICATION_LOST_COMMUNICATIONISLOST'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu_chassis_steer_communication_lost', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VaSteerStaFb::vcuchassissteercommunicationlost() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(7, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 8, 'description': '前转向方向盘转角反馈', 'is_signed_var': True, 'len': 16, 'name': 'vcu_chassis_steer_angle_fb', 'offset': 0.0, 'order': 'intel', 'physical_range': '[-500|500]', 'physical_unit': 'deg', 'precision': 1.0, 'type': 'int'}
int VaSteerStaFb::vcuchassissteeranglefb() {
  Byte t0(*(bytes + 2));
  int32_t x = t0.get_byte(0, 8);

  Byte t1(*(bytes + 1));
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  x <<= 16;
  x >>= 16;

  int ret = x;
  return ret;
}

// config detail: {'bit': 24, 'description': '后转向方向盘转角反馈', 'is_signed_var': True, 'len': 16, 'name': 'vcu_chassis_steer_angle_rear_fb', 'offset': 0.0, 'order': 'intel', 'physical_range': '[-500|500]', 'physical_unit': 'deg', 'precision': 1.0, 'type': 'int'}
int VaSteerStaFb::vcuchassissteeranglerearfb() {
  Byte t0(*(bytes + 4));
  int32_t x = t0.get_byte(0, 8);

  Byte t1(*(bytes + 3));
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  x <<= 16;
  x >>= 16;

  int ret = x;
  return ret;
}

// config detail: {'bit': 40, 'description': '设置的转向转角速度反馈', 'is_signed_var': False, 'len': 8, 'name': 'vcu_chassis_steer_angle_speed_fb', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|500]', 'physical_unit': 'deg/s', 'precision': 2.0, 'type': 'double'}
double VaSteerStaFb::vcuchassissteeranglespeedfb() {
  Byte t0(*(bytes + 5));
  int32_t x = t0.get_byte(0, 8);

  double ret = x * 2.000000;
  return ret;
}

// config detail: {'bit': 48, 'description': 'VCU循环计数', 'is_signed_var': False, 'len': 4, 'name': 'vcu_steer_life', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int VaSteerStaFb::vcusteerlife() {
  Byte t0(*(bytes + 6));
  int32_t x = t0.get_byte(0, 4);

  int ret = x;
  return ret;
}

// config detail: {'bit': 52, 'description': '转向控制信号的Checksum或者 life sig校验情况', 'enum': {0: 'VCU_STEER_CHECK_STA_CHECKOKORDISABLED_校验正常或校验功能关闭', 1: 'VCU_STEER_CHECK_STA_CHECKERROR_校验错误'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu_steer_check_sta', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VaSteerStaFb::vcusteerchecksta() {
  Byte t0(*(bytes + 6));
  int32_t x = t0.get_byte(4, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

