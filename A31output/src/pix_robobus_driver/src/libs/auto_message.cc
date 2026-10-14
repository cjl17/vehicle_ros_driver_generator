#include <libs/auto_message.hpp>

int32_t AutoMessage::ID = 0x3A0;

// public
AutoMessage::AutoMessage() { Reset(); }

void AutoMessage::UpdateData(int auto_drive_mode, int auto_heartbeat) {
  set_p_auto_drive_mode(auto_drive_mode);
  set_p_auto_heartbeat(auto_heartbeat);
}

void AutoMessage::Reset() {
  // TODO(All) :  you should check this manually
  for(uint8_t i=0;i<8;i++)
  {
    data[i] = 0;
  }
}

uint8_t * AutoMessage::get_data()
{
  return data;
}



// config detail: {'bit': 0, 'description': '自驾状态', 'enum': {0: 'AUTO_DRIVE_MODE_AUTOPLIOTMODE', 1: 'AUTO_DRIVE_MODE_RECEIVEDAREMOTEREQUEST', 2: 'AUTO_DRIVE_MODE_ALLOWREMOTETAKEOVER', 3: 'AUTO_DRIVE_MODE_AUTOEMERGENCYSTOP'}, 'is_signed_var': False, 'len': 8, 'name': 'auto_drive_mode', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void AutoMessage::set_p_auto_drive_mode(int auto_drive_mode) {
  int x = auto_drive_mode;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 0, 8);
  data[0] += to_set.return_byte_t();
  
}

// config detail: {'bit': 56, 'description': '自动驾驶心跳包', 'is_signed_var': False, 'len': 8, 'name': 'auto_heartbeat', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
void AutoMessage::set_p_auto_heartbeat(int auto_heartbeat) {
  // auto_heartbeat = ProtocolData::BoundedValue(0, 255, auto_heartbeat);
  int x = auto_heartbeat;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 0, 8);
  data[7] += to_set.return_byte_t();
  
}


