#pragma once

#include <libs/Byte.hpp>

class AcMessage2 {
public:
  static const uint32_t ID = 0x2FF;
  AcMessage2();
  void Parse();
  void update_bytes(uint8_t bytes_data[8]);
  // singal
  double reserve_;
  int fan_temp_;
  int ac_out_temp_;
  int ac_in_temp_;
  int ac_hardware_;
  int ac_software_;
  

private:
  uint8_t bytes[8];
  
  // config detail: {'bit': 8, 'description': '预留', 'is_signed_var': False, 'len': 16, 'name': 'reserve', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|65535]', 'physical_unit': 'V', 'precision': 0.01, 'type': 'double'}
  double reserve();

  // config detail: {'bit': 24, 'description': '蒸发风扇温度', 'is_signed_var': True, 'len': 8, 'name': 'fan_temp', 'offset': -40.0, 'order': 'intel', 'physical_range': '[-40|255]', 'physical_unit': '℃', 'precision': 1.0, 'type': 'int'}
  int fantemp();

  // config detail: {'bit': 32, 'description': '车外温度', 'is_signed_var': True, 'len': 8, 'name': 'ac_out_temp', 'offset': -40.0, 'order': 'intel', 'physical_range': '[-40|255]', 'physical_unit': '℃', 'precision': 1.0, 'type': 'int'}
  int acouttemp();

  // config detail: {'bit': 40, 'description': '车内温度', 'is_signed_var': True, 'len': 8, 'name': 'ac_in_temp', 'offset': -40.0, 'order': 'intel', 'physical_range': '[-40|255]', 'physical_unit': '℃', 'precision': 1.0, 'type': 'int'}
  int acintemp();

  // config detail: {'bit': 48, 'description': '空调硬件版本', 'is_signed_var': True, 'len': 8, 'name': 'ac_hardware', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  int achardware();

  // config detail: {'bit': 56, 'description': '空调软件版本', 'is_signed_var': True, 'len': 8, 'name': 'ac_software', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  int acsoftware();
};



