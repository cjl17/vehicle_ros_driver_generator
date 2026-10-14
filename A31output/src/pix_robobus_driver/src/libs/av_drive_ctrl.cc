#include <libs/av_drive_ctrl.hpp>

int32_t AvDriveCtrl::ID = 0x130;

// public
AvDriveCtrl::AvDriveCtrl() { Reset(); }

void AvDriveCtrl::UpdateData(int acu_chassis_driver_en_ctrl, int acu_chassis_driver_mode_ctrl, int acu_chassis_gear_ctrl, int acu_chassis4_wd_mode_ctrl, double acu_chassis_speed_ctrl, double acu_chassis_throttle_pdl_target, int acu_drive_life_sig, int acu_check_sum130) {
  set_p_acu_chassis_driver_en_ctrl(acu_chassis_driver_en_ctrl);
  set_p_acu_chassis_driver_mode_ctrl(acu_chassis_driver_mode_ctrl);
  set_p_acu_chassis_gear_ctrl(acu_chassis_gear_ctrl);
  set_p_acu_chassis4_wd_mode_ctrl(acu_chassis4_wd_mode_ctrl);
  set_p_acu_chassis_speed_ctrl(acu_chassis_speed_ctrl);
  set_p_acu_chassis_throttle_pdl_target(acu_chassis_throttle_pdl_target);
  set_p_acu_drive_life_sig(acu_drive_life_sig);
  set_p_acu_check_sum130(acu_check_sum130);
}

void AvDriveCtrl::Reset() {
  // TODO(All) :  you should check this manually
  for(uint8_t i=0;i<8;i++)
  {
    data[i] = 0;
  }
}

uint8_t * AvDriveCtrl::get_data()
{
  return data;
}



// config detail: {'bit': 0, 'description': '车辆驱动控制使能', 'enum': {0: 'ACU_CHASSIS_DRIVER_EN_CTRL_DISABLE', 1: 'ACU_CHASSIS_DRIVER_EN_CTRL_ENABLE'}, 'is_signed_var': False, 'len': 1, 'name': 'acu_chassis_driver_en_ctrl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void AvDriveCtrl::set_p_acu_chassis_driver_en_ctrl(int acu_chassis_driver_en_ctrl) {
  int x = acu_chassis_driver_en_ctrl;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 0, 1);
  data[0] += to_set.return_byte_t();
  
}

// config detail: {'bit': 2, 'description': '驱动模式控制', 'enum': {0: 'ACU_CHASSIS_DRIVER_MODE_CTRL_SPEEDCTRLMODE', 1: 'ACU_CHASSIS_DRIVER_MODE_CTRL_THROTTLECTRLMODE', 2: 'ACU_CHASSIS_DRIVER_MODE_CTRL_RESERVE1', 3: 'ACU_CHASSIS_DRIVER_MODE_CTRL_RESERVE2'}, 'is_signed_var': False, 'len': 2, 'name': 'acu_chassis_driver_mode_ctrl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void AvDriveCtrl::set_p_acu_chassis_driver_mode_ctrl(int acu_chassis_driver_mode_ctrl) {
  int x = acu_chassis_driver_mode_ctrl;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 2, 2);
  data[0] += to_set.return_byte_t();
  
}

// config detail: {'bit': 4, 'description': '档位控制 (与反馈的档位一致后 才能控制油门或速度)', 'enum': {0: 'ACU_CHASSIS_GEAR_CTRL_DEFAULTN', 1: 'ACU_CHASSIS_GEAR_CTRL_D', 2: 'ACU_CHASSIS_GEAR_CTRL_N', 3: 'ACU_CHASSIS_GEAR_CTRL_R'}, 'is_signed_var': False, 'len': 2, 'name': 'acu_chassis_gear_ctrl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void AvDriveCtrl::set_p_acu_chassis_gear_ctrl(int acu_chassis_gear_ctrl) {
  int x = acu_chassis_gear_ctrl;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 4, 2);
  data[0] += to_set.return_byte_t();
  
}

// config detail: {'bit': 6, 'description': '四驱两驱切换控制', 'enum': {0: 'ACU_CHASSIS4_WD_MODE_CTRL_FOURWD', 1: 'ACU_CHASSIS4_WD_MODE_CTRL_RWD', 2: 'ACU_CHASSIS4_WD_MODE_CTRL_FWD'}, 'is_signed_var': False, 'len': 2, 'name': 'acu_chassis4_wd_mode_ctrl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|2]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void AvDriveCtrl::set_p_acu_chassis4_wd_mode_ctrl(int acu_chassis4_wd_mode_ctrl) {
  int x = acu_chassis4_wd_mode_ctrl;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 6, 2);
  data[0] += to_set.return_byte_t();
  
}

// config detail: {'bit': 8, 'description': '车辆速度控制 （预留）', 'is_signed_var': False, 'len': 16, 'name': 'acu_chassis_speed_ctrl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|50]', 'physical_unit': 'm/s', 'precision': 0.01, 'type': 'double'}
void AvDriveCtrl::set_p_acu_chassis_speed_ctrl(double acu_chassis_speed_ctrl) {
  // acu_chassis_speed_ctrl = ProtocolData::BoundedValue(0.0, 50.0, acu_chassis_speed_ctrl);
  int x = acu_chassis_speed_ctrl / 0.010000;
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

// config detail: {'bit': 24, 'description': '车辆油门控制', 'is_signed_var': False, 'len': 10, 'name': 'acu_chassis_throttle_pdl_target', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|100]', 'physical_unit': '%', 'precision': 0.1, 'type': 'double'}
void AvDriveCtrl::set_p_acu_chassis_throttle_pdl_target(double acu_chassis_throttle_pdl_target) {
  // acu_chassis_throttle_pdl_target = ProtocolData::BoundedValue(0.0, 100.0, acu_chassis_throttle_pdl_target);
  int x = acu_chassis_throttle_pdl_target / 0.100000;
  uint8_t a = 0;
  uint8_t t = 0;

  t = x & 0xFF;
  Byte to_set0(a);
  to_set0.set_value(t, 0, 8);
  data[3] += to_set0.return_byte_t();
  x >>= 8;

  t = x & 0x3;
  Byte to_set1(a);
  to_set1.set_value(t, 0, 2);
  data[4] += to_set1.return_byte_t();
}

// config detail: {'bit': 48, 'description': '循环计数0~15', 'is_signed_var': False, 'len': 4, 'name': 'acu_drive_life_sig', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
void AvDriveCtrl::set_p_acu_drive_life_sig(int acu_drive_life_sig) {
  // acu_drive_life_sig = ProtocolData::BoundedValue(0, 15, acu_drive_life_sig);
  int x = acu_drive_life_sig;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 0, 4);
  data[6] += to_set.return_byte_t();
  
}

// config detail: {'bit': 56, 'description': '校验sum=byte0 xor byte1 xor...byte6', 'is_signed_var': False, 'len': 8, 'name': 'acu_check_sum130', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
void AvDriveCtrl::set_p_acu_check_sum130(int acu_check_sum130) {
  // acu_check_sum130 = ProtocolData::BoundedValue(0, 255, acu_check_sum130);
  int x = acu_check_sum130;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 0, 8);
  data[7] += to_set.return_byte_t();
  
}


