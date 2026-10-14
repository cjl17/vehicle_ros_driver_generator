#include <libs/dp_messgae4.hpp>


DpMessgae4::DpMessgae4() {}

void DpMessgae4::update_bytes(uint8_t bytes_data[8])
{
  for(uint i=0;i<8;i++)
  {
    bytes[i] = bytes_data[i];
  }
}

void DpMessgae4::Parse() {
  pdu_total_cur_ = pdutotalcur();
  dp_low_bat_vol_ = dplowbatvol();
  pdu_temp_ = pdutemp();
  auto_current1_ = autocurrent1();
  dp_error_code_ = dperrorcode();
  on_sta_ = onsta();
  auto_current2_ = autocurrent2();
}


// config detail: {'bit': 0, 'description': '配电盒总负载电流', 'is_signed_var': False, 'len': 8, 'name': 'pdu_total_cur', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'A', 'precision': 1.0, 'type': 'int'}
int DpMessgae4::pdutotalcur() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

// config detail: {'bit': 8, 'description': '低压电源电压', 'is_signed_var': False, 'len': 8, 'name': 'dp_low_bat_vol', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|127.5]', 'physical_unit': 'V', 'precision': 0.5, 'type': 'double'}
double DpMessgae4::dplowbatvol() {
  Byte t0(*(bytes + 1));
  int32_t x = t0.get_byte(0, 8);

  double ret = x * 0.500000;
  return ret;
}

// config detail: {'bit': 16, 'description': '配电盒工作温度', 'is_signed_var': False, 'len': 8, 'name': 'pdu_temp', 'offset': -40.0, 'order': 'intel', 'physical_range': '[-40|215]', 'physical_unit': '℃', 'precision': 1.0, 'type': 'int'}
int DpMessgae4::pdutemp() {
  Byte t0(*(bytes + 2));
  int32_t x = t0.get_byte(0, 8);

  int ret = x + -40.000000;
  return ret;
}

// config detail: {'bit': 24, 'description': '自动驾驶电流（T7）', 'is_signed_var': False, 'len': 8, 'name': 'auto_current1', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'A', 'precision': 1.0, 'type': 'int'}
int DpMessgae4::autocurrent1() {
  Byte t0(*(bytes + 3));
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

// config detail: {'bit': 32, 'description': 'DP故障代码', 'is_signed_var': False, 'len': 8, 'name': 'dp_error_code', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int DpMessgae4::dperrorcode() {
  Byte t0(*(bytes + 4));
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

// config detail: {'bit': 48, 'description': 'ON档电状态 （VCU指令与硬线是或逻辑）', 'is_signed_var': False, 'len': 8, 'name': 'on_sta', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int DpMessgae4::onsta() {
  Byte t0(*(bytes + 6));
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

// config detail: {'bit': 56, 'description': '自动驾驶电流（T2）', 'is_signed_var': False, 'len': 8, 'name': 'auto_current2', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': 'A', 'precision': 1.0, 'type': 'int'}
int DpMessgae4::autocurrent2() {
  Byte t0(*(bytes + 7));
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

