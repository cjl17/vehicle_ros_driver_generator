# A31 消息接口修改说明

日期：2026-10-14

项目目录：`/home/ipc/cjl_ws/vehicle_ros_driver_generator`

本文记录调用方与重新生成的 `pix_robobus_driver_msgs` 对齐所需的全部名称修改，包括此前手动调整涉及的内容。以当前文件中的最终名称为准。

本轮实际修改 5 个底盘接口文件。油门、制动沿用已确认的 `pald`、`padl` 接口，相关 DBC 和调用方约定也记录在本文中。以下路径均相对于项目目录。

## 1. 修改文件清单

| 文件 | 修改内容 |
|---|---|
| `output/src/pixmoving_chassis_interface/include/pixmoving_chassis_interface/chassis_interface_include.hpp` | 修改 VCU 软件版本消息的头文件引用 |
| `output/src/pixmoving_chassis_interface/include/pixmoving_chassis_interface/chassis_interface_common.hpp` | 修改软件版本话题常量和话题路径 |
| `output/src/pixmoving_chassis_interface/include/pixmoving_chassis_interface/pixmoving_chassis_interface.hpp` | 修改消息类型、回调声明和订阅成员名称 |
| `output/src/pixmoving_chassis_interface/src/pixmoving_chassis_interface.cpp` | 同步订阅使用的消息类型、话题、回调和成员名称 |
| `output/src/pixmoving_chassis_interface/src/pixmoving_chassis.cpp` | 修改版本回调及消息类型、电压字段和 VIN 字段 |

## 2. chassis_interface_include.hpp

位置：第 49 行。

修改前：

```cpp
#include "pix_robobus_driver_msgs/msg/va_vcu_sofver.hpp"
```

修改后：

```cpp
#include "pix_robobus_driver_msgs/msg/vcu_soft_ver.hpp"
```

当前消息定义文件是 `VcuSoftVer.msg`，ROS 为其生成的 C++ 头文件是 `vcu_soft_ver.hpp`，C++ 消息类型是 `pix_robobus_driver_msgs::msg::VcuSoftVer`。C++ 中引用 `.hpp` 头文件。

## 3. chassis_interface_common.hpp

位置：第 117 行。

修改前：

```cpp
constexpr char VA_VCU_SOFVER[] = "/pix_robobus/va_vcu_sofver";
```

修改后：

```cpp
constexpr char VCU_SOFT_VER[] = "/pix_robobus/vcu_soft_ver";
```

话题路径与当前驱动 `report_parser.cpp` 发布的软件版本话题一致。

## 4. pixmoving_chassis_interface.hpp

位置：第 164 行、第 222 行。

修改前：

```cpp
void onVaVcuSofver(const pix_robobus_driver_msgs::msg::VaVcuSofver::SharedPtr msg);

rclcpp::Subscription<pix_robobus_driver_msgs::msg::VaVcuSofver>::SharedPtr VaVcuSofver_sub_;
```

修改后：

```cpp
void onVcuSoftVer(const pix_robobus_driver_msgs::msg::VcuSoftVer::SharedPtr msg);

rclcpp::Subscription<pix_robobus_driver_msgs::msg::VcuSoftVer>::SharedPtr VcuSoftVer_sub_;
```

## 5. pixmoving_chassis_interface.cpp

位置：第 520 行附近。

修改前：

```cpp
VaVcuSofver_sub_ = this->create_subscription<pix_robobus_driver_msgs::msg::VaVcuSofver>(
    topics::VA_VCU_SOFVER, rclcpp::QoS(1),
    std::bind(&PixmovingChassisInterfaceNode::onVaVcuSofver, this, std::placeholders::_1), options);
```

修改后：

```cpp
VcuSoftVer_sub_ = this->create_subscription<pix_robobus_driver_msgs::msg::VcuSoftVer>(
    topics::VCU_SOFT_VER, rclcpp::QoS(1),
    std::bind(&PixmovingChassisInterfaceNode::onVcuSoftVer, this, std::placeholders::_1), options);
```

## 6. pixmoving_chassis.cpp

### 6.1 电压字段

位置：第 55、56、58、59 行。

| 修改前 | 修改后 | 出现次数 |
|---|---|---|
| `msg->ad_v_vin1` | `msg->ad_volt_vin1` | 2 |
| `msg->ad_v_vin2` | `msg->ad_volt_vin2` | 2 |

修改后的回调：

```cpp
void PixmovingChassisInterfaceNode::onBcmMessage5(const pix_robobus_driver_msgs::msg::BcmMessage5::SharedPtr msg)
{
  // 烟雾传感器
  v2d_vehicle_info_msg_.smoke_concentration_voltage = std::round(msg->ad_volt_vin1);
  vehicle_info_msg_.co2 = std::round(msg->ad_volt_vin1);
  // co2传感器
  v2d_vehicle_info_msg_.co2_concentration_voltage = std::round(msg->ad_volt_vin2);
  vehicle_info_msg_.smoke = std::round(msg->ad_volt_vin2);
}
```

此次仅对齐消息字段名称；传感器数据赋值关系沿用现有逻辑。

