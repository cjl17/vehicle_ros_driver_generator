#pragma once

#include <libs/Byte.hpp>

class VinResp3 {
public:
  static const uint32_t ID = 0x516;
  VinResp3();
  void Parse();
  void update_bytes(uint8_t bytes_data[8]);
  // singal
  int vin_16_;
  

private:
  uint8_t bytes[8];
  
  // config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'vin_16', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  int vin16();
};



