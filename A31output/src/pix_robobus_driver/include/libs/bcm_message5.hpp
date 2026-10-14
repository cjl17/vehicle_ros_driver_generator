#pragma once

#include <libs/Byte.hpp>

class BcmMessage5 {
public:
  static const uint32_t ID = 0x5F5;
  BcmMessage5();
  void Parse();
  void update_bytes(uint8_t bytes_data[8]);
  // singal
  int ad_volt_vin1_;
  int ad_volt_vin2_;
  

private:
  uint8_t bytes[8];
  
  // config detail: {'bit': 32, 'description': '电压型传感器输入口1（烟雾传感器）', 'enum': {0: 'AD_VOLT_VIN1_NORMAL', 1: 'AD_VOLT_VIN1_ABNORMAL'}, 'is_signed_var': False, 'len': 8, 'name': 'ad_volt_vin1', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int advoltvin1();

  // config detail: {'bit': 40, 'description': '电压型传感器输入口2（CO2传感器）', 'enum': {0: 'AD_VOLT_VIN2_NORMAL', 1: 'AD_VOLT_VIN2_ABNORMAL'}, 'is_signed_var': False, 'len': 8, 'name': 'ad_volt_vin2', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
  int advoltvin2();
};



