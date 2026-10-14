#include <libs/ac_message2.hpp>


AcMessage2::AcMessage2() {}

void AcMessage2::update_bytes(uint8_t bytes_data[8])
{
  for(uint i=0;i<8;i++)
  {
    bytes[i] = bytes_data[i];
  }
}

void AcMessage2::Parse() {
  reserve_ = reserve();
  fan_temp_ = fantemp();
  ac_out_temp_ = acouttemp();
  ac_in_temp_ = acintemp();
  ac_hardware_ = achardware();
  ac_software_ = acsoftware();
}


// config detail: {'bit': 8, 'description': '预留', 'is_signed_var': False, 'len': 16, 'name': 'reserve', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|65535]', 'physical_unit': 'V', 'precision': 0.01, 'type': 'double'}
double AcMessage2::reserve() {
  Byte t0(*(bytes + 2));
  int32_t x = t0.get_byte(0, 8);

  Byte t1(*(bytes + 1));
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.010000;
  return ret;
}

// config detail: {'bit': 24, 'description': '蒸发风扇温度', 'is_signed_var': True, 'len': 8, 'name': 'fan_temp', 'offset': -40.0, 'order': 'intel', 'physical_range': '[-40|255]', 'physical_unit': '℃', 'precision': 1.0, 'type': 'int'}
int AcMessage2::fantemp() {
  Byte t0(*(bytes + 3));
  int32_t x = t0.get_byte(0, 8);

  x <<= 24;
  x >>= 24;

  int ret = x + -40.000000;
  return ret;
}

// config detail: {'bit': 32, 'description': '车外温度', 'is_signed_var': True, 'len': 8, 'name': 'ac_out_temp', 'offset': -40.0, 'order': 'intel', 'physical_range': '[-40|255]', 'physical_unit': '℃', 'precision': 1.0, 'type': 'int'}
int AcMessage2::acouttemp() {
  Byte t0(*(bytes + 4));
  int32_t x = t0.get_byte(0, 8);

  x <<= 24;
  x >>= 24;

  int ret = x + -40.000000;
  return ret;
}

// config detail: {'bit': 40, 'description': '车内温度', 'is_signed_var': True, 'len': 8, 'name': 'ac_in_temp', 'offset': -40.0, 'order': 'intel', 'physical_range': '[-40|255]', 'physical_unit': '℃', 'precision': 1.0, 'type': 'int'}
int AcMessage2::acintemp() {
  Byte t0(*(bytes + 5));
  int32_t x = t0.get_byte(0, 8);

  x <<= 24;
  x >>= 24;

  int ret = x + -40.000000;
  return ret;
}

// config detail: {'bit': 48, 'description': '空调硬件版本', 'is_signed_var': True, 'len': 8, 'name': 'ac_hardware', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int AcMessage2::achardware() {
  Byte t0(*(bytes + 6));
  int32_t x = t0.get_byte(0, 8);

  x <<= 24;
  x >>= 24;

  int ret = x;
  return ret;
}

// config detail: {'bit': 56, 'description': '空调软件版本', 'is_signed_var': True, 'len': 8, 'name': 'ac_software', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int AcMessage2::acsoftware() {
  Byte t0(*(bytes + 7));
  int32_t x = t0.get_byte(0, 8);

  x <<= 24;
  x >>= 24;

  int ret = x;
  return ret;
}

