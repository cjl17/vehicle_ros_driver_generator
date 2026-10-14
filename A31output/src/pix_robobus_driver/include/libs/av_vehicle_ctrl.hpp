#pragma once
#include <libs/Byte.hpp>

class AvVehicleCtrl {
public:
	static  int32_t ID;

	AvVehicleCtrl();
	void UpdateData(int acu_vehicle_pos_lamp_ctrl, int acu_vehicle_head_lamp_ctrl, int acu_vehicle_left_lamp_ctrl, int acu_vehicle_right_lamp_ctrl, int acu_vehicle_high_beam_ctrl, int acu_vehicle_fog_lamp_ctrl, int acu_vehicle_body_light_ctrl, int acu_vehicle_read_light_ctrl, int acu_vehicle_voice, int acu_vehicle_wipers_ctrl, int acu_vehicle_door_ctrl, int acu_vehicle_window_ctrl, int acu_chassis_speed_limite_mode, int acu_vehicle_horn_ctrl, int acu_vehicle_spray_ctrl, double acu_chassis_speed_limite_val, int acu_check_sum_en);
	void Reset();
	uint8_t *get_data();


private:
	
  // config detail: {'bit': 0, 'description': '位置灯控制', 'enum': {0: 'ACU_VEHICLE_POS_LAMP_CTRL_OFF', 1: 'ACU_VEHICLE_POS_LAMP_CTRL_ON'}, 'is_signed_var': False, 'len': 1, 'name': 'acu_vehicle_pos_lamp_ctrl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_acu_vehicle_pos_lamp_ctrl(int acu_vehicle_pos_lamp_ctrl);

  // config detail: {'bit': 1, 'description': '近光灯控制', 'enum': {0: 'ACU_VEHICLE_HEAD_LAMP_CTRL_OFF', 1: 'ACU_VEHICLE_HEAD_LAMP_CTRL_ON'}, 'is_signed_var': False, 'len': 1, 'name': 'acu_vehicle_head_lamp_ctrl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_acu_vehicle_head_lamp_ctrl(int acu_vehicle_head_lamp_ctrl);

  // config detail: {'bit': 2, 'description': '左转向灯控制', 'enum': {0: 'ACU_VEHICLE_LEFT_LAMP_CTRL_OFF', 1: 'ACU_VEHICLE_LEFT_LAMP_CTRL_ON'}, 'is_signed_var': False, 'len': 1, 'name': 'acu_vehicle_left_lamp_ctrl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_acu_vehicle_left_lamp_ctrl(int acu_vehicle_left_lamp_ctrl);

  // config detail: {'bit': 3, 'description': '右转向灯控制', 'enum': {0: 'ACU_VEHICLE_RIGHT_LAMP_CTRL_OFF', 1: 'ACU_VEHICLE_RIGHT_LAMP_CTRL_ON'}, 'is_signed_var': False, 'len': 1, 'name': 'acu_vehicle_right_lamp_ctrl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_acu_vehicle_right_lamp_ctrl(int acu_vehicle_right_lamp_ctrl);

  // config detail: {'bit': 4, 'description': '远光灯控制', 'enum': {0: 'ACU_VEHICLE_HIGH_BEAM_CTRL_OFF', 1: 'ACU_VEHICLE_HIGH_BEAM_CTRL_ON'}, 'is_signed_var': False, 'len': 1, 'name': 'acu_vehicle_high_beam_ctrl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_acu_vehicle_high_beam_ctrl(int acu_vehicle_high_beam_ctrl);

  // config detail: {'bit': 5, 'description': '雾灯控制', 'enum': {0: 'ACU_VEHICLE_FOG_LAMP_CTRL_OFF', 1: 'ACU_VEHICLE_FOG_LAMP_CTRL_ON'}, 'is_signed_var': False, 'len': 1, 'name': 'acu_vehicle_fog_lamp_ctrl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_acu_vehicle_fog_lamp_ctrl(int acu_vehicle_fog_lamp_ctrl);

  // config detail: {'bit': 6, 'description': '氛围灯控制', 'enum': {0: 'ACU_VEHICLE_BODY_LIGHT_CTRL_OFF', 1: 'ACU_VEHICLE_BODY_LIGHT_CTRL_ON'}, 'is_signed_var': False, 'len': 1, 'name': 'acu_vehicle_body_light_ctrl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_acu_vehicle_body_light_ctrl(int acu_vehicle_body_light_ctrl);

  // config detail: {'bit': 7, 'description': '车内灯光总控制', 'enum': {0: 'ACU_VEHICLE_READ_LIGHT_CTRL_OFF', 1: 'ACU_VEHICLE_READ_LIGHT_CTRL_ON'}, 'is_signed_var': False, 'len': 1, 'name': 'acu_vehicle_read_light_ctrl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_acu_vehicle_read_light_ctrl(int acu_vehicle_read_light_ctrl);

