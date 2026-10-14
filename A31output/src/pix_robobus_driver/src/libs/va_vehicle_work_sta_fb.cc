#include <libs/va_vehicle_work_sta_fb.hpp>


VaVehicleWorkStaFb::VaVehicleWorkStaFb() {}

void VaVehicleWorkStaFb::update_bytes(uint8_t bytes_data[8])
{
  for(uint i=0;i<8;i++)
  {
    bytes[i] = bytes_data[i];
  }
}

void VaVehicleWorkStaFb::Parse() {
  vcu_driving_mode_fb_ = vcudrivingmodefb();
  vcu_chassis_power_sta_fb_ = vcuchassispowerstafb();
  vcu_chassis_power_dc_sta_ = vcuchassispowerdcsta();
  vcu_chassis_speed_limited_mode_fb_ = vcuchassisspeedlimitedmodefb();
  vcu_chassis_power_limite_sta_ = vcuchassispowerlimitesta();
  vcu_sys_eco_mode_ = vcusysecomode();
  vcu_chassis_speed_limited_val_fb_ = vcuchassisspeedlimitedvalfb();
  vcu_chassis_low_power_volt_sta_ = vcuchassislowpowervoltsta();
  vcu_chassis_e_stop_sta_fb_ = vcuchassisestopstafb();
  vcu_crash_front_sta_ = vcucrashfrontsta();
  vcu_crash_rear_sta_ = vcucrashrearsta();
  vcu_crash_left_sta_ = vcucrashleftsta();
  vcu_crash_right_sta_ = vcucrashrightsta();
  vcu_life_ = vculife();
  vcu_check_sum_ = vcuchecksum();
}


