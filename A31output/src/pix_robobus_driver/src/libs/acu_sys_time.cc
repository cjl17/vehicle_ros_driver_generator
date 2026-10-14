#include <libs/acu_sys_time.hpp>

int32_t AcuSysTime::ID = 0x52B;

// public
AcuSysTime::AcuSysTime() { Reset(); }

void AcuSysTime::UpdateData(int sys_time_year, int sys_time_month, int sys_time_day, int sys_time_hour, int sys_time_minute, int sys_time_second) {
  set_p_sys_time_year(sys_time_year);
  set_p_sys_time_month(sys_time_month);
  set_p_sys_time_day(sys_time_day);
  set_p_sys_time_hour(sys_time_hour);
  set_p_sys_time_minute(sys_time_minute);
  set_p_sys_time_second(sys_time_second);
}

void AcuSysTime::Reset() {
  // TODO(All) :  you should check this manually
  for(uint8_t i=0;i<8;i++)
  {
    data[i] = 0;
  }
}

uint8_t * AcuSysTime::get_data()
{
  return data;
}



// config detail: {'bit': 0, 'description': '当前年份', 'is_signed_var': False, 'len': 8, 'name': 'sys_time_year', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|153]', 'physical_unit': 'Y', 'precision': 1.0, 'type': 'int'}
void AcuSysTime::set_p_sys_time_year(int sys_time_year) {
  // sys_time_year = ProtocolData::BoundedValue(0, 153, sys_time_year);
  int x = sys_time_year;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 0, 8);
  data[0] += to_set.return_byte_t();
  
}

// config detail: {'bit': 8, 'description': '月', 'is_signed_var': False, 'len': 8, 'name': 'sys_time_month', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|18]', 'physical_unit': 'M', 'precision': 1.0, 'type': 'int'}
void AcuSysTime::set_p_sys_time_month(int sys_time_month) {
  // sys_time_month = ProtocolData::BoundedValue(0, 18, sys_time_month);
  int x = sys_time_month;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 0, 8);
  data[1] += to_set.return_byte_t();
  
}

// config detail: {'bit': 16, 'description': '日', 'is_signed_var': False, 'len': 8, 'name': 'sys_time_day', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|49]', 'physical_unit': 'D', 'precision': 1.0, 'type': 'int'}
void AcuSysTime::set_p_sys_time_day(int sys_time_day) {
  // sys_time_day = ProtocolData::BoundedValue(0, 49, sys_time_day);
  int x = sys_time_day;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 0, 8);
  data[2] += to_set.return_byte_t();
  
}

// config detail: {'bit': 24, 'description': '时', 'is_signed_var': False, 'len': 8, 'name': 'sys_time_hour', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|36]', 'physical_unit': 'h', 'precision': 1.0, 'type': 'int'}
void AcuSysTime::set_p_sys_time_hour(int sys_time_hour) {
  // sys_time_hour = ProtocolData::BoundedValue(0, 36, sys_time_hour);
  int x = sys_time_hour;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 0, 8);
  data[3] += to_set.return_byte_t();
  
}

// config detail: {'bit': 32, 'description': '分', 'is_signed_var': False, 'len': 8, 'name': 'sys_time_minute', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|96]', 'physical_unit': 'm', 'precision': 1.0, 'type': 'int'}
void AcuSysTime::set_p_sys_time_minute(int sys_time_minute) {
  // sys_time_minute = ProtocolData::BoundedValue(0, 96, sys_time_minute);
  int x = sys_time_minute;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 0, 8);
  data[4] += to_set.return_byte_t();
  
}

// config detail: {'bit': 40, 'description': '秒', 'is_signed_var': True, 'len': 8, 'name': 'sys_time_second', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|96]', 'physical_unit': 's', 'precision': 1.0, 'type': 'int'}
void AcuSysTime::set_p_sys_time_second(int sys_time_second) {
  // sys_time_second = ProtocolData::BoundedValue(0, 96, sys_time_second);
  int x = sys_time_second;
  uint8_t a = 0;

  Byte to_set(a);
  to_set.set_value(x, 0, 8);
  data[5] += to_set.return_byte_t();
  
}


