#pragma once

#include <libs/Byte.hpp>

class VcuSoftVer {
public:
  static const uint32_t ID = 0x10F;
  VcuSoftVer();
  void Parse();
  void update_bytes(uint8_t bytes_data[8]);
  // singal
  int vehicle_parameter_;
  int reserve10_f2_;
  int version_year_;
  int version_month_;
  int version_day_;
  int version_main_;
  int version_sub_;
  int version_patch_;
  

private:
  uint8_t bytes[8];
  
  // config detail: {'bit': 0, 'description': '车辆硬件配置参数', 'is_signed_var': False, 'len': 8, 'name': 'vehicle_parameter', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  int vehicleparameter();

  // config detail: {'bit': 8, 'description': '预留', 'is_signed_var': False, 'len': 8, 'name': 'reserve10_f2', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  int reserve10f2();

  // config detail: {'bit': 16, 'description': '年', 'is_signed_var': False, 'len': 8, 'name': 'version_year', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  int versionyear();

  // config detail: {'bit': 24, 'description': '月', 'is_signed_var': False, 'len': 8, 'name': 'version_month', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  int versionmonth();

  // config detail: {'bit': 32, 'description': '日', 'is_signed_var': False, 'len': 8, 'name': 'version_day', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  int versionday();

  // config detail: {'bit': 40, 'description': '主版本号', 'is_signed_var': False, 'len': 8, 'name': 'version_main', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  int versionmain();

  // config detail: {'bit': 48, 'description': '次版本号', 'is_signed_var': False, 'len': 8, 'name': 'version_sub', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  int versionsub();

  // config detail: {'bit': 56, 'description': '修订号', 'is_signed_var': False, 'len': 8, 'name': 'version_patch', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|255]', 'physical_unit': '', 'precision': 1.0, 'type': 'int'}
  int versionpatch();
};