// config detail: {'bit': 0, 'description': '驾驶模式反馈', 'enum': {0: 'VCU_DRIVING_MODE_FB_STANDBY', 1: 'VCU_DRIVING_MODE_FB_SELFDRIVING', 2: 'VCU_DRIVING_MODE_FB_REMOTE', 3: 'VCU_DRIVING_MODE_FB_TAKEOVER'}, 'is_signed_var': False, 'len': 2, 'name': 'vcu_driving_mode_fb', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VaVehicleWorkStaFb::vcudrivingmodefb() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(0, 2);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 2, 'description': '车辆上电状态反馈', 'enum': {0: 'VCU_CHASSIS_POWER_STA_FB_SLEEP', 1: 'VCU_CHASSIS_POWER_STA_FB_ONACC', 2: 'VCU_CHASSIS_POWER_STA_FB_READY', 3: 'VCU_CHASSIS_POWER_STA_FB_OFF'}, 'is_signed_var': False, 'len': 2, 'name': 'vcu_chassis_power_sta_fb', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VaVehicleWorkStaFb::vcuchassispowerstafb() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(2, 2);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 4, 'description': 'DC工作状态', 'enum': {0: 'VCU_CHASSIS_POWER_DC_STA_OFF', 1: 'VCU_CHASSIS_POWER_DC_STA_ON', 2: 'VCU_CHASSIS_POWER_DC_STA_STANDBY'}, 'is_signed_var': False, 'len': 2, 'name': 'vcu_chassis_power_dc_sta', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|2]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VaVehicleWorkStaFb::vcuchassispowerdcsta() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(4, 2);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 8, 'description': '车辆限速状态', 'enum': {0: 'VCU_CHASSIS_SPEED_LIMITED_MODE_FB_DEFAULT', 1: 'VCU_CHASSIS_SPEED_LIMITED_MODE_FB_LIMIT'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu_chassis_speed_limited_mode_fb', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VaVehicleWorkStaFb::vcuchassisspeedlimitedmodefb() {
  Byte t0(*(bytes + 1));
  int32_t x = t0.get_byte(0, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 9, 'description': '功率限制状态', 'enum': {0: 'VCU_CHASSIS_POWER_LIMITE_STA_DEFAULT', 1: 'VCU_CHASSIS_POWER_LIMITE_STA_LIMIT'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu_chassis_power_limite_sta', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VaVehicleWorkStaFb::vcuchassispowerlimitesta() {
  Byte t0(*(bytes + 1));
  int32_t x = t0.get_byte(1, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 10, 'description': '节能模式反馈', 'enum': {0: 'VCU_SYS_ECO_MODE_DEFAULT', 1: 'VCU_SYS_ECO_MODE_ECO', 2: 'VCU_SYS_ECO_MODE_SPORT'}, 'is_signed_var': False, 'len': 2, 'name': 'vcu_sys_eco_mode', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|2]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VaVehicleWorkStaFb::vcusysecomode() {
  Byte t0(*(bytes + 1));
  int32_t x = t0.get_byte(2, 2);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 16, 'description': '车辆限速值反馈', 'is_signed_var': False, 'len': 16, 'name': 'vcu_chassis_speed_limited_val_fb', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|50]', 'physical_unit': 'm/s', 'precision': 0.1, 'type': 'double'}
double VaVehicleWorkStaFb::vcuchassisspeedlimitedvalfb() {
  Byte t0(*(bytes + 3));
  int32_t x = t0.get_byte(0, 8);

  Byte t1(*(bytes + 2));
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.100000;
  return ret;
}

// config detail: {'bit': 32, 'description': '低压蓄电池电压', 'is_signed_var': False, 'len': 8, 'name': 'vcu_chassis_low_power_volt_sta', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|25]', 'physical_unit': 'V', 'precision': 0.1, 'type': 'double'}
double VaVehicleWorkStaFb::vcuchassislowpowervoltsta() {
  Byte t0(*(bytes + 4));
  int32_t x = t0.get_byte(0, 8);

  double ret = x * 0.100000;
  return ret;
}

// config detail: {'bit': 40, 'description': '紧急停车状态反馈', 'enum': {0: 'VCU_CHASSIS_E_STOP_STA_FB_NOTESTOP', 1: 'VCU_CHASSIS_E_STOP_STA_FB_CHASSISESTOP', 2: 'VCU_CHASSIS_E_STOP_STA_FB_REMOTEESTOP', 3: 'VCU_CHASSIS_E_STOP_STA_FB_CHASSISERRESTOP', 4: 'VCU_CHASSIS_E_STOP_STA_FB_ACULOSSESTOP', 5: 'VCU_CHASSIS_E_STOP_STA_FB_ACUESTOP', 6: 'VCU_CHASSIS_E_STOP_STA_FB_CRASHESTOP'}, 'is_signed_var': False, 'len': 4, 'name': 'vcu_chassis_e_stop_sta_fb', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VaVehicleWorkStaFb::vcuchassisestopstafb() {
  Byte t0(*(bytes + 5));
  int32_t x = t0.get_byte(0, 4);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 44, 'description': '车辆前碰撞传感器反馈（预留）', 'enum': {0: 'VCU_CRASH_FRONT_STA_OFF', 1: 'VCU_CRASH_FRONT_STA_COLLIDE'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu_crash_front_sta', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VaVehicleWorkStaFb::vcucrashfrontsta() {
  Byte t0(*(bytes + 5));
  int32_t x = t0.get_byte(4, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 45, 'description': '车辆后碰撞传感器反馈（预留）', 'enum': {0: 'VCU_CRASH_REAR_STA_OFF', 1: 'VCU_CRASH_REAR_STA_COLLIDE'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu_crash_rear_sta', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VaVehicleWorkStaFb::vcucrashrearsta() {
  Byte t0(*(bytes + 5));
  int32_t x = t0.get_byte(5, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 46, 'description': '车辆左碰撞传感器反馈（预留）', 'enum': {0: 'VCU_CRASH_LEFT_STA_OFF', 1: 'VCU_CRASH_LEFT_STA_COLLIDE'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu_crash_left_sta', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VaVehicleWorkStaFb::vcucrashleftsta() {
  Byte t0(*(bytes + 5));
  int32_t x = t0.get_byte(6, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 47, 'description': '车辆右碰撞传感器反馈（预留）', 'enum': {0: 'VCU_CRASH_RIGHT_STA_OFF', 1: 'VCU_CRASH_RIGHT_STA_COLLIDE'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu_crash_right_sta', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VaVehicleWorkStaFb::vcucrashrightsta() {
  Byte t0(*(bytes + 5));
  int32_t x = t0.get_byte(7, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 48, 'description': 'VCU循环计数', 'is_signed_var': False, 'len': 4, 'name': 'vcu_life', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int VaVehicleWorkStaFb::vculife() {
  Byte t0(*(bytes + 6));
  int32_t x = t0.get_byte(0, 4);

  int ret = x;
  return ret;
}

// config detail: {'bit': 56, 'description': '校验sum=byte0 xor byte1 xor...byte6', 'is_signed_var': False, 'len': 8, 'name': 'vcu_check_sum', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int VaVehicleWorkStaFb::vcuchecksum() {
  Byte t0(*(bytes + 7));
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

