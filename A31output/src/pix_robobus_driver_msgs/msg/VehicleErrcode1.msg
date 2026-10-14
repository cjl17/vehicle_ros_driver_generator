std_msgs/Header header 
# 前左电控硬件故障 [] [0|1]
int8 flmc_hardware_fault 
# 前左电控温度故障 [] [0|1]
int8 flmc_tem_fault 
# 前左电机温度故障 [] [0|1]
int8 flm_tem_fault 
# 后左电控硬件故障 [] [0|1]
int8 rlmc_hardware_fault 
# 后左电控温度故障 [] [0|1]
int8 rlmc_tem_fault 
# 后左电机温度故障 [] [0|1]
int8 rlm_tem_fault 
# 前右电控硬件故障 [] [0|1]
int8 frmc_hardware_fault 
# 前右电控温度故障 [] [0|1]
int8 frmc_tem_fault 
# 前右电机温度故障 [] [0|1]
int8 frm_tem_fault 
# 后右电控硬件故障 [] [0|1]
int8 rrmc_hardware_fault 
# 后右电控温度故障 [] [0|1]
int8 rrmc_tem_fault 
# 后右电机温度故障 [] [0|1]
int8 rrm_tem_fault 
# 前左电控网络故障 [] [0|1]
int8 flmc_network_fault 
# 前右电控网络故障 [] [0|1]
int8 frmc_network_fault 
# 后左电控网络故障 [] [0|1]
int8 rlmc_network_fault 
# 后右电控网络故障 [] [0|1]
int8 rrmc_network_fault 
# 前电子转向硬件故障 [] [0|1]
int8 fr_steer_hardware_fault 
# 后电子转向硬件故障 [] [0|1]
int8 rr_steer_hardware_fault 
# 前电子转向网络故障 [] [0|1]
int8 fr_steer_network_fault 
# 后电子转向网络故障 [] [0|1]
int8 rr_steer_network_fault 
# 电制动系统硬件故障 [] [0|1]
int8 brake_hardware_fault 
# 电制动系统高温故障 [] [0|1]
int8 brake_high_tem_fault 
# 制动液位过低 [] [0|1]
int8 brake_luid_level_low 
# 电制动系统网络故障 [] [0|1]
int8 brake_network_fault 
# 驻车冗余系统硬件故障 [] [0|1]
int8 park_hardware_fault 
# 驻车冗余系统网络故障 [] [0|1]
int8 park_network_fault 
# 无线遥控器系统网络故障 [] [0|1]
int8 rcu_network_fault 
# 无线遥控器系统信号强度弱 [] [0|1]
int8 rcu_weak_signal 
# 无线遥控电池电量报警 [] [0|1]
int8 rcu_elec_low_alarm 
# 预留 [] [0|1]
int8 spare1 
# 预留 [] [0|1]
int8 spare2 
# BMS系统网络故障 [] [0|1]
int8 bms_network_fault 
# 绝缘报警 [] [0|1]
int8 bms_insulation_fault 
# 单体电压过压 [] [0|1]
int8 bms_ocv_cell 
# 单体电压欠压 [] [0|1]
int8 bms_odv_cell 
# 总压过高 [] [0|1]
int8 bms_ocv_batt 
# 总压过低 [] [0|1]
int8 bms_odv_batt 
# 压差过大 [] [0|1]
int8 bms_cell_volt_diff 
# 电池温度过高 [] [0|1]
int8 bms_temp_h 
# 电池温度过低 [] [0|1]
int8 bms_temp_l 
# 温差过大 [] [0|1]
int8 bms_temp_diff 
# 回馈过流 [] [0|1]
int8 bms_war_chg_overcurrent 
# SOC过高 [] [0|1]
int8 bms_soc_h 
# SOC过低 [] [0|1]
int8 bms_soc_l 
# 充电加热超时 [] [0|1]
int8 bms_time_of_heating_too_long 
# SOC跳变 [] [0|1]
int8 bms_soc_break 
# 放电过流 [] [0|1]
int8 bms_dis_char_over_cur 
# 慢充充电过流 [] [0|1]
int8 bms_char_over_cur_slow 
# 快充充电过流 [] [0|1]
int8 bms_fast_char_over_cur 
# 单体电压采集故障 [] [0|1]
int8 bms_alm_sense_cell 
# 温度采集故障 [] [0|1]
int8 bms_alm_sense_temp 
# 电流传感器故障 [] [0|1]
int8 bms_alm_sense_curr 
# 高压互锁故障 [] [0|1]
int8 bms_hvil 
# 内网通信 [] [0|1]
int8 bms_war_in_can_fault 
# 充电机通信中断 [] [0|1]
int8 bms_lst_com_with_obc 
# 整车通信中断 [] [0|1]
int8 bms_lst_com_with_vcu 
# 预充失败 [] [0|1]
int8 bms_precharger_fault 
# 总正继电器黏连 [] [0|1]
int8 bms_pos_relay_conglutination 
# 总负继电器黏连 [] [0|1]
int8 bms_neg_relay_conglutination 
# 预留 [] [0|1]
int8 spare3 
# 预留 [] [0|1]
int8 spare4 
# DCDC系统过温故障 [] [0|1]
int8 dcdc_high_tem_alarm 
# DCDC系统硬件故障 [] [0|1]
int8 dcdc_hardware_fault 
# DCDC系统网络故障 [] [0|1]
int8 dcdc_network_fault 
