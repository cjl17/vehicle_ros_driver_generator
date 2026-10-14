#pragma once
#include <libs/Byte.hpp>

class AvWheelTorqueCtrl {
public:
	static  int32_t ID;

	AvWheelTorqueCtrl();
	void UpdateData(double acu_motor_torque_lf_ctrl, double acu_motor_torque_rf_ctrl, double acu_motor_torque_lr_ctrl, double acu_motor_torque_rr_ctrl);
	void Reset();
	uint8_t *get_data();


private:
	
  // config detail: {'bit': 0, 'description': '左前电机扭矩', 'is_signed_var': True, 'len': 16, 'name': 'acu_motor_torque_lf_ctrl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[-200|200]', 'physical_unit': 'Nm', 'precision': 0.1, 'type': 'double'}
  void set_p_acu_motor_torque_lf_ctrl(double acu_motor_torque_lf_ctrl);

  // config detail: {'bit': 16, 'description': '右前电机扭矩', 'is_signed_var': True, 'len': 16, 'name': 'acu_motor_torque_rf_ctrl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[-200|200]', 'physical_unit': 'Nm', 'precision': 0.1, 'type': 'double'}
  void set_p_acu_motor_torque_rf_ctrl(double acu_motor_torque_rf_ctrl);

  // config detail: {'bit': 32, 'description': '左后电机扭矩', 'is_signed_var': True, 'len': 16, 'name': 'acu_motor_torque_lr_ctrl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[-200|200]', 'physical_unit': 'Nm', 'precision': 0.1, 'type': 'double'}
  void set_p_acu_motor_torque_lr_ctrl(double acu_motor_torque_lr_ctrl);

  // config detail: {'bit': 48, 'description': '右后电机扭矩', 'is_signed_var': True, 'len': 16, 'name': 'acu_motor_torque_rr_ctrl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[-200|200]', 'physical_unit': 'Nm', 'precision': 0.1, 'type': 'double'}
  void set_p_acu_motor_torque_rr_ctrl(double acu_motor_torque_rr_ctrl);

private:
	uint8_t data[8];
};



