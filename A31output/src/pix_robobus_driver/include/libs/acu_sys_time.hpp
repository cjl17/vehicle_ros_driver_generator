#pragma once
#include <libs/Byte.hpp>

class AcuSysTime {
public:
	static  int32_t ID;

	AcuSysTime();
	void UpdateData(int sys_time_year, int sys_time_month, int sys_time_day, int sys_time_hour, int sys_time_minute, int sys_time_second);
	void Reset();
	uint8_t *get_data();


private:
	
  // config detail: {'bit': 0, 'description': '当前年份', 'is_signed_var': False, 'len': 8, 'name': 'sys_time_year', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|153]', 'physical_unit': 'Y', 'precision': 1.0, 'type': 'int'}
  void set_p_sys_time_year(int sys_time_year);

  // config detail: {'bit': 8, 'description': '月', 'is_signed_var': False, 'len': 8, 'name': 'sys_time_month', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|18]', 'physical_unit': 'M', 'precision': 1.0, 'type': 'int'}
  void set_p_sys_time_month(int sys_time_month);

  // config detail: {'bit': 16, 'description': '日', 'is_signed_var': False, 'len': 8, 'name': 'sys_time_day', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|49]', 'physical_unit': 'D', 'precision': 1.0, 'type': 'int'}
  void set_p_sys_time_day(int sys_time_day);

  // config detail: {'bit': 24, 'description': '时', 'is_signed_var': False, 'len': 8, 'name': 'sys_time_hour', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|36]', 'physical_unit': 'h', 'precision': 1.0, 'type': 'int'}
  void set_p_sys_time_hour(int sys_time_hour);

  // config detail: {'bit': 32, 'description': '分', 'is_signed_var': False, 'len': 8, 'name': 'sys_time_minute', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|96]', 'physical_unit': 'm', 'precision': 1.0, 'type': 'int'}
  void set_p_sys_time_minute(int sys_time_minute);

  // config detail: {'bit': 40, 'description': '秒', 'is_signed_var': True, 'len': 8, 'name': 'sys_time_second', 'offset': 0.0, 'order': 'intel', 'physical_range': '[0|96]', 'physical_unit': 's', 'precision': 1.0, 'type': 'int'}
  void set_p_sys_time_second(int sys_time_second);

private:
	uint8_t data[8];
};



