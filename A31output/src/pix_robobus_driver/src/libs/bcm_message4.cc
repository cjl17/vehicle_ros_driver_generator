#include <libs/bcm_message4.hpp>


BcmMessage4::BcmMessage4() {}

void BcmMessage4::update_bytes(uint8_t bytes_data[8])
{
  for(uint i=0;i<8;i++)
  {
    bytes[i] = bytes_data[i];
  }
}

void BcmMessage4::Parse() {
  ltemp_ = ltemp();
  ntemp_ = ntemp();
  safe_belt_sta1_ = safebeltsta1();
  safe_belt_sta2_ = safebeltsta2();
  safe_belt_sta3_ = safebeltsta3();
  safe_belt_sta4_ = safebeltsta4();
  safe_belt_sta5_ = safebeltsta5();
  safe_belt_sta6_ = safebeltsta6();
  seat_sta1_ = seatsta1();
  seat_sta2_ = seatsta2();
  seat_sta3_ = seatsta3();
  seat_sta4_ = seatsta4();
  seat_sta5_ = seatsta5();
  seat_sta6_ = seatsta6();
}


// config detail: {'bit': 8, 'description': '交流充L线温度', 'is_signed_var': False, 'len': 8, 'name': 'ltemp', 'offset': -40.0, 'order': 'intel', 'physical_range': '[-40|215]', 'physical_unit': '℃', 'precision': 1.0, 'type': 'int'}
int BcmMessage4::ltemp() {
  Byte t0(*(bytes + 1));
  int32_t x = t0.get_byte(0, 8);

  int ret = x + -40.000000;
  return ret;
}

// config detail: {'bit': 16, 'description': '交流充N线温度', 'is_signed_var': False, 'len': 8, 'name': 'ntemp', 'offset': -40.0, 'order': 'intel', 'physical_range': '[-40|215]', 'physical_unit': '℃', 'precision': 1.0, 'type': 'int'}
int BcmMessage4::ntemp() {
  Byte t0(*(bytes + 2));
  int32_t x = t0.get_byte(0, 8);

  int ret = x + -40.000000;
  return ret;
}

// config detail: {'bit': 24, 'description': '前左安全带状态', 'enum': {0: 'SAFE_BELT_STA1_FASTENED', 1: 'SAFE_BELT_STA1_UNFASTENED'}, 'is_signed_var': False, 'len': 1, 'name': 'safe_belt_sta1', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int BcmMessage4::safebeltsta1() {
  Byte t0(*(bytes + 3));
  int32_t x = t0.get_byte(0, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 25, 'description': '前中安全带状态', 'enum': {0: 'SAFE_BELT_STA2_FASTENED', 1: 'SAFE_BELT_STA2_UNFASTENED'}, 'is_signed_var': False, 'len': 1, 'name': 'safe_belt_sta2', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int BcmMessage4::safebeltsta2() {
  Byte t0(*(bytes + 3));
  int32_t x = t0.get_byte(1, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 26, 'description': '前右安全带状态', 'enum': {0: 'SAFE_BELT_STA3_FASTENED', 1: 'SAFE_BELT_STA3_UNFASTENED'}, 'is_signed_var': False, 'len': 1, 'name': 'safe_belt_sta3', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int BcmMessage4::safebeltsta3() {
  Byte t0(*(bytes + 3));
  int32_t x = t0.get_byte(2, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 27, 'description': '后左安全带状态', 'enum': {0: 'SAFE_BELT_STA4_FASTENED', 1: 'SAFE_BELT_STA4_UNFASTENED'}, 'is_signed_var': False, 'len': 1, 'name': 'safe_belt_sta4', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int BcmMessage4::safebeltsta4() {
  Byte t0(*(bytes + 3));
  int32_t x = t0.get_byte(3, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 28, 'description': '后中安全带状态', 'enum': {0: 'SAFE_BELT_STA5_FASTENED', 1: 'SAFE_BELT_STA5_UNFASTENED'}, 'is_signed_var': False, 'len': 1, 'name': 'safe_belt_sta5', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int BcmMessage4::safebeltsta5() {
  Byte t0(*(bytes + 3));
  int32_t x = t0.get_byte(4, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 29, 'description': '后右安全带状态', 'enum': {0: 'SAFE_BELT_STA6_FASTENED', 1: 'SAFE_BELT_STA6_UNFASTENED'}, 'is_signed_var': False, 'len': 1, 'name': 'safe_belt_sta6', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int BcmMessage4::safebeltsta6() {
  Byte t0(*(bytes + 3));
  int32_t x = t0.get_byte(5, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 30, 'description': '前左座椅状态', 'enum': {0: 'SEAT_STA1_VACANT', 1: 'SEAT_STA1_SOMEONE'}, 'is_signed_var': False, 'len': 1, 'name': 'seat_sta1', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int BcmMessage4::seatsta1() {
  Byte t0(*(bytes + 3));
  int32_t x = t0.get_byte(6, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 31, 'description': '前中座椅状态', 'enum': {0: 'SEAT_STA2_VACANT', 1: 'SEAT_STA2_SOMEONE'}, 'is_signed_var': False, 'len': 1, 'name': 'seat_sta2', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int BcmMessage4::seatsta2() {
  Byte t0(*(bytes + 3));
  int32_t x = t0.get_byte(7, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 32, 'description': '前右座椅状态', 'enum': {0: 'SEAT_STA3_VACANT', 1: 'SEAT_STA3_SOMEONE'}, 'is_signed_var': False, 'len': 1, 'name': 'seat_sta3', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int BcmMessage4::seatsta3() {
  Byte t0(*(bytes + 4));
  int32_t x = t0.get_byte(0, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 33, 'description': '后左座椅状态', 'enum': {0: 'SEAT_STA4_VACANT', 1: 'SEAT_STA4_SOMEONE'}, 'is_signed_var': False, 'len': 1, 'name': 'seat_sta4', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int BcmMessage4::seatsta4() {
  Byte t0(*(bytes + 4));
  int32_t x = t0.get_byte(1, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 34, 'description': '后中座椅状态', 'enum': {0: 'SEAT_STA5_VACANT', 1: 'SEAT_STA5_SOMEONE'}, 'is_signed_var': False, 'len': 1, 'name': 'seat_sta5', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int BcmMessage4::seatsta5() {
  Byte t0(*(bytes + 4));
  int32_t x = t0.get_byte(2, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 35, 'description': '后右座椅状态', 'enum': {0: 'SEAT_STA6_VACANT', 1: 'SEAT_STA6_SOMEONE'}, 'is_signed_var': False, 'len': 1, 'name': 'seat_sta6', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int BcmMessage4::seatsta6() {
  Byte t0(*(bytes + 4));
  int32_t x = t0.get_byte(3, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

