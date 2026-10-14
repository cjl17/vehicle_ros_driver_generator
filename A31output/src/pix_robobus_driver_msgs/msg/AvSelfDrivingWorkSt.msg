std_msgs/Header header 
# 域控1温度 [℃] [-40|215]
int32 acu_adcu1_sys_temp 
# 域控2温度 [℃] [-40|215]
int32 acu_adcu2_sys_temp 
# 自动驾驶系统启动状态(自动驾驶系统已启动，感知规划等有效) [] [0|1]
int8 acu_self_driving_run_st 
# 远程驾驶控制模式(是否处于远程驾驶状态) [] [0|1]
int8 acu_remote_control_mode 
# 自动驾驶标定模式设置(只有运行标定模式才需要发这个信号！！) [] [0|3]
int8 acu_calibration_mode 
