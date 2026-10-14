#pragma once

#include <libs/Byte.hpp>

class VaChassisOdoFb {
public:
  static const uint32_t ID = 0x53A;
  VaChassisOdoFb();
  void Parse();
  void update_bytes(uint8_t bytes_data[8]);
  // singal
  int vcu_vehicle_odo_;
  double vcu_vehicle_trip_;
  int vcu_vehicle_remaining_range_;
  

private:
  uint8_t bytes[8];
  
  // config detail: {'bit': 0, 'description': '总里程', 'is_signed_var': False, 'len': 24, 'name': 'vcu_vehicle_odo', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|16777215]', 'physical_unit': 'km', 'precision': 1.0, 'type': 'int'}
  int vcuvehicleodo();

  // config detail: {'bit': 24, 'description': '单次里程(每次下电清零)', 'is_signed_var': False, 'len': 24, 'name': 'vcu_vehicle_trip', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|167772.15]', 'physical_unit': 'km', 'precision': 0.01, 'type': 'double'}
  double vcuvehicletrip();

  // config detail: {'bit': 48, 'description': '剩余里程估计(预留)', 'is_signed_var': False, 'len': 16, 'name': 'vcu_vehicle_remaining_range', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|1000]', 'physical_unit': 'km', 'precision': 1.0, 'type': 'int'}
  int vcuvehicleremainingrange();
};



