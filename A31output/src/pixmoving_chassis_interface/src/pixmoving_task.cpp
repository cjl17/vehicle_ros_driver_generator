#include "pixmoving_chassis_interface/pixmoving_chassis_interface.hpp"

namespace pixmoving
{
namespace chassis
{
namespace interface
{

void PixmovingChassisInterfaceNode::readStationYamlFile(const std::string station_yaml_file_path)
{
  try
  {
    // 尝试加载文件
    station_yaml_list_obj_ = YAML::LoadAllFromFile(station_yaml_file_path);
  }
  catch (const YAML::BadFile& e)
  {
    // 文件不存在或无法读取时处理
    RCLCPP_ERROR(this->get_logger(), "[%s]No such file or directory", station_yaml_file_path.c_str());
    rclcpp::shutdown();
  }

  if (station_yaml_list_obj_.size() < 2)
  {
    RCLCPP_ERROR(this->get_logger(), "[%s]至少2个站点", station_yaml_file_path.c_str());
    rclcpp::shutdown();
  }
}

bool PixmovingChassisInterfaceNode::calculateAngleBetweenQuaternions(const std::array<double, 4>& q1,
                                                                     const std::array<double, 4>& q2)
{
  // 计算点积
  double dot_product = q1[0] * q2[0] + q1[1] * q2[1] + q1[2] * q2[2] + q1[3] * q2[3];
  dot_product = std::max(-1.0, std::min(1.0, std::abs(dot_product)));
  // 计算夹角
  double angle = 2 * std::acos(dot_product);

  // 将弧度转换为度数
  double angle_degrees = angle * 180.0 / M_PI;

  // 判断当前点和起点或者终点夹角小于10, 真代表当前点和起点或者终点同向，假代表不同向
  return angle_degrees < 10.0;
}

bool PixmovingChassisInterfaceNode::calculateTwoPointsDistance(const std::array<double, 3>& p1,
                                                               const std::array<double, 3>& p2)
{
  // 只考虑平面距离
  double distance = std::sqrt(std::pow(p1[0] - p2[0], 2) + std::pow(p1[1] - p2[1], 2));
  return std::abs(distance) < 10.0;
}

int8_t PixmovingChassisInterfaceNode::matchStationIndex(const geometry_msgs::msg::Pose route, const std::string info)
{
  RCLCPP_INFO(this->get_logger(), "%s", info.c_str());

  std::array<double, 3> p2 = { route.position.x, route.position.y, route.position.z };

  std::array<double, 4> q2 = { route.orientation.x, route.orientation.y, route.orientation.z, route.orientation.w };

  for (std::size_t index = 0; index < station_yaml_list_obj_.size(); ++index)
  {
    std::array<double, 3> p1 = { station_yaml_list_obj_[index]["pose"]["position"]["x"].as<double>(),
                                 station_yaml_list_obj_[index]["pose"]["position"]["y"].as<double>(),
                                 station_yaml_list_obj_[index]["pose"]["position"]["z"].as<double>() };

    std::array<double, 4> q1 = { station_yaml_list_obj_[index]["pose"]["orientation"]["x"].as<double>(),
                                 station_yaml_list_obj_[index]["pose"]["orientation"]["y"].as<double>(),
                                 station_yaml_list_obj_[index]["pose"]["orientation"]["z"].as<double>(),
                                 station_yaml_list_obj_[index]["pose"]["orientation"]["w"].as<double>() };

    // 判读两点之间距离大于 10.0，则跳过
    if (!calculateTwoPointsDistance(p2, p1))
    {
      continue;
    }
    // 判读两点之间夹角是否小于10.0
    if (calculateAngleBetweenQuaternions(q2, q1))
    {
      RCLCPP_INFO(this->get_logger(), "找到站点: %s",
                  station_yaml_list_obj_[index]["station_name"].as<std::string>().c_str());
      return static_cast<int8_t>(index);
    }
  }
  RCLCPP_ERROR(this->get_logger(), "没有找到相关站点返回-1");
  return -1;
}

int8_t PixmovingChassisInterfaceNode::matchStationWithDistanceAndAngle(const geometry_msgs::msg::Pose& pose)
{
  double vehicle_yaw = ChassisInterfaceUtils::yawFromQuaternion(pose.orientation);
  struct Candidate
  {
    int index;
    double distance;
    double angle_diff;
  };
  std::vector<Candidate> candidates;

  // 阈值
  constexpr double DIST_THRESHOLD = 15.0;       // 米
  constexpr double ANGLE_THRESHOLD = M_PI / 2;  // 90度

  // 1. 找距离阈值内的候选
  for (size_t i = 0; i < station_yaml_list_obj_.size(); ++i)
  {
    const auto& station_pose = station_yaml_list_obj_[i]["pose"];
    double dx = pose.position.x - station_pose["position"]["x"].as<double>();
    double dy = pose.position.y - station_pose["position"]["y"].as<double>();
    double distance = std::sqrt(dx * dx + dy * dy);

    if (distance <= DIST_THRESHOLD)
    {
      geometry_msgs::msg::Quaternion station_q;
      station_q.x = station_pose["orientation"]["x"].as<double>();
      station_q.y = station_pose["orientation"]["y"].as<double>();
      station_q.z = station_pose["orientation"]["z"].as<double>();
      station_q.w = station_pose["orientation"]["w"].as<double>();
      double station_yaw = ChassisInterfaceUtils::yawFromQuaternion(station_q);
      double angle_diff = ChassisInterfaceUtils::angleDifference(vehicle_yaw, station_yaw);
      candidates.push_back({ static_cast<int>(i), distance, angle_diff });
    }
  }

  // 2. 没有候选 → fallback
  if (candidates.empty())
    return -1;

  // 3. 只有一个候选 → 直接返回
  if (candidates.size() == 1)
    return static_cast<int8_t>(candidates[0].index);

  // 4. 多候选 → 按角度最小选择
  int best_index = -1;
  double min_angle = ANGLE_THRESHOLD;
  for (auto& c : candidates)
  {
    if (c.angle_diff < min_angle)
    {
      min_angle = c.angle_diff;
      best_index = c.index;
    }
  }

  // 5. 没有角度在阈值内的 → 返回距离最小
  if (best_index == -1)
  {
    best_index = std::min_element(candidates.begin(), candidates.end(), [](const Candidate& a, const Candidate& b) {
                   return a.distance < b.distance;
                 })->index;
  }

  return static_cast<int8_t>(best_index);
}

// 发布所有站点信息
void PixmovingChassisInterfaceNode::publishAllStationInfo()
{
  RCLCPP_INFO_STREAM(this->get_logger(), "station.yaml可用的站点数量: " << station_yaml_list_obj_.size());

  v2d_all_station_info_msg_.header.frame_id = "map";
  v2d_all_station_info_msg_.header.stamp = this->get_clock()->now();

  for (std::size_t station_index = 0; station_index < station_yaml_list_obj_.size(); ++station_index)
  {
    pixmoving_hmi_msgs::msg::Station station;

    station.id = station_index;
    station.name = station_yaml_list_obj_[station_index]["station_name"].as<std::string>();
    station.osm_id = station_yaml_list_obj_[station_index]["osm_id"].as<int>();
    station.staion_pose.position.x = station_yaml_list_obj_[station_index]["pose"]["position"]["x"].as<double>();
    station.staion_pose.position.y = station_yaml_list_obj_[station_index]["pose"]["position"]["y"].as<double>();
    station.staion_pose.position.z = station_yaml_list_obj_[station_index]["pose"]["position"]["z"].as<double>();

    station.staion_pose.orientation.x = station_yaml_list_obj_[station_index]["pose"]["orientation"]["x"].as<double>();
    station.staion_pose.orientation.y = station_yaml_list_obj_[station_index]["pose"]["orientation"]["y"].as<double>();
    station.staion_pose.orientation.z = station_yaml_list_obj_[station_index]["pose"]["orientation"]["z"].as<double>();
    station.staion_pose.orientation.w = station_yaml_list_obj_[station_index]["pose"]["orientation"]["w"].as<double>();

    v2d_all_station_info_msg_.stations.push_back(station);
  }

  all_station_info_pub_->publish(v2d_all_station_info_msg_);

  RCLCPP_INFO_STREAM(this->get_logger(), "v2d_all_station_info_msg发布成功");
}

void PixmovingChassisInterfaceNode::populateStationMsgFromYamlIndex(
    int station_index, const std::string& station_name, pixmoving_hmi_msgs::msg::Station& station_msg)
{
  if (station_index < 0 || station_index >= static_cast<int>(station_yaml_list_obj_.size()))
  {
    RCLCPP_WARN(this->get_logger(), "Invalid station index %d while populating display message", station_index);
    return;
  }

  station_msg.id = station_index + 1;
  station_msg.name = station_name.empty() ?
      station_yaml_list_obj_[station_index]["station_name"].as<std::string>() :
      station_name;
  station_msg.osm_id = station_yaml_list_obj_[station_index]["osm_id"].as<int>();
  station_msg.staion_pose.position.x = station_yaml_list_obj_[station_index]["pose"]["position"]["x"].as<double>();
  station_msg.staion_pose.position.y = station_yaml_list_obj_[station_index]["pose"]["position"]["y"].as<double>();
  station_msg.staion_pose.position.z = station_yaml_list_obj_[station_index]["pose"]["position"]["z"].as<double>();
  station_msg.staion_pose.orientation.x =
      station_yaml_list_obj_[station_index]["pose"]["orientation"]["x"].as<double>();
  station_msg.staion_pose.orientation.y =
      station_yaml_list_obj_[station_index]["pose"]["orientation"]["y"].as<double>();
  station_msg.staion_pose.orientation.z =
      station_yaml_list_obj_[station_index]["pose"]["orientation"]["z"].as<double>();
  station_msg.staion_pose.orientation.w =
      station_yaml_list_obj_[station_index]["pose"]["orientation"]["w"].as<double>();
}

void PixmovingChassisInterfaceNode::setDisplayStationsFromIndexes(
    int current_index, const std::string& current_name, int target_index, const std::string& target_name)
{
  populateStationMsgFromYamlIndex(current_index, current_name, v2d_current_station_info_msg_.current_station);
  populateStationMsgFromYamlIndex(target_index, target_name, v2d_current_station_info_msg_.target_station);
}

void PixmovingChassisInterfaceNode::latchTaskSemantic(
    int current_index, const std::string& current_name, int target_index, const std::string& target_name)
{
  std::lock_guard<std::mutex> lock(task_semantic_mutex_);
  semantic_origin_station_index_ = current_index;
  semantic_target_station_index_ = target_index;
  has_task_semantic_ = true;
  task_terminal_ = false;

  task_station_info_temp_.current_station_index = current_index + 1;
  task_station_info_temp_.target_station_index = target_index + 1;
  task_station_info_temp_.current_station_name = current_name;
  task_station_info_temp_.target_station_name = target_name;

  RCLCPP_INFO(
      this->get_logger(),
      "latched task semantic origin=%s(idx=%d) target=%s(idx=%d)",
      task_station_info_temp_.current_station_name.c_str(), semantic_origin_station_index_,
      task_station_info_temp_.target_station_name.c_str(), semantic_target_station_index_);
}

void PixmovingChassisInterfaceNode::updateTaskSemanticStatusDebug(
    const std::string& lifecycle, const std::string& decision, const std::string& source,
    int inferred_current_index, const std::string& inferred_current_name,
    int inferred_target_index, const std::string& inferred_target_name, bool triggered_new_task_event)
{
  std::lock_guard<std::mutex> lock(task_semantic_mutex_);
  if (!lifecycle.empty())
  {
    last_task_lifecycle_ = lifecycle;
  }
  if (!decision.empty())
  {
    last_task_route_decision_ = decision;
  }
  if (!source.empty())
  {
    last_task_station_source_ = source;
  }
  last_inferred_current_station_index_ = inferred_current_index;
  last_inferred_target_station_index_ = inferred_target_index;
  last_inferred_current_station_name_ = inferred_current_name;
  last_inferred_target_station_name_ = inferred_target_name;
  last_triggered_new_task_event_ = triggered_new_task_event;
}

void PixmovingChassisInterfaceNode::refreshTaskSemanticStatusSummary()
{
  std::lock_guard<std::mutex> lock(task_semantic_mutex_);

  task_semantic_status_msg_.header.stamp = this->now();
  task_semantic_status_msg_.header.frame_id = "map";
  task_semantic_status_msg_.lifecycle = last_task_lifecycle_;
  task_semantic_status_msg_.last_route_decision = last_task_route_decision_;
  task_semantic_status_msg_.last_station_source = last_task_station_source_;
  task_semantic_status_msg_.has_task_semantic = has_task_semantic_;
  task_semantic_status_msg_.task_terminal = task_terminal_;
  task_semantic_status_msg_.last_triggered_new_task_event = last_triggered_new_task_event_;

  task_semantic_status_msg_.semantic_origin_station_index =
      semantic_origin_station_index_ >= 0 ? semantic_origin_station_index_ + 1 : 0;
  task_semantic_status_msg_.semantic_origin_station_name =
      semantic_origin_station_index_ >= 0 ? task_station_info_temp_.current_station_name : "";
  task_semantic_status_msg_.semantic_target_station_index =
      semantic_target_station_index_ >= 0 ? semantic_target_station_index_ + 1 : 0;
  task_semantic_status_msg_.semantic_target_station_name =
      semantic_target_station_index_ >= 0 ? task_station_info_temp_.target_station_name : "";

  task_semantic_status_msg_.inferred_current_station_index =
      last_inferred_current_station_index_ >= 0 ? last_inferred_current_station_index_ + 1 : 0;
  task_semantic_status_msg_.inferred_current_station_name = last_inferred_current_station_name_;
  task_semantic_status_msg_.inferred_target_station_index =
      last_inferred_target_station_index_ >= 0 ? last_inferred_target_station_index_ + 1 : 0;
  task_semantic_status_msg_.inferred_target_station_name = last_inferred_target_station_name_;

  task_semantic_status_msg_.drive_mode = vehicle_info_msg_.mode;
  task_semantic_status_msg_.autoware_state = autoware_state_;
  task_semantic_status_msg_.task_distance = v2d_current_station_info_msg_.task_distance;
  task_semantic_status_msg_.target_distance = v2d_current_station_info_msg_.target_distance;
  task_semantic_status_msg_.near_done_active =
      vehicle_info_msg_.mode == ChassisInterfaceUtils::toInt8(DriveMode::AUTO_DONE_NEAR);
  task_semantic_status_msg_.near_done_condition_met =
      vehicle_info_msg_.spd <= 1 &&
      v2d_current_station_info_msg_.target_distance <= 50 &&
      vehicle_info_msg_.mode == ChassisInterfaceUtils::toInt8(DriveMode::AUTO_TAKEOVER_MANUAL);
  task_semantic_status_msg_.near_done_hold_until_sec = near_done_hold_until_sec_;
  task_semantic_status_msg_.near_done_remaining_sec =
      std::max(0.0, near_done_hold_until_sec_ - rclcpp::Clock(RCL_SYSTEM_TIME).now().seconds());

  task_semantic_status_msg_.summary =
      "lifecycle=" + task_semantic_status_msg_.lifecycle +
      ", decision=" + task_semantic_status_msg_.last_route_decision +
      ", latched=" + task_semantic_status_msg_.semantic_origin_station_name + "->" +
      task_semantic_status_msg_.semantic_target_station_name +
      ", inferred=" + task_semantic_status_msg_.inferred_current_station_name + "->" +
      task_semantic_status_msg_.inferred_target_station_name +
      ", near_done_active=" + std::string(task_semantic_status_msg_.near_done_active ? "true" : "false") +
      ", near_done_remaining=" + std::to_string(task_semantic_status_msg_.near_done_remaining_sec);
}

void PixmovingChassisInterfaceNode::applyLatchedTaskStationsToDisplay()
{
  int current_index = -1;
  int target_index = -1;
  std::string current_name;
  std::string target_name;
  {
    std::lock_guard<std::mutex> lock(task_semantic_mutex_);
    if (!has_task_semantic_ || semantic_origin_station_index_ < 0 || semantic_target_station_index_ < 0)
    {
      RCLCPP_WARN(this->get_logger(), "Skip applying latched task stations: semantic context is not ready");
      return;
    }
    current_index = semantic_origin_station_index_;
    target_index = semantic_target_station_index_;
    current_name = task_station_info_temp_.current_station_name;
    target_name = task_station_info_temp_.target_station_name;
  }

  setDisplayStationsFromIndexes(current_index, current_name, target_index, target_name);
}

bool PixmovingChassisInterfaceNode::shouldTreatAsNewTask(int route_target_station_index)
{
  std::lock_guard<std::mutex> lock(task_semantic_mutex_);
  if (!has_task_semantic_ || task_terminal_)
  {
    return true;
  }
  return route_target_station_index != semantic_target_station_index_;
}

void PixmovingChassisInterfaceNode::markTaskTerminal()
{
  std::lock_guard<std::mutex> lock(task_semantic_mutex_);
  if (!has_task_semantic_)
  {
    return;
  }
  task_terminal_ = true;
  pending_new_task_event_ = false;
  last_task_lifecycle_ = "terminal";
}

void PixmovingChassisInterfaceNode::onPlanGoal(const geometry_msgs::msg::PoseStamped::SharedPtr msg)
{
  last_current_target_station_ = current_target_station_;
  current_target_station_ = msg->pose.position;
}

void PixmovingChassisInterfaceNode::onLaneletRoute(const autoware_planning_msgs::msg::LaneletRoute::SharedPtr msg)
{
  last_staion_name = v2d_current_station_info_msg_.current_station.name;

  auto request_route_length = [this](bool is_new_task) {
    auto request = std::make_shared<get_osm_info_msgs::srv::GetPrimitiveLength::Request>();
    request->model = get_osm_info_msgs::srv::GetPrimitiveLength::Request::MULTIPLE_LANELET;
    const auto request_seq = ++route_length_request_seq_;

    planner_length_client_->async_send_request(
        request, [this, is_new_task, request_seq](
                     rclcpp::Client<get_osm_info_msgs::srv::GetPrimitiveLength>::SharedFuture result) {
          if (request_seq != route_length_request_seq_)
          {
            RCLCPP_DEBUG(this->get_logger(), "Ignore stale route length response seq=%lu", request_seq);
            return;
          }

          const auto& response = result.get();
          if (response->status == 1)
          {
            const auto route_length = static_cast<int32_t>(std::round(response->length));
            if (is_new_task)
            {
              v2d_current_station_info_msg_.task_distance = route_length;
            }
            v2d_current_station_info_msg_.target_distance = route_length;
            v2d_current_station_info_msg_.estimate_time =
                std::round(v2d_current_station_info_msg_.target_distance / planning_speed_mph_);
            RCLCPP_INFO(
                this->get_logger(), "route length updated: is_new_task=%d task_distance=%d target_distance=%d",
                static_cast<int>(is_new_task), v2d_current_station_info_msg_.task_distance,
                v2d_current_station_info_msg_.target_distance);
            return;
          }

          RCLCPP_ERROR(
              this->get_logger(),
              "[handle_distance_action]获取任务距离出错[2.0 到达目标的剩余距离无效,请运行[ros2 launch "
              "get_osm_info get_osm_info.launch.py]]");
          if (is_new_task)
          {
            v2d_current_station_info_msg_.task_distance = 0;
            v2d_current_station_info_msg_.target_distance = 0;
            v2d_current_station_info_msg_.estimate_time = 0;
          }
        });
  };

  auto handle_inferred_route = [this, request_route_length](
                                   int current_index, const std::string& current_name, int target_index,
                                   const std::string& target_name, const char* source) {
    if (current_index < 0 || target_index < 0 ||
        current_index >= static_cast<int>(station_yaml_list_obj_.size()) ||
        target_index >= static_cast<int>(station_yaml_list_obj_.size()))
    {
      RCLCPP_WARN(this->get_logger(), "%s returned invalid station index current=%d target=%d",
                  source, current_index, target_index);
      return;
    }

    const bool is_new_task = shouldTreatAsNewTask(target_index);
    bool should_trigger_new_task_event = false;
    {
      std::lock_guard<std::mutex> lock(task_semantic_mutex_);
      const bool had_active_task = has_task_semantic_ && !task_terminal_;
      const bool task_in_cancelable_mode =
          last_pixmoving_mode_ == ChassisInterfaceUtils::toInt8(DriveMode::AUTO_EXECUTING) ||
          last_pixmoving_mode_ == ChassisInterfaceUtils::toInt8(DriveMode::AUTO_TAKEOVER_MANUAL) ||
          last_pixmoving_mode_ == ChassisInterfaceUtils::toInt8(DriveMode::AUTO_TAKEOVER_BRAKE);
      should_trigger_new_task_event = is_new_task && had_active_task && task_in_cancelable_mode;
      pending_new_task_event_ = should_trigger_new_task_event;
    }

    if (is_new_task)
    {
      travel_distance_ = 0.0F;
      plan_status_ = true;
      latchTaskSemantic(current_index, current_name, target_index, target_name);
      applyLatchedTaskStationsToDisplay();
    }
    else
    {
      applyLatchedTaskStationsToDisplay();
    }

    request_route_length(is_new_task);
    updateTaskSemanticStatusDebug(
        "active", is_new_task ? "new_task" : "replan", source,
        current_index, current_name, target_index, target_name, should_trigger_new_task_event);

    RCLCPP_INFO(
        this->get_logger(),
        "%s classified route as %s: inferred_current=%s inferred_target=%s trigger_new_task_event=%d",
        source, is_new_task ? "new_task" : "replan", current_name.c_str(), target_name.c_str(),
        static_cast<int>(should_trigger_new_task_event));
  };

  auto apply_pose_matching_fallback = [this, msg, handle_inferred_route]() {
    int end_index = matchStationIndex(msg->goal_pose, "查询车辆终点信息");
    int start_index = matchStationIndex(msg->start_pose, "查询车辆起点信息");
    int8_t start_index_tmp = matchStationWithDistanceAndAngle(msg->start_pose);

    if (end_index < 0 && start_index < 0)
    {
      {
        std::lock_guard<std::mutex> lock(task_semantic_mutex_);
        pending_new_task_event_ = false;
      }
      v2d_current_station_info_msg_.target_station.id = 0;
      v2d_current_station_info_msg_.target_station.name = "";
      v2d_current_station_info_msg_.current_station.id = 0;
      v2d_current_station_info_msg_.current_station.name = "";
      updateTaskSemanticStatusDebug(
          "", "inference_failed", "pose_matching_fallback", -1, "", -1, "", false);
      RCLCPP_ERROR(this->get_logger(), "终点和起点-都没有找到, 请检查站点文件-[站点文件有误]");
      return;
    }

    if (end_index >= 0 && start_index < 0)
    {
      int inferred_start_index = start_index_tmp;
      if (inferred_start_index < 0)
      {
        inferred_start_index = end_index - 1;
        if (inferred_start_index < 0)
        {
          inferred_start_index = static_cast<int>(station_yaml_list_obj_.size()) - 1;
        }
        RCLCPP_WARN(this->get_logger(), "起点匹配不到，使用终点上一站作为当前站");
      }
      handle_inferred_route(
          inferred_start_index,
          station_yaml_list_obj_[inferred_start_index]["station_name"].as<std::string>(),
          end_index,
          station_yaml_list_obj_[end_index]["station_name"].as<std::string>(),
          "pose matching fallback");
      return;
    }

    if (end_index < 0 && start_index >= 0)
    {
      int end_index2 = start_index + 1;
      if (end_index2 >= static_cast<int>(station_yaml_list_obj_.size()))
      {
        end_index2 = 0;
      }
      RCLCPP_ERROR(this->get_logger(), "找到起点-没有找到终点, 使用下一站兜底");
      handle_inferred_route(
          start_index,
          station_yaml_list_obj_[start_index]["station_name"].as<std::string>(),
          end_index2,
          station_yaml_list_obj_[end_index2]["station_name"].as<std::string>(),
          "pose matching fallback");
      return;
    }

    handle_inferred_route(
        start_index,
        station_yaml_list_obj_[start_index]["station_name"].as<std::string>(),
        end_index,
        station_yaml_list_obj_[end_index]["station_name"].as<std::string>(),
        "pose matching fallback");
  };

  if (route_stations_client_ && route_stations_client_->service_is_ready())
  {
    auto station_request = std::make_shared<get_osm_info_msgs::srv::GetRouteStations::Request>();
    station_request->route = *msg;
    const auto request_seq = ++route_station_request_seq_;
    route_stations_client_->async_send_request(
        station_request,
        [this, request_seq, handle_inferred_route, apply_pose_matching_fallback](
            rclcpp::Client<get_osm_info_msgs::srv::GetRouteStations>::SharedFuture future) {
          if (request_seq != route_station_request_seq_)
          {
            RCLCPP_DEBUG(this->get_logger(), "Ignore stale route station response seq=%lu", request_seq);
            return;
          }

          try
          {
            const auto response = future.get();
            if (response &&
                response->status == get_osm_info_msgs::srv::GetRouteStations::Response::SUCCESS &&
                0 <= response->current_station_index && 0 <= response->target_station_index &&
                response->current_station_index < static_cast<int>(station_yaml_list_obj_.size()) &&
                response->target_station_index < static_cast<int>(station_yaml_list_obj_.size()))
            {
              handle_inferred_route(
                  response->current_station_index, response->current_station_name,
                  response->target_station_index, response->target_station_name,
                  "route station service");

              RCLCPP_INFO(this->get_logger(),
                          "route station service matched start=%s target=%s detail=%s",
                          response->current_station_name.c_str(),
                          response->target_station_name.c_str(),
                          response->detail.c_str());
              return;
            }

            if (response)
            {
              RCLCPP_WARN(this->get_logger(),
                          "route station service fallback: status=%d detail=%s",
                          response->status,
                          response->detail.c_str());
            }
            else
            {
              RCLCPP_WARN(this->get_logger(), "route station service returned null response");
            }
          }
          catch (const std::exception & e)
          {
            RCLCPP_WARN(this->get_logger(), "route station service exception: %s", e.what());
          }

          apply_pose_matching_fallback();
        });
    return;
  }

  apply_pose_matching_fallback();
}

void PixmovingChassisInterfaceNode::isTaskGoal()
{
  // 获取剩余的距离
  double remaining_distance = v2d_current_station_info_msg_.target_distance;

  // 使用实际速度 km/h → 转换 m/s
  double speed = v2d_vehicle_info_msg_.vehicle_speed_km_per_h / 3.6;

  constexpr double DIST_THRESHOLD = 20.0;  // 距离阈值 (米)
  constexpr double SPEED_THRESHOLD = 1.0;  // 速度阈值 (m/s)
  // 当距离小于阈值且速度小于阈值时，并且驾驶模式不是自驾时，认为到达终点
  if (remaining_distance < DIST_THRESHOLD && speed < SPEED_THRESHOLD &&
      autoware_state_ != autoware_system_msgs::msg::AutowareState::DRIVING)
  {
    // 到达终点 或者 停车
    // 这时需要搜索当前是否有站点，来上报当前所在站点
    if (localization_pose_ptr_ != nullptr)
    {
      int station_index = matchStationWithDistanceAndAngle(localization_pose_ptr_->pose);
      if (station_index >= 0)
      {
        v2d_current_station_info_msg_.current_station.id = station_index;  // 当前站点的ID
        v2d_current_station_info_msg_.current_station.name =
            station_yaml_list_obj_[station_index]["station_name"].as<std::string>();
        v2d_current_station_info_msg_.target_station.id = 0;
        v2d_current_station_info_msg_.target_station.name = "";
      }
      else
      {
        v2d_current_station_info_msg_.current_station.id = 0;
        v2d_current_station_info_msg_.current_station.name = "";
        v2d_current_station_info_msg_.target_station.id = 0;
        v2d_current_station_info_msg_.target_station.name = "";
      }
    }
  }
  else
  {
    // 检测是否从 非 DRIVING -> DRIVING
    if (last_autoware_state_ != autoware_system_msgs::msg::AutowareState::DRIVING &&
        autoware_state_ == autoware_system_msgs::msg::AutowareState::DRIVING)
    {
      v2d_current_station_info_msg_.current_station.id = task_station_info_temp_.current_station_index;  // 当前站点的ID
      v2d_current_station_info_msg_.current_station.name = task_station_info_temp_.current_station_name;
      v2d_current_station_info_msg_.target_station.id = task_station_info_temp_.target_station_index;
      v2d_current_station_info_msg_.target_station.name = task_station_info_temp_.target_station_name;

      RCLCPP_INFO(this->get_logger(), "进入DRIVING状态，更新站点信息");
      RCLCPP_INFO(this->get_logger(), "current_station_name:%s",
                  v2d_current_station_info_msg_.current_station.name.c_str());
      RCLCPP_INFO(this->get_logger(), "target_station_name:%s",
                  v2d_current_station_info_msg_.target_station.name.c_str());
    }
  }
  // 更新 last_autoware_state_
  last_autoware_state_ = autoware_state_;
}

}  // namespace interface
}  // namespace chassis
}  // namespace pixmoving
