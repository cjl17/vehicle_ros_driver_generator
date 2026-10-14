#pragma once

#include <libs/Byte.hpp>

class DpMessgae4 {
public:
  static const uint32_t ID = 0x6F4;
  DpMessgae4();
  void Parse();
  void update_bytes(uint8_t bytes_data[8]);
  // singal
  int pdu_total_cur_;
  double dp_low_bat_vol_;
  int pdu_temp_;
  int auto_current1_;
  int dp_error_code_;
  int on_sta_;
  int auto_current2_;
  

private:
  uint8_t bytes[8];
  
  // config detail: {'bit': 0, 'description': '配电盒总负载电流', 'is_signed_var': False, 'len': 8, 'name': 'pdu_total_cur', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'A', 'precision': 1.0, 'type': 'int'}
  int pdutotalcur();

  // config detail: {'bit': 8, 'description': '低压电源电压', 'is_signed_var': False, 'len': 8, 'name': 'dp_low_bat_vol', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|127.5]', 'physical_unit': 'V', 'precision': 0.5, 'type': 'double'}
  double dplowbatvol();

  // config detail: {'bit': 16, 'description': '配电盒工作温度', 'is_signed_var': False, 'len': 8, 'name': 'pdu_temp', 'offset': -40.0, 'order': 'intel', 'physical_range': '[-40|215]', 'physical_unit': '℃', 'precision': 1.0, 'type': 'int'}
  int pdutemp();

  // config detail: {'bit': 24, 'description': '自动驾驶电流（T7）', 'is_signed_var': False, 'len': 8, 'name': 'auto_current1', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'A', 'precision': 1.0, 'type': 'int'}
  int autocurrent1();

  // config detail: {'bit': 32, 'description': 'DP故障代码', 'is_signed_var': False, 'len': 8, 'name': 'dp_error_code', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  int dperrorcode();

  // config detail: {'bit': 48, 'description': 'ON档电状态 （VCU指令与硬线是或逻辑）', 'is_signed_var': False, 'len': 8, 'name': 'on_sta', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  int onsta();

  // config detail: {'bit': 56, 'description': '自动驾驶电流（T2）', 'is_signed_var': False, 'len': 8, 'name': 'auto_current2', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'A', 'precision': 1.0, 'type': 'int'}
  int autocurrent2();
};



