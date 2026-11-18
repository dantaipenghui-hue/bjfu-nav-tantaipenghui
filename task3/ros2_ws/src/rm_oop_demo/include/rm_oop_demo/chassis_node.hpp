#ifndef RM_OOP_DEMO__CHASSIS_NODE_HPP_
#define RM_OOP_DEMO__CHASSIS_NODE_HPP_

#include <memory>
#include <string>

#include "geometry_msgs/msg/twist.hpp"
#include "nav_msgs/msg/odometry.hpp"
#include "rclcpp/rclcpp.hpp"
#include "tf2_ros/transform_broadcaster.h"
#include "visualization_msgs/msg/marker.hpp"

namespace rm_oop_demo
{

/// 底盘节点：订阅 /cmd_vel，对速度积分得到位姿，发布 /odom 与 odom -> base_link 的 TF。
class ChassisNode : public rclcpp::Node
{
public:
  explicit ChassisNode(const rclcpp::NodeOptions & options = rclcpp::NodeOptions());

private:
  void cmdVelCallback(const geometry_msgs::msg::Twist::SharedPtr msg);
  void update();
  void publishOdometry(const rclcpp::Time & stamp);
  void publishTransform(const rclcpp::Time & stamp);
  void publishMarker(const rclcpp::Time & stamp);

  rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr cmd_vel_sub_;
  rclcpp::Publisher<nav_msgs::msg::Odometry>::SharedPtr odom_pub_;
  rclcpp::Publisher<visualization_msgs::msg::Marker>::SharedPtr marker_pub_;
  std::unique_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster_;
  rclcpp::TimerBase::SharedPtr timer_;

  geometry_msgs::msg::Twist current_cmd_;
  rclcpp::Time last_update_time_;
  double x_{0.0};
  double y_{0.0};
  double yaw_{0.0};
  bool first_update_{true};

  std::string odom_frame_;
  std::string base_frame_;
};

}  // namespace rm_oop_demo

#endif  // RM_OOP_DEMO__CHASSIS_NODE_HPP_
