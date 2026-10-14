#include <libs/va_chassis_odo_fb.hpp>


VaChassisOdoFb::VaChassisOdoFb() {}

void VaChassisOdoFb::update_bytes(uint8_t bytes_data[8])
{
  for(uint i=0;i<8;i++)
  {
    bytes[i] = bytes_data[i];
  }
}

void VaChassisOdoFb::Parse() {
  vcu_vehicle_odo_ = vcuvehicleodo();
  vcu_vehicle_trip_ = vcuvehicletrip();
  vcu_vehicle_remaining_range_ = vcuvehicleremainingrange();
}


// config detail: {'bit': 0, 'description': '总里程', 'is_signed_var': False, 'len': 24, 'name': 'vcu_vehicle_odo', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|16777215]', 'physical_unit': 'km', 'precision': 1.0, 'type': 'int'}
int VaChassisOdoFb::vcuvehicleodo() {
  Byte t0(*(bytes + 2));
  int32_t x = t0.get_byte(0, 8);

  Byte t1(*(bytes + 1));
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  Byte t2(*(bytes + 0));
  t = t2.get_byte(0, 8);
  x <<= 8;
  x |= t;

  int ret = x;
  return ret;
}

// config detail: {'bit': 24, 'description': '单次里程(每次下电清零)', 'is_signed_var': False, 'len': 24, 'name': 'vcu_vehicle_trip', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|167772.15]', 'physical_unit': 'km', 'precision': 0.01, 'type': 'double'}
double VaChassisOdoFb::vcuvehicletrip() {
  Byte t0(*(bytes + 5));
  int32_t x = t0.get_byte(0, 8);

  Byte t1(*(bytes + 4));
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  Byte t2(*(bytes + 3));
  t = t2.get_byte(0, 8);
  x <<= 8;
  x |= t;

  double ret = x * 0.010000;
  return ret;
}

// config detail: {'bit': 48, 'description': '剩余里程估计(预留)', 'is_signed_var': False, 'len': 16, 'name': 'vcu_vehicle_remaining_range', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1000]', 'physical_unit': 'km', 'precision': 1.0, 'type': 'int'}
int VaChassisOdoFb::vcuvehicleremainingrange() {
  Byte t0(*(bytes + 7));
  int32_t x = t0.get_byte(0, 8);

  Byte t1(*(bytes + 6));
  int32_t t = t1.get_byte(0, 8);
  x <<= 8;
  x |= t;

  int ret = x;
  return ret;
}

