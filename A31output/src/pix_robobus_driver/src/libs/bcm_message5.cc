#include <libs/bcm_message5.hpp>


BcmMessage5::BcmMessage5() {}

void BcmMessage5::update_bytes(uint8_t bytes_data[8])
{
  for(uint i=0;i<8;i++)
  {
    bytes[i] = bytes_data[i];
  }
}

void BcmMessage5::Parse() {
  ad_volt_vin1_ = advoltvin1();
  ad_volt_vin2_ = advoltvin2();
}


// config detail: {'bit': 32, 'description': '电压型传感器输入口1（烟雾传感器）', 'enum': {0: 'AD_VOLT_VIN1_NORMAL', 1: 'AD_VOLT_VIN1_ABNORMAL'}, 'is_signed_var': False, 'len': 8, 'name': 'ad_volt_vin1', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int BcmMessage5::advoltvin1() {
  Byte t0(*(bytes + 4));
  int32_t x = t0.get_byte(0, 8);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 40, 'description': '电压型传感器输入口2（CO2传感器）', 'enum': {0: 'AD_VOLT_VIN2_NORMAL', 1: 'AD_VOLT_VIN2_ABNORMAL'}, 'is_signed_var': False, 'len': 8, 'name': 'ad_volt_vin2', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int BcmMessage5::advoltvin2() {
  Byte t0(*(bytes + 5));
  int32_t x = t0.get_byte(0, 8);

  int ret =  static_cast<int>(x);
  return ret;
}

