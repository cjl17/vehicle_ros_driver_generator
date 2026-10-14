#include "pixmoving_chassis_interface/pixmoving_chassis_interface.hpp"

namespace
{
constexpr double kEarthRadiusMeters = 6378137.0;
constexpr double kPi = 3.14159265358979323846;

double toRadians(const double degrees)
{
  return degrees * kPi / 180.0;
}
}  // namespace

namespace pixmoving
{
namespace chassis
{
namespace interface
{

const char* PixmovingChassisInterfaceNode::mileageSourceToString(const MileageSource source) const
{
  switch (source)
  {
    case MileageSource::NDT:
      return "NDT";
    case MileageSource::GNSS:
      return "GNSS";
    case MileageSource::CHASSIS_SPEED:
      return "CHASSIS_SPEED";
    case MileageSource::NONE:
    default:
      return "NONE";
  }
}

bool PixmovingChassisInterfaceNode::isNdtReliable() const
{
  if (localization_pose_ptr_ == nullptr || last_ndt_pos_q_time_.nanoseconds() == 0)
  {
    return false;
  }

  const auto now = this->now();
  if ((now - localization_pose_received_time_).seconds() > ndt_timeout_sec_ ||
      (now - last_ndt_pos_q_time_).seconds() > ndt_timeout_sec_)
  {
    return false;
  }

  if (!std::isfinite(latest_ndt_pos_q_))
  {
    return false;
  }

  return latest_ndt_pos_q_ >= 0.0 && latest_ndt_pos_q_ <= ndt_pos_q_threshold_;
}

bool PixmovingChassisInterfaceNode::isGnssReliable() const
{
  if (!last_gnss_fix_valid_ || latest_valid_gnss_fix_ptr_ == nullptr)
  {
    return false;
  }

  const auto now = this->now();
  if ((now - last_gnss_fix_time_).seconds() > gnss_timeout_sec_)
  {
    return false;
  }

  const auto required_streak = static_cast<std::size_t>(std::max(0, gnss_warmup_frames_));
  if (gnss_valid_streak_ < required_streak)
  {
    return false;
  }

  const auto& msg = *latest_valid_gnss_fix_ptr_;
  if (msg.status.status < sensor_msgs::msg::NavSatStatus::STATUS_FIX)
  {
    return false;
  }

  return !(msg.latitude == 0.0 && msg.longitude == 0.0 && msg.altitude == 0.0);
}

bool PixmovingChassisInterfaceNode::isChassisSpeedReliable() const
{
  if (last_chassis_speed_time_.nanoseconds() == 0)
  {
    return false;
  }

  if ((this->now() - last_chassis_speed_time_).seconds() > chassis_speed_timeout_sec_)
  {
    return false;
  }

  return std::isfinite(last_chassis_speed_mps_) && last_chassis_speed_mps_ >= 0.0;
}

PixmovingChassisInterfaceNode::MileageSource PixmovingChassisInterfaceNode::chooseMileageSource() const
{
  if (isNdtReliable())
  {
    return MileageSource::NDT;
  }

  if (isGnssReliable())
  {
    return MileageSource::GNSS;
  }

  if (isChassisSpeedReliable())
  {
    return MileageSource::CHASSIS_SPEED;
  }

  return MileageSource::NONE;
}

bool PixmovingChassisInterfaceNode::shouldAcceptMileageDelta(
    const double delta_m, const double delta_time_s, const double jump_threshold_m) const
{
  if (!std::isfinite(delta_m) || !std::isfinite(delta_time_s))
  {
    return false;
  }

  if (delta_time_s <= 0.0 || delta_m < 1e-4)
  {
    return false;
  }

  if (jump_threshold_m > 0.0 && delta_m > jump_threshold_m)
  {
    return false;
  }

  if (isChassisSpeedReliable())
  {
    if (last_chassis_speed_mps_ < standstill_speed_threshold_mps_)
    {
      return delta_m <= 0.3;
    }

    const double predicted_max = last_chassis_speed_mps_ * delta_time_s * max_delta_ratio_ + 1.0;
    if (delta_m > std::max(jump_threshold_m, predicted_max))
    {
      return false;
    }
  }

  return true;
}

double PixmovingChassisInterfaceNode::calcHaversineMeters(
    const sensor_msgs::msg::NavSatFix& from, const sensor_msgs::msg::NavSatFix& to) const
{
  const double lat1 = toRadians(from.latitude);
  const double lat2 = toRadians(to.latitude);
  const double delta_lat = lat2 - lat1;
  const double delta_lon = toRadians(to.longitude - from.longitude);

  const double sin_half_dlat = std::sin(delta_lat * 0.5);
  const double sin_half_dlon = std::sin(delta_lon * 0.5);
  const double a = sin_half_dlat * sin_half_dlat +
                   std::cos(lat1) * std::cos(lat2) * sin_half_dlon * sin_half_dlon;
  const double c = 2.0 * std::atan2(std::sqrt(a), std::sqrt(std::max(0.0, 1.0 - a)));
  return kEarthRadiusMeters * c;
}

void PixmovingChassisInterfaceNode::resetMileageAnchorForSource(const MileageSource source)
{
  switch (source)
  {
    case MileageSource::NDT:
      if (localization_pose_ptr_ != nullptr)
      {
        last_ndt_pose_for_mileage_ = std::make_shared<geometry_msgs::msg::PoseStamped>(*localization_pose_ptr_);
        last_ndt_pose_time_for_mileage_ = localization_pose_received_time_;
      }
      else
      {
        last_ndt_pose_for_mileage_.reset();
      }
      break;

    case MileageSource::GNSS:
      if (latest_valid_gnss_fix_ptr_ != nullptr)
      {
        last_gnss_fix_for_mileage_ = latest_valid_gnss_fix_ptr_;
        last_gnss_fix_time_for_mileage_ = last_gnss_fix_time_;
      }
      else
      {
        last_gnss_fix_for_mileage_.reset();
      }
      break;

    case MileageSource::CHASSIS_SPEED:
      if (last_chassis_speed_time_.nanoseconds() != 0)
      {
        last_chassis_speed_integration_time_ = last_chassis_speed_time_;
      }
      break;

    case MileageSource::NONE:
    default:
      break;
  }
}

void PixmovingChassisInterfaceNode::syncPowerCycleResetByRawTrip()
{
  if (latest_raw_can_trip_m_ < 0.0)
  {
    return;
  }

  if (pending_raw_trip_sync_)
  {
    pending_raw_trip_sync_ = false;

    if (latest_raw_can_trip_m_ + raw_trip_sync_threshold_m_ < fused_power_on_mileage_m_)
    {
      fused_power_on_mileage_m_ = std::max(0.0, latest_raw_can_trip_m_);
      current_mileage_source_ = MileageSource::NONE;
      last_ndt_pose_for_mileage_.reset();
      last_gnss_fix_for_mileage_.reset();
      last_chassis_speed_integration_time_ = last_chassis_speed_time_;
      RCLCPP_WARN(
          this->get_logger(),
          "Detected new power cycle after startup, reset fused ptm to raw CAN trip %.2f m",
          latest_raw_can_trip_m_);
    }
    else if (latest_raw_can_trip_m_ > fused_power_on_mileage_m_ + raw_trip_sync_threshold_m_)
    {
      fused_power_on_mileage_m_ = latest_raw_can_trip_m_;
      RCLCPP_WARN(
          this->get_logger(),
          "Aligned fused ptm to raw CAN trip on startup: %.2f m",
          latest_raw_can_trip_m_);
    }
  }

  if (last_raw_can_trip_m_ >= 0.0 &&
      latest_raw_can_trip_m_ + raw_trip_sync_threshold_m_ < last_raw_can_trip_m_)
  {
    fused_power_on_mileage_m_ = std::max(0.0, latest_raw_can_trip_m_);
    current_mileage_source_ = MileageSource::NONE;
    last_ndt_pose_for_mileage_.reset();
    last_gnss_fix_for_mileage_.reset();
    last_chassis_speed_integration_time_ = last_chassis_speed_time_;
    RCLCPP_WARN(
        this->get_logger(),
        "Detected raw CAN trip reset during runtime, reset fused ptm to %.2f m",
        latest_raw_can_trip_m_);
  }

  last_raw_can_trip_m_ = latest_raw_can_trip_m_;
}

void PixmovingChassisInterfaceNode::accumulateFromNdt()
{
  if (localization_pose_ptr_ == nullptr)
  {
    return;
  }

  if (last_ndt_pose_for_mileage_ == nullptr || last_ndt_pose_time_for_mileage_.nanoseconds() == 0)
  {
    resetMileageAnchorForSource(MileageSource::NDT);
    return;
  }

  const double delta_time_s = (localization_pose_received_time_ - last_ndt_pose_time_for_mileage_).seconds();
  if (delta_time_s <= 0.0 || delta_time_s > ndt_timeout_sec_)
  {
    resetMileageAnchorForSource(MileageSource::NDT);
    return;
  }

  const double dx =
      localization_pose_ptr_->pose.position.x - last_ndt_pose_for_mileage_->pose.position.x;
  const double dy =
      localization_pose_ptr_->pose.position.y - last_ndt_pose_for_mileage_->pose.position.y;
  const double delta_m = std::sqrt(dx * dx + dy * dy);

  if (shouldAcceptMileageDelta(delta_m, delta_time_s, ndt_jump_reject_threshold_m_))
  {
    fused_power_on_mileage_m_ += delta_m;
  }

  last_ndt_pose_for_mileage_ = std::make_shared<geometry_msgs::msg::PoseStamped>(*localization_pose_ptr_);
  last_ndt_pose_time_for_mileage_ = localization_pose_received_time_;
}

void PixmovingChassisInterfaceNode::accumulateFromGnss()
{
  if (latest_valid_gnss_fix_ptr_ == nullptr)
  {
    return;
  }

  if (last_gnss_fix_for_mileage_ == nullptr || last_gnss_fix_time_for_mileage_.nanoseconds() == 0)
  {
    resetMileageAnchorForSource(MileageSource::GNSS);
    return;
  }

  const double delta_time_s = (last_gnss_fix_time_ - last_gnss_fix_time_for_mileage_).seconds();
  if (delta_time_s <= 0.0 || delta_time_s > gnss_timeout_sec_)
  {
    resetMileageAnchorForSource(MileageSource::GNSS);
    return;
  }

  const double delta_m = calcHaversineMeters(*last_gnss_fix_for_mileage_, *latest_valid_gnss_fix_ptr_);
  if (shouldAcceptMileageDelta(delta_m, delta_time_s, gnss_jump_reject_threshold_m_))
  {
    fused_power_on_mileage_m_ += delta_m;
  }

  last_gnss_fix_for_mileage_ = latest_valid_gnss_fix_ptr_;
  last_gnss_fix_time_for_mileage_ = last_gnss_fix_time_;
}

void PixmovingChassisInterfaceNode::accumulateFromChassisSpeed()
{
  if (!isChassisSpeedReliable())
  {
    return;
  }

  if (last_chassis_speed_integration_time_.nanoseconds() == 0)
  {
    last_chassis_speed_integration_time_ = last_chassis_speed_time_;
    return;
  }

  const double delta_time_s = (last_chassis_speed_time_ - last_chassis_speed_integration_time_).seconds();
  if (delta_time_s <= 0.0 || delta_time_s > chassis_speed_timeout_sec_)
  {
    last_chassis_speed_integration_time_ = last_chassis_speed_time_;
    return;
  }

  if (last_chassis_speed_mps_ >= standstill_speed_threshold_mps_)
  {
    fused_power_on_mileage_m_ += last_chassis_speed_mps_ * delta_time_s;
  }

  last_chassis_speed_integration_time_ = last_chassis_speed_time_;
}

void PixmovingChassisInterfaceNode::updateFusedPowerOnMileage()
{
  if (!enable_fused_ptm_)
  {
    return;
  }

  syncPowerCycleResetByRawTrip();

  const auto selected_source = chooseMileageSource();
  if (selected_source != current_mileage_source_)
  {
    RCLCPP_INFO(
        this->get_logger(),
        "Mileage source switched: %s -> %s",
        mileageSourceToString(current_mileage_source_),
        mileageSourceToString(selected_source));
    current_mileage_source_ = selected_source;
    resetMileageAnchorForSource(current_mileage_source_);
  }

  switch (current_mileage_source_)
  {
    case MileageSource::NDT:
      accumulateFromNdt();
      break;

    case MileageSource::GNSS:
      accumulateFromGnss();
      break;

    case MileageSource::CHASSIS_SPEED:
      accumulateFromChassisSpeed();
      break;

    case MileageSource::NONE:
    default:
      break;
  }

  const std::int32_t new_ptm =
      static_cast<std::int32_t>(std::lround(std::max(0.0, fused_power_on_mileage_m_)));
  if (last_ptm_ != new_ptm && ((last_ptm_ == -1) != (new_ptm == -1)))
  {
    RCLCPP_INFO(this->get_logger(), "VehicleInfo.ptm changed %d -> %d", last_ptm_, new_ptm);
  }

  vehicle_info_msg_.ptm = new_ptm;
  last_ptm_ = new_ptm;
}

}  // namespace interface
}  // namespace chassis
}  // namespace pixmoving
