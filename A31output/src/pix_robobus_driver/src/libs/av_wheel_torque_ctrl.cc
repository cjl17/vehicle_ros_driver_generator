#include <libs/av_wheel_torque_ctrl.hpp>

int32_t AvWheelTorqueCtrl::ID = 0x135;

// public
AvWheelTorqueCtrl::AvWheelTorqueCtrl() { Reset(); }

void AvWheelTorqueCtrl::UpdateData(double acu_motor_torque_lf_ctrl, double acu_motor_torque_rf_ctrl, double acu_motor_torque_lr_ctrl, double acu_motor_torque_rr_ctrl) {
  set_p_acu_motor_torque_lf_ctrl(acu_motor_torque_lf_ctrl);
  set_p_acu_motor_torque_rf_ctrl(acu_motor_torque_rf_ctrl);
  set_p_acu_motor_torque_lr_ctrl(acu_motor_torque_lr_ctrl);
  set_p_acu_motor_torque_rr_ctrl(acu_motor_torque_rr_ctrl);
}

void AvWheelTorqueCtrl::Reset() {
  // TODO(All) :  you should check this manually
  for(uint8_t i=0;i<8;i++)
  {
    data[i] = 0;
  }
}

uint8_t * AvWheelTorqueCtrl::get_data()
{
  return data;
}



// config detail: {'bit': 0, 'description': '左前电机扭矩', 'is_signed_var': True, 'len': 16, 'name': 'acu_motor_torque_lf_ctrl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[-200|200]', 'physical_unit': 'Nm', 'precision': 0.1, 'type': 'double'}
void AvWheelTorqueCtrl::set_p_acu_motor_torque_lf_ctrl(double acu_motor_torque_lf_ctrl) {
  // acu_motor_torque_lf_ctrl = ProtocolData::BoundedValue(-200.0, 200.0, acu_motor_torque_lf_ctrl);
  int x = acu_motor_torque_lf_ctrl / 0.100000;
  uint8_t a = 0;
  uint8_t t = 0;

  t = x & 0xFF;
  Byte to_set0(a);
  to_set0.set_value(t, 0, 8);
  data[0] += to_set0.return_byte_t();
  x >>= 8;

  t = x & 0xFF;
  Byte to_set1(a);
  to_set1.set_value(t, 0, 8);
  data[1] += to_set1.return_byte_t();
}

// config detail: {'bit': 16, 'description': '右前电机扭矩', 'is_signed_var': True, 'len': 16, 'name': 'acu_motor_torque_rf_ctrl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[-200|200]', 'physical_unit': 'Nm', 'precision': 0.1, 'type': 'double'}
void AvWheelTorqueCtrl::set_p_acu_motor_torque_rf_ctrl(double acu_motor_torque_rf_ctrl) {
  // acu_motor_torque_rf_ctrl = ProtocolData::BoundedValue(-200.0, 200.0, acu_motor_torque_rf_ctrl);
  int x = acu_motor_torque_rf_ctrl / 0.100000;
  uint8_t a = 0;
  uint8_t t = 0;

  t = x & 0xFF;
  Byte to_set0(a);
  to_set0.set_value(t, 0, 8);
  data[2] += to_set0.return_byte_t();
  x >>= 8;

  t = x & 0xFF;
  Byte to_set1(a);
  to_set1.set_value(t, 0, 8);
  data[3] += to_set1.return_byte_t();
}

// config detail: {'bit': 32, 'description': '左后电机扭矩', 'is_signed_var': True, 'len': 16, 'name': 'acu_motor_torque_lr_ctrl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[-200|200]', 'physical_unit': 'Nm', 'precision': 0.1, 'type': 'double'}
void AvWheelTorqueCtrl::set_p_acu_motor_torque_lr_ctrl(double acu_motor_torque_lr_ctrl) {
  // acu_motor_torque_lr_ctrl = ProtocolData::BoundedValue(-200.0, 200.0, acu_motor_torque_lr_ctrl);
  int x = acu_motor_torque_lr_ctrl / 0.100000;
  uint8_t a = 0;
  uint8_t t = 0;

  t = x & 0xFF;
  Byte to_set0(a);
  to_set0.set_value(t, 0, 8);
  data[4] += to_set0.return_byte_t();
  x >>= 8;

  t = x & 0xFF;
  Byte to_set1(a);
  to_set1.set_value(t, 0, 8);
  data[5] += to_set1.return_byte_t();
}

// config detail: {'bit': 48, 'description': '右后电机扭矩', 'is_signed_var': True, 'len': 16, 'name': 'acu_motor_torque_rr_ctrl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[-200|200]', 'physical_unit': 'Nm', 'precision': 0.1, 'type': 'double'}
void AvWheelTorqueCtrl::set_p_acu_motor_torque_rr_ctrl(double acu_motor_torque_rr_ctrl) {
  // acu_motor_torque_rr_ctrl = ProtocolData::BoundedValue(-200.0, 200.0, acu_motor_torque_rr_ctrl);
  int x = acu_motor_torque_rr_ctrl / 0.100000;
  uint8_t a = 0;
  uint8_t t = 0;

  t = x & 0xFF;
  Byte to_set0(a);
  to_set0.set_value(t, 0, 8);
  data[6] += to_set0.return_byte_t();
  x >>= 8;

  t = x & 0xFF;
  Byte to_set1(a);
  to_set1.set_value(t, 0, 8);
  data[7] += to_set1.return_byte_t();
}