  // config detail: {'bit': 8, 'description': '提示音控制', 'enum': {0: 'ACU_VEHICLE_VOICE_OFF', 1: 'ACU_VEHICLE_VOICE_TURNLEFT', 2: 'ACU_VEHICLE_VOICE_TURNRIGHT', 3: 'ACU_VEHICLE_VOICE_BACKWARD'}, 'is_signed_var': False, 'len': 2, 'name': 'acu_vehicle_voice', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_acu_vehicle_voice(int acu_vehicle_voice);

  // config detail: {'bit': 10, 'description': '雨刮控制', 'enum': {0: 'ACU_VEHICLE_WIPERS_CTRL_OFF', 1: 'ACU_VEHICLE_WIPERS_CTRL_LOW', 2: 'ACU_VEHICLE_WIPERS_CTRL_MID', 3: 'ACU_VEHICLE_WIPERS_CTRL_HIGH'}, 'is_signed_var': False, 'len': 2, 'name': 'acu_vehicle_wipers_ctrl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|3]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_acu_vehicle_wipers_ctrl(int acu_vehicle_wipers_ctrl);

  // config detail: {'bit': 12, 'description': '车门控制(触发型)', 'enum': {0: 'ACU_VEHICLE_DOOR_CTRL_DEFAULT_保持之前状态', 1: 'ACU_VEHICLE_DOOR_CTRL_CLOSE', 2: 'ACU_VEHICLE_DOOR_CTRL_OPEN'}, 'is_signed_var': False, 'len': 2, 'name': 'acu_vehicle_door_ctrl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|2]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_acu_vehicle_door_ctrl(int acu_vehicle_door_ctrl);

  // config detail: {'bit': 14, 'description': '车窗控制（预留）', 'enum': {0: 'ACU_VEHICLE_WINDOW_CTRL_DEFAULT', 1: 'ACU_VEHICLE_WINDOW_CTRL_CLOSE', 2: 'ACU_VEHICLE_WINDOW_CTRL_OPEN'}, 'is_signed_var': False, 'len': 2, 'name': 'acu_vehicle_window_ctrl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|2]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_acu_vehicle_window_ctrl(int acu_vehicle_window_ctrl);

  // config detail: {'bit': 24, 'description': '限速控制', 'enum': {0: 'ACU_CHASSIS_SPEED_LIMITE_MODE_DEFAULT', 1: 'ACU_CHASSIS_SPEED_LIMITE_MODE_LIMIT'}, 'is_signed_var': False, 'len': 1, 'name': 'acu_chassis_speed_limite_mode', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_acu_chassis_speed_limite_mode(int acu_chassis_speed_limite_mode);

  // config detail: {'bit': 25, 'description': '电喇叭控制 (VCU限制单次开启时间不超过3秒,防止喇叭一直鸣叫)', 'enum': {0: 'ACU_VEHICLE_HORN_CTRL_OFF', 1: 'ACU_VEHICLE_HORN_CTRL_ON'}, 'is_signed_var': False, 'len': 1, 'name': 'acu_vehicle_horn_ctrl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_acu_vehicle_horn_ctrl(int acu_vehicle_horn_ctrl);

  // config detail: {'bit': 26, 'description': '雨刮喷淋控制 (VCU限制单次喷淋时间不超过5秒)', 'enum': {0: 'ACU_VEHICLE_SPRAY_CTRL_OFF', 1: 'ACU_VEHICLE_SPRAY_CTRL_ON'}, 'is_signed_var': False, 'len': 1, 'name': 'acu_vehicle_spray_ctrl', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_acu_vehicle_spray_ctrl(int acu_vehicle_spray_ctrl);

  // config detail: {'bit': 32, 'description': '速度限制值', 'is_signed_var': False, 'len': 8, 'name': 'acu_chassis_speed_limite_val', 'offset': 0.0, 'order': 'intel', 'physical_range': '[1|20]', 'physical_unit': 'm/s', 'precision': 0.1, 'type': 'double'}
  void set_p_acu_chassis_speed_limite_val(double acu_chassis_speed_limite_val);

  // config detail: {'bit': 48, 'description': '校验模式使能 (发1：disable可关闭校验，目前只校验0x130~132的life信号)', 'enum': {0: 'ACU_CHECK_SUM_EN_ENABLE', 1: 'ACU_CHECK_SUM_EN_DISABLE'}, 'is_signed_var': False, 'len': 1, 'name': 'acu_check_sum_en', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_acu_check_sum_en(int acu_check_sum_en);

private:
	uint8_t data[8];
};



