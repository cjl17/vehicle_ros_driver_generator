#include <libs/va_brake_sta_fb.hpp>


VaBrakeStaFb::VaBrakeStaFb() {}

void VaBrakeStaFb::update_bytes(uint8_t bytes_data[8])
{
  for(uint i=0;i<8;i++)
  {
    bytes[i] = bytes_data[i];
  }
}

void VaBrakeStaFb::Parse() {
  vcu_chassis_brake_en_sta_ = vcuchassisbrakeensta();
  vcu_vehicle_brake_lamp_fb_ = vcuvehiclebrakelampfb();
  vcu_chassis_epb_fb_ = vcuchassisepbfb();
  vcu_chassis_brake_communication_lost_ = vcuchassisbrakecommunicationlost();
  vcu_chassis_brake_padl_fb_ = vcuchassisbrakepadlfb();
  vcu_brake_pedal_req_fb_ = vcubrakepedalreqfb();
  vcu_aeb_en_sta_fb_ = vcuaebenstafb();
  vcu_aeb_trigger_sta_fb_ = vcuaebtriggerstafb();
  vcu_chassis_brake_pressure_fb_ = vcuchassisbrakepressurefb();
  vcu_brake_life_ = vcubrakelife();
  vcu_brake_check_sta_ = vcubrakechecksta();
  vcu_energy_recovery_sta_fb_ = vcuenergyrecoverystafb();
  vcu_energy_recovery_tor_fb_ = vcuenergyrecoverytorfb();
}


// config detail: {'bit': 0, 'description': '制动使能状态', 'enum': {0: 'VCU_CHASSIS_BRAKE_EN_STA_DISABLE', 1: 'VCU_CHASSIS_BRAKE_EN_STA_ENABLE'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu_chassis_brake_en_sta', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VaBrakeStaFb::vcuchassisbrakeensta() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(0, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 2, 'description': '制动灯状态反馈', 'enum': {0: 'VCU_VEHICLE_BRAKE_LAMP_FB_OFF', 1: 'VCU_VEHICLE_BRAKE_LAMP_FB_ON'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu_vehicle_brake_lamp_fb', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VaBrakeStaFb::vcuvehiclebrakelampfb() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(2, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 4, 'description': '驻车状态', 'enum': {0: 'VCU_CHASSIS_EPB_FB_RELEASE', 1: 'VCU_CHASSIS_EPB_FB_BRAKE', 2: 'VCU_CHASSIS_EPB_FB_RELEASING', 3: 'VCU_CHASSIS_EPB_FB_BRAKING'}, 'is_signed_var': False, 'len': 2, 'name': 'vcu_chassis_epb_fb', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VaBrakeStaFb::vcuchassisepbfb() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(4, 2);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 7, 'description': '制动控制报文中断提醒', 'enum': {0: 'VCU_CHASSIS_BRAKE_COMMUNICATION_LOST_NORMAL', 1: 'VCU_CHASSIS_BRAKE_COMMUNICATION_LOST_COMMUNICATIONISLOST'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu_chassis_brake_communication_lost', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VaBrakeStaFb::vcuchassisbrakecommunicationlost() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(7, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 8, 'description': '制动踏板值反馈', 'is_signed_var': False, 'len': 10, 'name': 'vcu_chassis_brake_padl_fb', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|100]', 'physical_unit': '%', 'precision': 0.1, 'type': 'double'}
double VaBrakeStaFb::vcuchassisbrakepadlfb() {
  Byte t0(*(bytes + 2));
  int32_t x = t0.get_byte(0, 2);

  Byte t1(*(bytes + 1));
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.100000;
  return ret;
}

// config detail: {'bit': 18, 'description': '自驾状态下用户请求了制动', 'enum': {0: 'VCU_BRAKE_PEDAL_REQ_FB_NOTREQBRAKEPEDAL', 1: 'VCU_BRAKE_PEDAL_REQ_FB_REQBRAKEPEDAL'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu_brake_pedal_req_fb', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VaBrakeStaFb::vcubrakepedalreqfb() {
  Byte t0(*(bytes + 2));
  int32_t x = t0.get_byte(2, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 20, 'description': 'AEB开启状态反馈（预留）', 'enum': {0: 'VCU_AEB_EN_STA_FB_OFF', 1: 'VCU_AEB_EN_STA_FB_ON'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu_aeb_en_sta_fb', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VaBrakeStaFb::vcuaebenstafb() {
  Byte t0(*(bytes + 2));
  int32_t x = t0.get_byte(4, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 22, 'description': 'AEB触发状态反馈（预留）', 'enum': {0: 'VCU_AEB_TRIGGER_STA_FB_OFF', 1: 'VCU_AEB_TRIGGER_STA_FB_AEBTRIGGER'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu_aeb_trigger_sta_fb', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VaBrakeStaFb::vcuaebtriggerstafb() {
  Byte t0(*(bytes + 2));
  int32_t x = t0.get_byte(6, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 24, 'description': '制动压力反馈', 'is_signed_var': False, 'len': 8, 'name': 'vcu_chassis_brake_pressure_fb', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|100]', 'physical_unit': 'bar', 'precision': 1.0, 'type': 'int'}
int VaBrakeStaFb::vcuchassisbrakepressurefb() {
  Byte t0(*(bytes + 3));
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

// config detail: {'bit': 48, 'description': 'VCU循环计数', 'is_signed_var': False, 'len': 4, 'name': 'vcu_brake_life', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int VaBrakeStaFb::vcubrakelife() {
  Byte t0(*(bytes + 6));
  int32_t x = t0.get_byte(0, 4);

  int ret = x;
  return ret;
}

// config detail: {'bit': 52, 'description': '制动控制信号的Checksum或者 life sig校验情况', 'enum': {0: 'VCU_BRAKE_CHECK_STA_CHECKOKORDISABLED_校验正常或校验功能关闭', 1: 'VCU_BRAKE_CHECK_STA_CHECKERROR_校验错误'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu_brake_check_sta', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VaBrakeStaFb::vcubrakechecksta() {
  Byte t0(*(bytes + 6));
  int32_t x = t0.get_byte(4, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 53, 'description': '当前能量回收状态反馈', 'is_signed_var': False, 'len': 1, 'name': 'vcu_energy_recovery_sta_fb', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'bool'}
bool VaBrakeStaFb::vcuenergyrecoverystafb() {
  Byte t0(*(bytes + 6));
  int32_t x = t0.get_byte(5, 1);

  bool ret = x;
  return ret;
}

// config detail: {'bit': 54, 'description': '当前能量回收扭矩反馈', 'is_signed_var': False, 'len': 10, 'name': 'vcu_energy_recovery_tor_fb', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1023]', 'physical_unit': 'Nm', 'precision': 1.0, 'type': 'int'}
int VaBrakeStaFb::vcuenergyrecoverytorfb() {
  Byte t0(*(bytes + 7));
  int32_t x = t0.get_byte(0, 8);

  Byte t1(*(bytes + 6));
  int32_t t = t1.get_byte(6, 2);
  x <<= 2;
  x |= t;

  int ret = x;
  return ret;
}

