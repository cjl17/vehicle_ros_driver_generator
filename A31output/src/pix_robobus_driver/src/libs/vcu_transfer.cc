#include <libs/vcu_transfer.hpp>


VcuTransfer::VcuTransfer() {}

void VcuTransfer::update_bytes(uint8_t bytes_data[8])
{
  for(uint i=0;i<8;i++)
  {
    bytes[i] = bytes_data[i];
  }
}

void VcuTransfer::Parse() {
  vcu_pad_auto_start_ = vcupadautostart();
  ac_out_temp_ = acouttemp();
  ac_in_temp_ = acintemp();
}


// config detail: {'bit': 4, 'description': 'PAD自动驾驶启动按钮', 'enum': {0: 'VCU_PAD_AUTO_START_INVALID', 1: 'VCU_PAD_AUTO_START_START'}, 'is_signed_var': False, 'len': 1, 'name': 'vcu_pad_auto_start', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1]', 'physical_unit': '', 'precision': 1.0, 'type': 'enum'}
int VcuTransfer::vcupadautostart() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(4, 1);

  int ret =  static_cast<int>(x);
  return ret;
}

// config detail: {'bit': 40, 'description': '车外温度', 'is_signed_var': True, 'len': 8, 'name': 'ac_out_temp', 'offset': -40.0, 'order': 'intel', 'physical_range': '[-40|215]', 'physical_unit': '℃', 'precision': 1.0, 'type': 'int'}
int VcuTransfer::acouttemp() {
  Byte t0(*(bytes + 5));
  int32_t x = t0.get_byte(0, 8);

  x <<= 24;
  x >>= 24;

  int ret = x + -40.000000;
  return ret;
}

// config detail: {'bit': 48, 'description': '车内温度', 'is_signed_var': True, 'len': 8, 'name': 'ac_in_temp', 'offset': -40.0, 'order': 'intel', 'physical_range': '[-40|215]', 'physical_unit': '℃', 'precision': 1.0, 'type': 'int'}
int VcuTransfer::acintemp() {
  Byte t0(*(bytes + 6));
  int32_t x = t0.get_byte(0, 8);

  x <<= 24;
  x >>= 24;

  int ret = x + -40.000000;
  return ret;
}

