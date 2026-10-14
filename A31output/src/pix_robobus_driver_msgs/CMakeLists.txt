cmake_minimum_required(VERSION 3.5)
project(pix_robobus_driver_msgs)

find_package(ament_cmake_auto REQUIRED)
ament_auto_find_build_dependencies()

set(msg_files
	"msg/VcuSoftVer.msg"
	"msg/AcMessage1.msg"
	"msg/AcMessage2.msg"
	"msg/VinResp1.msg"
	"msg/VinResp2.msg"
	"msg/VinResp3.msg"
	"msg/VehicleErrcode1.msg"
	"msg/VehicleErrcode2.msg"
	"msg/HistoricalVehiclefailures1.msg"
	"msg/HistoricalVehiclefailures2.msg"
	"msg/VaDriveStaFb.msg"
	"msg/VaBrakeStaFb.msg"
	"msg/VaSteerStaFb.msg"
	"msg/VaVehicleWorkStaFb.msg"
	"msg/VaPowerStaFb.msg"
	"msg/VaVehicleStaFb.msg"
	"msg/VaVehicleFltSta.msg"
	"msg/VaChassisWheelRpmFb.msg"
	"msg/VaChassisOdoFb.msg"
	"msg/VcuTransfer.msg"
	"msg/VaChassisWheelTirePressFb.msg"
	"msg/VaChassisWheelAngleFb.msg"
	"msg/VaChassisWheelTorqueFb.msg"
	"msg/BcmMessage4.msg"
	"msg/BcmMessage5.msg"
	"msg/DpMessgae4.msg"
	"msg/DpMessgae5.msg"
	"msg/AvAebCtrl.msg"
	"msg/AvDriveCtrl.msg"
	"msg/AvBrakeCtrl.msg"
	"msg/AvSteerCtrl.msg"
	"msg/AvVehicleCtrl.msg"
	"msg/AvWheelTorqueCtrl.msg"
	"msg/AvManualSpdLimit.msg"
	"msg/AvSelfDrivingWorkSt.msg"
	"msg/AutoMessage.msg"
	"msg/RemoteMessage.msg"
	"msg/AcuSysTime.msg"
	"msg/AvMessage1.msg"
	"msg/AvMessage2.msg"

)

set(msg_dependencies
	std_msgs
  builtin_interfaces)

rosidl_generate_interfaces(${PROJECT_NAME}
  ${msg_files}
  DEPENDENCIES ${msg_dependencies}
  ADD_LINTER_TESTS)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_auto_package()