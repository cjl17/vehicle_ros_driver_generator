#pragma once

#include <libs/Byte.hpp>

class BcmMessage4 {
public:
  static const uint32_t ID = 0x5F4;
  BcmMessage4();
  void Parse();
  void update_bytes(uint8_t bytes_data[8]);
  // singal
  int ltemp_;
  int ntemp_;
  int safe_belt_sta1_;
  int safe_belt_sta2_;
  int safe_belt_sta3_;
  int safe_belt_sta4_;
  int safe_belt_sta5_;
  int safe_belt_sta6_;
  int seat_sta1_;
  int seat_sta2_;
  int seat_sta3_;
  int seat_sta4_;
  int seat_sta5_;
  int seat_sta6_;
  

private:
  uint8_t bytes[8];
  
  // config detail: {'bit': 8, 'description': '交流充L线温度', 'is_signed_var': False, 'len': 8, 'name': 'ltemp', 'offset': -40.0, 'order': 'intel', 'physical_range': '[-40|215]', 'physical_unit': '℃', 'precision': 1.0, 'type': 'int'}
  int ltemp();

  // config detail: {'bit': 16, 'description': '交流充N线温度', 'is_signed_var': False, 'len': 8, 'name': 'ntemp', 'offset': -40.0, 'order': 'intel', 'physical_range': '[-40|215]', 'physical_unit': '℃', 'precision': 1.0, 'type': 'int'}
  int ntemp();

  // config detail: {'bit': 24, 'description': '前左安全带状态', 'enum': {0: 'SAFE_BELT_STA1_FASTENED', 1: 'SAFE_BELT_STA1_UNFASTENED'}, 'is_signed_var': False, 'len': 1, 'name': 'safe_belt_sta1', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int safebeltsta1();

  // config detail: {'bit': 25, 'description': '前中安全带状态', 'enum': {0: 'SAFE_BELT_STA2_FASTENED', 1: 'SAFE_BELT_STA2_UNFASTENED'}, 'is_signed_var': False, 'len': 1, 'name': 'safe_belt_sta2', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int safebeltsta2();

  // config detail: {'bit': 26, 'description': '前右安全带状态', 'enum': {0: 'SAFE_BELT_STA3_FASTENED', 1: 'SAFE_BELT_STA3_UNFASTENED'}, 'is_signed_var': False, 'len': 1, 'name': 'safe_belt_sta3', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int safebeltsta3();

  // config detail: {'bit': 27, 'description': '后左安全带状态', 'enum': {0: 'SAFE_BELT_STA4_FASTENED', 1: 'SAFE_BELT_STA4_UNFASTENED'}, 'is_signed_var': False, 'len': 1, 'name': 'safe_belt_sta4', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int safebeltsta4();

  // config detail: {'bit': 28, 'description': '后中安全带状态', 'enum': {0: 'SAFE_BELT_STA5_FASTENED', 1: 'SAFE_BELT_STA5_UNFASTENED'}, 'is_signed_var': False, 'len': 1, 'name': 'safe_belt_sta5', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int safebeltsta5();

  // config detail: {'bit': 29, 'description': '后右安全带状态', 'enum': {0: 'SAFE_BELT_STA6_FASTENED', 1: 'SAFE_BELT_STA6_UNFASTENED'}, 'is_signed_var': False, 'len': 1, 'name': 'safe_belt_sta6', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int safebeltsta6();

  // config detail: {'bit': 30, 'description': '前左座椅状态', 'enum': {0: 'SEAT_STA1_VACANT', 1: 'SEAT_STA1_SOMEONE'}, 'is_signed_var': False, 'len': 1, 'name': 'seat_sta1', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int seatsta1();

  // config detail: {'bit': 31, 'description': '前中座椅状态', 'enum': {0: 'SEAT_STA2_VACANT', 1: 'SEAT_STA2_SOMEONE'}, 'is_signed_var': False, 'len': 1, 'name': 'seat_sta2', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int seatsta2();

  // config detail: {'bit': 32, 'description': '前右座椅状态', 'enum': {0: 'SEAT_STA3_VACANT', 1: 'SEAT_STA3_SOMEONE'}, 'is_signed_var': False, 'len': 1, 'name': 'seat_sta3', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int seatsta3();

  // config detail: {'bit': 33, 'description': '后左座椅状态', 'enum': {0: 'SEAT_STA4_VACANT', 1: 'SEAT_STA4_SOMEONE'}, 'is_signed_var': False, 'len': 1, 'name': 'seat_sta4', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int seatsta4();

  // config detail: {'bit': 34, 'description': '后中座椅状态', 'enum': {0: 'SEAT_STA5_VACANT', 1: 'SEAT_STA5_SOMEONE'}, 'is_signed_var': False, 'len': 1, 'name': 'seat_sta5', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int seatsta5();

  // config detail: {'bit': 35, 'description': '后右座椅状态', 'enum': {0: 'SEAT_STA6_VACANT', 1: 'SEAT_STA6_SOMEONE'}, 'is_signed_var': False, 'len': 1, 'name': 'seat_sta6', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int seatsta6();
};



