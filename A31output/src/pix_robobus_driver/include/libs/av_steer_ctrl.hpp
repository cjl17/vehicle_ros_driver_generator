#pragma once
#include <libs/Byte.hpp>

class AvSteerCtrl {
public:
	static  int32_t ID;

	AvSteerCtrl();
	void UpdateData(int acu_chassis_steer_en_ctrl, int acu_chassis_steer_mode_ctrl, int acu_chassis_steer_angle_target, int acu_chassis_steer_angle_rear_target, double acu_chassis_steer_angle_speed_ctrl, int acu_steer_life_sig, int acu_check_sum132);
	void Reset();
	uint8_t *get_data();


private:
	
  // config detail: {'bit': 0, 'description': '车辆转向控制使能', 'enum': {0: 'ACU_CHASSIS_STEER_EN_CTRL_DISABLE', 1: 'ACU_CHASSIS_STEER_EN_CTRL_ENABLE'}, 'is_signed_var': False, 'len': 1, 'name': 'acu_chassis_steer_en_ctrl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_acu_chassis_steer_en_ctrl(int acu_chassis_steer_en_ctrl);

  // config detail: {'bit': 4, 'description': '转向模式控制 （车速低于5km/h或请求的转向小于15度才能切换）', 'enum': {0: 'ACU_CHASSIS_STEER_MODE_CTRL_FRONTACKERMAN', 1: 'ACU_CHASSIS_STEER_MODE_CTRL_SAMEFRONTANDBACK', 2: 'ACU_CHASSIS_STEER_MODE_CTRL_FRONTDIFFERENTBACK', 3: 'ACU_CHASSIS_STEER_MODE_CTRL_BACKACKRMAN', 4: 'ACU_CHASSIS_STEER_MODE_CTRL_FRONTBACK'}, 'is_signed_var': False, 'len': 4, 'name': 'acu_chassis_steer_mode_ctrl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|4]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_acu_chassis_steer_mode_ctrl(int acu_chassis_steer_mode_ctrl);

  // config detail: {'bit': 8, 'description': '车辆转向控制（前）', 'is_signed_var': True, 'len': 16, 'name': 'acu_chassis_steer_angle_target', 'offset': 0.0, 'order': 'intel', 'physical_range': '[-500|500]', 'physical_unit': 'deg', 'precision': 1.0, 'type': 'int'}
  void set_p_acu_chassis_steer_angle_target(int acu_chassis_steer_angle_target);

  // config detail: {'bit': 24, 'description': '车辆转向控制（后）', 'is_signed_var': True, 'len': 16, 'name': 'acu_chassis_steer_angle_rear_target', 'offset': 0.0, 'order': 'intel', 'physical_range': '[-500|500]', 'physical_unit': 'deg', 'precision': 1.0, 'type': 'int'}
  void set_p_acu_chassis_steer_angle_rear_target(int acu_chassis_steer_angle_rear_target);

  // config detail: {'bit': 40, 'description': '车辆方向盘转角速度控制', 'is_signed_var': False, 'len': 8, 'name': 'acu_chassis_steer_angle_speed_ctrl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|500]', 'physical_unit': 'deg/s', 'precision': 2.0, 'type': 'double'}
  void set_p_acu_chassis_steer_angle_speed_ctrl(double acu_chassis_steer_angle_speed_ctrl);

  // config detail: {'bit': 48, 'description': '循环计数0~15', 'is_signed_var': False, 'len': 4, 'name': 'acu_steer_life_sig', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|15]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  void set_p_acu_steer_life_sig(int acu_steer_life_sig);

  // config detail: {'bit': 56, 'description': '校验sum=byte0 xor byte1 xor...byte6', 'is_signed_var': False, 'len': 8, 'name': 'acu_check_sum132', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  void set_p_acu_check_sum132(int acu_check_sum132);

private:
	uint8_t data[8];
};



