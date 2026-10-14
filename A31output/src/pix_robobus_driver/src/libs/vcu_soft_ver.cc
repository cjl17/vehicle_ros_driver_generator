#include <libs/vcu_soft_ver.hpp>


VcuSoftVer::VcuSoftVer() {}

void VcuSoftVer::update_bytes(uint8_t bytes_data[8])
{
  for(uint i=0;i<8;i++)
  {
    bytes[i] = bytes_data[i];
  }
}

void VcuSoftVer::Parse() {
  vehicle_parameter_ = vehicleparameter();
  reserve10_f2_ = reserve10f2();
  version_year_ = versionyear();
  version_month_ = versionmonth();
  version_day_ = versionday();
  version_main_ = versionmain();
  version_sub_ = versionsub();
  version_patch_ = versionpatch();
}


// config detail: {'bit': 0, 'description': '车辆硬件配置参数', 'is_signed_var': False, 'len': 8, 'name': 'vehicle_parameter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int VcuSoftVer::vehicleparameter() {
  Byte t0(*(bytes + 0));
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

// config detail: {'bit': 8, 'description': '预留', 'is_signed_var': False, 'len': 8, 'name': 'reserve10_f2', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int VcuSoftVer::reserve10f2() {
  Byte t0(*(bytes + 1));
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

// config detail: {'bit': 16, 'description': '年', 'is_signed_var': False, 'len': 8, 'name': 'version_year', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int VcuSoftVer::versionyear() {
  Byte t0(*(bytes + 2));
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

// config detail: {'bit': 24, 'description': '月', 'is_signed_var': False, 'len': 8, 'name': 'version_month', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int VcuSoftVer::versionmonth() {
  Byte t0(*(bytes + 3));
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

// config detail: {'bit': 32, 'description': '日', 'is_signed_var': False, 'len': 8, 'name': 'version_day', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int VcuSoftVer::versionday() {
  Byte t0(*(bytes + 4));
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

// config detail: {'bit': 40, 'description': '主版本号', 'is_signed_var': False, 'len': 8, 'name': 'version_main', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int VcuSoftVer::versionmain() {
  Byte t0(*(bytes + 5));
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

// config detail: {'bit': 48, 'description': '次版本号', 'is_signed_var': False, 'len': 8, 'name': 'version_sub', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int VcuSoftVer::versionsub() {
  Byte t0(*(bytes + 6));
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

// config detail: {'bit': 56, 'description': '修订号', 'is_signed_var': False, 'len': 8, 'name': 'version_patch', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
int VcuSoftVer::versionpatch() {
  Byte t0(*(bytes + 7));
  int32_t x = t0.get_byte(0, 8);

  int ret = x;
  return ret;
}

