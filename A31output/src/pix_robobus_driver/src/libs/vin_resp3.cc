#include <libs/vin_resp3.hpp>


VinResp3::VinResp3() {}

void VinResp3::update_bytes(uint8_t bytes_data[8])
{
  for(uint i=0;i<8;i++)
  {
    bytes[i] = bytes_data[i];
  }
}

void VinResp3::Parse() {
  vin_16_ = vin16();
}


// config detail: {'bit': 0, 'is_signed_var': False, 'len': 8, 'name': 'vin_16', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int VinResp3::vin16() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

