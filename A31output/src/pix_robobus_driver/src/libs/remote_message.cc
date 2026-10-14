#include <libs/remote_message.hpp>

int32_t RemoteMessage::ID = 0x3B0;

// public
RemoteMessage::RemoteMessage() { Reset(); }

void RemoteMessage::UpdateData(int remote_drive_mode, int remote_heartbeat) {
  set_p_remote_drive_mode(remote_drive_mode);
  set_p_remote_heartbeat(remote_heartbeat);
}

void RemoteMessage::Reset() {
  // TODO(All) :  you should check this manually
  for(uint8_t i=0;i<8;i++)
  {
    data[i] = 0;
  }
}

uint8_t * RemoteMessage::get_data()
{
  return data;
}



// config detail: {'bit': 0, 'description': '远控状态', 'enum': {0: 'REMOTE_DRIVE_MODE_NOREQUEST', 1: 'REMOTE_DRIVE_MODE_REMOTEREQUESTTAKEOVER', 2: 'REMOTE_DRIVE_MODE_REMOTETAKEOVER', 3: 'REMOTE_DRIVE_MODE_REMOTEEMENGENCYSTOP'}, 'is_signed_var': False, 'len': 8, 'name': 'remote_drive_mode', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
void RemoteMessage::set_p_remote_drive_mode(int remote_drive_mode) {
  int x = remote_drive_mode;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 0, 8);
  data[0] += to_set.return_byte_t();
  
}

// config detail: {'bit': 56, 'description': '远控心跳包', 'is_signed_var': False, 'len': 8, 'name': 'remote_heartbeat', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
void RemoteMessage::set_p_remote_heartbeat(int remote_heartbeat) {
  // remote_heartbeat = ProtocolData::BoundedValue(0, 255, remote_heartbeat);
  int x = remote_heartbeat;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 0, 8);
  data[7] += to_set.return_byte_t();
  
}


