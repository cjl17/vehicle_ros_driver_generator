#pragma once

#include <libs/Byte.hpp>

class VinResp1 {
public:
  static const uint32_t ID = 0x514;
  VinResp1();
  void Parse();
  void update_bytes(uint8_t bytes_data[8]);
  // singal
  int vin_00_;
  int vin_01_;
  int vin_02_;
  int vin_03_;
  int vin_04_;
  int vin_05_;
  int vin_06_;
  int vin_07_;
  

private:
  uint8_t bytes[8];
  
  // config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'vin_00', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  int vin00();

  // config detail: {'bit': 8, 'is_signed_var': False, 'len': 8, 'name': 'vin_01', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  int vin01();

  // config detail: {'bit': 16, 'is_signed_var': False, 'len': 8, 'name': 'vin_02', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  int vin02();

  // config detail: {'bit': 24, 'is_signed_var': False, 'len': 8, 'name': 'vin_03', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  int vin03();

  // config detail: {'bit': 32, 'is_signed_var': False, 'len': 8, 'name': 'vin_04', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  int vin04();

  // config detail: {'bit': 40, 'is_signed_var': False, 'len': 8, 'name': 'vin_05', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  int vin05();

  // config detail: {'bit': 48, 'is_signed_var': False, 'len': 8, 'name': 'vin_06', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  int vin06();

  // config detail: {'bit': 56, 'is_signed_var': False, 'len': 8, 'name': 'vin_07', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  int vin07();
};



