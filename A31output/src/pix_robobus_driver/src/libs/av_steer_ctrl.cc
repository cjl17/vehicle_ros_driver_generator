#include <libs/av_steer_ctrl.hpp>

int32_t AvSteerCtrl::ID = 0x132;

// public
AvSteerCtrl::AvSteerCtrl() { Reset(); }

void AvSteerCtrl::UpdateData(int acu_chassis_steer_en_ctrl, int acu_chassis_steer_mode_ctrl, int acu_chassis_steer_angle_target, int acu_chassis_steer_angle_rear_target, double acu_chassis_steer_angle_speed_ctrl, int acu_steer_life_sig, int acu_check_sum132) {
  set_p_acu_chassis_steer_en_ctrl(acu_chassis_steer_en_ctrl);
  set_p_acu_chassis_steer_mode_ctrl(acu_chassis_steer_mode_ctrl);
  set_p_acu_chassis_steer_angle_target(acu_chassis_steer_angle_target);
  set_p_acu_chassis_steer_angle_rear_target(acu_chassis_steer_angle_rear_target);
  set_p_acu_chassis_steer_angle_speed_ctrl(acu_chassis_steer_angle_speed_ctrl);
  set_p_acu_steer_life_sig(acu_steer_life_sig);
  set_p_acu_check_sum132(acu_check_sum132);
}

void AvSteerCtrl::Reset() {
  // TODO(All) :  you should check this manually
  for(uint8_t i=0;i<8;i++)
  {
    data[i] = 0;
  }
}

uint8_t * AvSteerCtrl::get_data()
{
  return data;
}



// config detail: {'bit': 0, 'description': '车辆转向控制使能', 'enum': {0: 'ACU_CHASSIS_STEER_EN_CTRL_DISABLE', 1: 'ACU_CHASSIS_STEER_EN_CTRL_ENABLE'}, 'is_signed_var': False, 'len': 1, 'name': 'acu_chassis_steer_en_ctrl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void AvSteerCtrl::set_p_acu_chassis_steer_en_ctrl(int acu_chassis_steer_en_ctrl) {
  int x = acu_chassis_steer_en_ctrl;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 0, 1);
  data[0] += to_set.return_byte_t();
  
}

// config detail: {'bit': 4, 'description': '转向模式控制 （车速低于5km/h或请求的转向小于15度才能切换）', 'enum': {0: 'ACU_CHASSIS_STEER_MODE_CTRL_FRONTACKERMAN', 1: 'ACU_CHASSIS_STEER_MODE_CTRL_SAMEFRONTANDBACK', 2: 'ACU_CHASSIS_STEER_MODE_CTRL_FRONTDIFFERENTBACK', 3: 'ACU_CHASSIS_STEER_MODE_CTRL_BACKACKRMAN', 4: 'ACU_CHASSIS_STEER_MODE_CTRL_FRONTBACK'}, 'is_signed_var': False, 'len': 4, 'name': 'acu_chassis_steer_mode_ctrl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|4]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void AvSteerCtrl::set_p_acu_chassis_steer_mode_ctrl(int acu_chassis_steer_mode_ctrl) {
  int x = acu_chassis_steer_mode_ctrl;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 4, 4);
  data[0] += to_set.return_byte_t();
  
}

// config detail: {'bit': 8, 'description': '车辆转向控制（前）', 'is_signed_var': True, 'len': 16, 'name': 'acu_chassis_steer_angle_target', 'offset': 0.0, 'order': 'intel', 'physical_range': '[-500|500]', 'physical_unit': 'deg', 'precision': 1.0, 'type': 'int'}
void AvSteerCtrl::set_p_acu_chassis_steer_angle_target(int acu_chassis_steer_angle_target) {
  // acu_chassis_steer_angle_target = ProtocolData::BoundedValue(-500, 500, acu_chassis_steer_angle_target);
  int x = acu_chassis_steer_angle_target;
  uint8_t a = 0;
  uint8_t t = 0;

  t = x & 0xFF;
  Byte to_set0(a);
  to_set0.set_value(t, 0, 8);
  data[1] += to_set0.return_byte_t();
  x >>= 8;

  t = x & 0xFF;
  Byte to_set1(a);
  to_set1.set_value(t, 0, 8);
  data[2] += to_set1.return_byte_t();
}

// config detail: {'bit': 24, 'description': '车辆转向控制（后）', 'is_signed_var': True, 'len': 16, 'name': 'acu_chassis_steer_angle_rear_target', 'offset': 0.0, 'order': 'intel', 'physical_range': '[-500|500]', 'physical_unit': 'deg', 'precision': 1.0, 'type': 'int'}
void AvSteerCtrl::set_p_acu_chassis_steer_angle_rear_target(int acu_chassis_steer_angle_rear_target) {
  // acu_chassis_steer_angle_rear_target = ProtocolData::BoundedValue(-500, 500, acu_chassis_steer_angle_rear_target);
  int x = acu_chassis_steer_angle_rear_target;
  uint8_t a = 0;
  uint8_t t = 0;

  t = x & 0xFF;
  Byte to_set0(a);
  to_set0.set_value(t, 0, 8);
  data[3] += to_set0.return_byte_t();
  x >>= 8;

  t = x & 0xFF;
  Byte to_set1(a);
  to_set1.set_value(t, 0, 8);
  data[4] += to_set1.return_byte_t();
}

// config detail: {'bit': 40, 'description': '车辆方向盘转角速度控制', 'is_signed_var': False, 'len': 8, 'name': 'acu_chassis_steer_angle_speed_ctrl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|500]', 'physical_unit': 'deg/s', 'precision': 2.0, 'type': 'double'}
void AvSteerCtrl::set_p_acu_chassis_steer_angle_speed_ctrl(double acu_chassis_steer_angle_speed_ctrl) {
  // acu_chassis_steer_angle_speed_ctrl = ProtocolData::BoundedValue(0.0, 500.0, acu_chassis_steer_angle_speed_ctrl);
  int x = acu_chassis_steer_angle_speed_ctrl / 2.000000;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 0, 8);
  data[5] += to_set.return_byte_t();
  
}

// config detail: {'bit': 48, 'description': '循环计数0~15', 'is_signed_var': False, 'len': 4, 'name': 'acu_steer_life_sig', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
void AvSteerCtrl::set_p_acu_steer_life_sig(int acu_steer_life_sig) {
  // acu_steer_life_sig = ProtocolData::BoundedValue(0, 15, acu_steer_life_sig);
  int x = acu_steer_life_sig;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 0, 4);
  data[6] += to_set.return_byte_t();
  
}

// config detail: {'bit': 56, 'description': '校验sum=byte0 xor byte1 xor...byte6', 'is_signed_var': False, 'len': 8, 'name': 'acu_check_sum132', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
void AvSteerCtrl::set_p_acu_check_sum132(int acu_check_sum132) {
  // acu_check_sum132 = ProtocolData::BoundedValue(0, 255, acu_check_sum132);
  int x = acu_check_sum132;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 0, 8);
  data[7] += to_set.return_byte_t();
  
}


