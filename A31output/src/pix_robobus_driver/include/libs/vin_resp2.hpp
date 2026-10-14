#pragma once

#include <libs/Byte.hpp>

class VinResp2 {
public:
  static const uint32_t ID = 0x515;
  VinResp2();
  void Parse();
  void update_bytes(uint8_t bytes_data[8]);
  // singal
  int vin_08_;
  int vin_09_;
  int vin_10_;
  int vin_11_;
  int vin_12_;
  int vin_13_;
  int vin_14_;
  int vin_15_;
  

private:
  uint8_t bytes[8];
  
  // config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'vin_08', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  int vin08();

  // config detail: {'bit': 8, 'is_signed_var': False, 'len': 8, 'name': 'vin_09', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  int vin09();

  // config detail: {'bit': 16, 'is_signed_var': False, 'len': 8, 'name': 'vin_10', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  int vin10();

  // config detail: {'bit': 24, 'is_signed_var': False, 'len': 8, 'name': 'vin_11', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  int vin11();

  // config detail: {'bit': 32, 'is_signed_var': False, 'len': 8, 'name': 'vin_12', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  int vin12();

  // config detail: {'bit': 40, 'is_signed_var': False, 'len': 8, 'name': 'vin_13', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  int vin13();

  // config detail: {'bit': 48, 'is_signed_var': False, 'len': 8, 'name': 'vin_14', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  int vin14();

  // config detail: {'bit': 56, 'is_signed_var': False, 'len': 8, 'name': 'vin_15', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  int vin15();
};



