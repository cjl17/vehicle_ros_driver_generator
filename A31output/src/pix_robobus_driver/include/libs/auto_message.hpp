#pragma once
#include <libs/Byte.hpp>

class AutoMessage {
public:
	static  int32_t ID;

	AutoMessage();
	void UpdateData(int auto_drive_mode, int auto_heartbeat);
	void Reset();
	uint8_t *get_data();


private:
	
  // config detail: {'bit': 0, 'description': '自驾状态', 'enum': {0: 'AUTO_DRIVE_MODE_AUTOPLIOTMODE', 1: 'AUTO_DRIVE_MODE_RECEIVEDAREMOTEREQUEST', 2: 'AUTO_DRIVE_MODE_ALLOWREMOTETAKEOVER', 3: 'AUTO_DRIVE_MODE_AUTOEMERGENCYSTOP'}, 'is_signed_var': False, 'len': 8, 'name': 'auto_drive_mode', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  void set_p_auto_drive_mode(int auto_drive_mode);

  // config detail: {'bit': 56, 'description': '自动驾驶心跳包', 'is_signed_var': False, 'len': 8, 'name': 'auto_heartbeat', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  void set_p_auto_heartbeat(int auto_heartbeat);

private:
	uint8_t data[8];
};



