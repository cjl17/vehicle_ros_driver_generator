std_msgs/Header header 
# 驱动使能状态 [] [0|1]
int8 vcu_chassis_driver_en_sta 
# 驱动控制越界提醒 [] [0|1]
int8 vcu_chassis_diver_slopover 
# 驱动模式反馈 [] [0|3]
int8 vcu_chassis_driver_mode_sta 
# 档位状态 [] [0|3]
int8 vcu_chassis_gear_fb 
# 四驱两驱状态反馈 [] [0|2]
int8 vcu_chassis4_wd_mode_fb 
# 车速实际反馈 [m/s] [-50|50]
float32 vcu_chassis_speed_fb 
# 油门请求值反馈 [%] [0|100]
float32 vcu_chassis_throttle_pald_fb 
# 自驾模式下操作员请求了油门踏板(预留) [] [0|1]
int8 vcu_chassis_throttle_pedal_req_fb 
# 车辆加速度 [m/s2] [-20|20]
float32 vcu_chassis_acceleration_fb 
# VCU循环计数 [] [0|15]
int32 vcu_drive_life 
# 驱动控制信号的Checksum或者 life sig校验情况 [] [0|1]
int8 vcu_drive_check_sta 
