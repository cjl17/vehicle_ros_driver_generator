std_msgs/Header header 
# 车辆转向控制使能 [] [0|1]
int8 acu_chassis_steer_en_ctrl 
# 转向模式控制 （车速低于5km/h或请求的转向小于15度才能切换） [] [0|4]
int8 acu_chassis_steer_mode_ctrl 
# 车辆转向控制（前） [deg] [-500|500]
int32 acu_chassis_steer_angle_target 
# 车辆转向控制（后） [deg] [-500|500]
int32 acu_chassis_steer_angle_rear_target 
# 车辆方向盘转角速度控制 [deg/s] [0|500]
float32 acu_chassis_steer_angle_speed_ctrl 
# 循环计数0~15 [] [0|15]
int32 acu_steer_life_sig 
# 校验sum=byte0 xor byte1 xor...byte6 [] [0|255]
int32 acu_check_sum132 