### 6.2 软件版本回调

位置：第 380 行。

修改前：

```cpp
void PixmovingChassisInterfaceNode::onVaVcuSofver(const pix_robobus_driver_msgs::msg::VaVcuSofver::SharedPtr msg)
```

修改后：

```cpp
void PixmovingChassisInterfaceNode::onVcuSoftVer(const pix_robobus_driver_msgs::msg::VcuSoftVer::SharedPtr msg)
```

函数体中的 `version_year`、`version_month`、`version_day`、`version_main`、`version_sub`、`version_patch` 已与新消息定义一致，继续使用这些字段。

### 6.3 VIN 字段

位置：`onVinResp1`、`onVinResp2`、`onVinResp3`，第 389 至 407 行附近。

| 回调 | 原字段 | 当前字段 |
|---|---|---|
| `onVinResp1` | `vin00` 至 `vin07` | `vin_00` 至 `vin_07` |
| `onVinResp2` | `vin08` 至 `vin15` | `vin_08` 至 `vin_15` |
| `onVinResp3` | `vin16` | `vin_16` |

共修改 17 个字段引用，保留原有 VIN 拼接逻辑。三个回调中读取字段的代码分别为：

```cpp
// onVinResp1
std::string vcu_version1 = std::to_string(msg->vin_00) + std::to_string(msg->vin_01) + std::to_string(msg->vin_02) +
                           std::to_string(msg->vin_03) + std::to_string(msg->vin_04) + std::to_string(msg->vin_05) +
                           std::to_string(msg->vin_06) + std::to_string(msg->vin_07);

// onVinResp2
std::string vcu_version2 = std::to_string(msg->vin_08) + std::to_string(msg->vin_09) + std::to_string(msg->vin_10) +
                           std::to_string(msg->vin_11) + std::to_string(msg->vin_12) + std::to_string(msg->vin_13) +
                           std::to_string(msg->vin_14) + std::to_string(msg->vin_15);

// onVinResp3
std::string vcu_version3 = std::to_string(msg->vin_16);
```

## 7. 油门、制动字段的最终约定

油门和制动字段从 DBC 源头确定名称。最终使用下表名称，避免将反馈字段再次改为 `pedal_fb`。

| 信号 | DBC 原名 | DBC 当前名称 | 生成的消息字段 |
|---|---|---|---|
| 油门反馈 | `VCU_ChassisThrottlePedalFb` | `VCU_ChassisThrottlePaldFb` | `vcu_chassis_throttle_pald_fb` |
| 制动反馈 | `VCU_ChassisBrakePedalFb` | `VCU_ChassisBrakePadlFb` | `vcu_chassis_brake_padl_fb` |

`config/a31.dbc` 中已同步修改信号定义和注释引用，共 4 处：

```dbc
SG_ VCU_ChassisThrottlePaldFb:24|10@1+ (0.1,0) [0|100] "%"  ACU
SG_ VCU_ChassisBrakePadlFb:8|10@1+ (0.1,0) [0|100] "%"  ACU
CM_ SG_ 1328 VCU_ChassisThrottlePaldFb "油门请求值反馈";
CM_ SG_ 1329 VCU_ChassisBrakePadlFb "制动踏板值反馈";
```

上述四行位于各自原来的报文定义、注释位置，分别是第 73、84、674、684 行。当前 DBC 已统一为 UTF-8 编码，保留 CRLF 换行；信号位位置、长度、缩放系数及范围沿用原值。

`output/src/pixmoving_chassis_interface/src/pixmoving_chassis.cpp` 第 67、111 行使用：

```cpp
vehicle_info_msg_.thr = msg->vcu_chassis_throttle_pald_fb;
vehicle_info_msg_.brk = msg->vcu_chassis_brake_padl_fb;
```

`output/src/pix_interface/src/report_converter.cpp` 第 483、485 行使用：

```cpp
actuation_status_stamped_msg_.status.accel_status =
    va_drive_sta_fb_ptr_->vcu_chassis_throttle_pald_fb / 100.0;
actuation_status_stamped_msg_.status.brake_status =
    va_brake_sta_fb_ptr_->vcu_chassis_brake_padl_fb / 100.0;
```

`report_converter.cpp` 的这两处此前已经恢复为旧接口，本轮无需再次修改。新生成的消息定义和驱动解析代码也已使用 `pald`、`padl`。

其他信号中的 `Pedal` 保留各自原名，例如 `vcu_chassis_throttle_pedal_req_fb`、`vcu_brake_pedal_req_fb`。不能全局替换所有 `Pedal` 或 `pedal`。

## 8. 验证情况

- 已根据当前 40 个 `.msg` 定义，静态核对驱动、底盘接口、`pix_interface` 和 `robobus_hmi_data_relay` 中识别到的消息头文件、消息类型和字段引用，未发现名称不匹配。
- 已检查软件版本回调的声明、定义、订阅绑定及发布和订阅话题一致性。
- 已核对消息文件在 CMake 中的登记、相关包的消息依赖声明及列出的源码路径。
- 按要求未执行编译，也未进行运行或实车验证。静态检查结果不等同于编译通过。
