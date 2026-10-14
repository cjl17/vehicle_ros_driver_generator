std_msgs/Header header 
# 制动使能状态 [] [0|1]
int8 vcu_chassis_brake_en_sta 
# 制动灯状态反馈 [] [0|1]
int8 vcu_vehicle_brake_lamp_fb 
# 驻车状态 [] [0|3]
int8 vcu_chassis_epb_fb 
# 制动控制报文中断提醒 [] [0|1]
int8 vcu_chassis_brake_communication_lost 
# 制动踏板值反馈 [%] [0|100]
float32 vcu_chassis_brake_padl_fb 
# 自驾状态下用户请求了制动 [] [0|1]
int8 vcu_brake_pedal_req_fb 
# AEB开启状态反馈（预留） [] [0|1]
int8 vcu_aeb_en_sta_fb 
# AEB触发状态反馈（预留） [] [0|1]
int8 vcu_aeb_trigger_sta_fb 
# 制动压力反馈 [bar] [0|100]
int32 vcu_chassis_brake_pressure_fb 
# VCU循环计数 [] [0|15]
int32 vcu_brake_life 
# 制动控制信号的Checksum或者 life sig校验情况 [] [0|1]
int8 vcu_brake_check_sta 
# 当前能量回收状态反馈 [] [0|15]
bool vcu_energy_recovery_sta_fb 
# 当前能量回收扭矩反馈 [Nm] [0|1023]
int32 vcu_energy_recovery_tor_fb 
