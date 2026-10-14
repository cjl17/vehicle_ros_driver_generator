std_msgs/Header header 
# 配电盒总负载电流 [A] [0|255]
int32 pdu_total_cur 
# 低压电源电压 [V] [0|127.5]
float32 dp_low_bat_vol 
# 配电盒工作温度 [℃] [-40|215]
int32 pdu_temp 
# 自动驾驶电流（T7） [A] [0|255]
int32 auto_current1 
# DP故障代码 [] [0|255]
int32 dp_error_code 
# ON档电状态 （VCU指令与硬线是或逻辑） [] [0|255]
int32 on_sta 
# 自动驾驶电流（T2） [A] [0|255]
int32 auto_current2 
