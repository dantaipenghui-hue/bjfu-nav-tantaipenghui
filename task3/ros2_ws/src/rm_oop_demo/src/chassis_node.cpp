#include "rm_oop_demo/chassis_node.hpp"

#include <chrono>
#include <cmath>
#include <memory>

#include "tf2/LinearMath/Quaternion.h"

namespace rm_oop_demo
{

ChassisNode::ChassisNode(const rclcpp::NodeOptions & options)
: Node("chassis_node", options)
{
  odom_frame_ = declare_parameter<std::string>("odom_frame", "odom");
  base_frame_ = declare_parameter<std::string>("base_frame", "base_link");
  const double publish_rate = declare_parameter<double>("publish_rate", 50.0);

  cmd_vel_sub_ = create_subscription<geometry_msgs::msg::Twist>(
    "cmd_vel", rclcpp::QoS(10),
    std::bind(&ChassisNode::cmdVelCallback, this, std::placeholders::_1));
  odom_pub_ = create_publisher<nav_msgs::msg::Odometry>("odom", rclcpp::QoS(10));
  marker_pub_ = create_publisher<visualization_msgs::msg::Marker>(
    "robot_visual", rclcpp::QoS(10));
  tf_broadcaster_ = std::make_unique<tf2_ros::TransformBroadcaster>(*this);

  last_update_time_ = now();
  timer_ = create_wall_timer(
    std::chrono::duration<double>(1.0 / publish_rate),
    std::bind(&ChassisNode::update, this));

  RCLCPP_INFO(
    get_logger(), "底盘节点已启动：订阅 /cmd_vel，发布 /odom 与 %s -> %s TF",
    odom_frame_.c_str(), base_frame_.c_str());
}

void ChassisNode::cmdVelCallback(const geometry_msgs::msg::Twist::SharedPtr msg)
{
  current_cmd_ = *msg;
  RCLCPP_INFO_THROTTLE(
    get_logger(), *get_clock(), 2000,
    "收到 /cmd_vel：线速度 %.2f m/s，角速度 %.2f rad/s",
    current_cmd_.linear.x, current_cmd_.angular.z);
}

void ChassisNode::update()
{
  const rclcpp::Time stamp = now();
  const double dt = first_update_ ? 0.0 : (stamp - last_update_time_).seconds();
  last_update_time_ = stamp;

  if (!first_update_ && dt > 0.0) {
    const double vx = current_cmd_.linear.x;
    const double vy = current_cmd_.linear.y;
    const double wz = current_cmd_.angular.z;

    x_ += (vx * std::cos(yaw_) - vy * std::sin(yaw_)) * dt;
    y_ += (vx * std::sin(yaw_) + vy * std::cos(yaw_)) * dt;
    yaw_ += wz * dt;
    yaw_ = std::atan2(std::sin(yaw_), std::cos(yaw_));
  }
  first_update_ = false;

  publishOdometry(stamp);
  publishTransform(stamp);
  publishMarker(stamp);
}

void ChassisNode::publishOdometry(const rclcpp::Time & stamp)
{
  nav_msgs::msg::Odometry odom;
  odom.header.stamp = stamp;
  odom.header.frame_id = odom_frame_;
  odom.child_frame_id = base_frame_;

  odom.pose.pose.position.x = x_;
  odom.pose.pose.position.y = y_;

  tf2::Quaternion orientation;
  orientation.setRPY(0.0, 0.0, yaw_);
  odom.pose.pose.orientation.x = orientation.x();
  odom.pose.pose.orientation.y = orientation.y();
  odom.pose.pose.orientation.z = orientation.z();
  odom.pose.pose.orientation.w = orientation.w();

  odom.twist.twist = current_cmd_;

  odom.pose.covariance[0] = 0.01;
  odom.pose.covariance[7] = 0.01;
  odom.pose.covariance[35] = 0.01;
  odom.twist.covariance[0] = 0.01;
  odom.twist.covariance[7] = 0.01;
  odom.twist.covariance[35] = 0.01;

  odom_pub_->publish(odom);
}

void ChassisNode::publishTransform(const rclcpp::Time & stamp)
{
  geometry_msgs::msg::TransformStamped transform;
  transform.header.stamp = stamp;
  transform.header.frame_id = odom_frame_;
  transform.child_frame_id = base_frame_;

  transform.transform.translation.x = x_;
  transform.transform.translation.y = y_;
  transform.transform.translation.z = 0.0;

  tf2::Quaternion orientation;
  orientation.setRPY(0.0, 0.0, yaw_);
  transform.transform.rotation.x = orientation.x();
  transform.transform.rotation.y = orientation.y();
  transform.transform.rotation.z = orientation.z();
  transform.transform.rotation.w = orientation.w();

  tf_broadcaster_->sendTransform(transform);
}

void ChassisNode::publishMarker(const rclcpp::Time & stamp)
{
  visualization_msgs::msg::Marker marker;
  marker.header.stamp = stamp;
  marker.header.frame_id = base_frame_;
  marker.ns = "chassis";
  marker.id = 0;
  marker.type = visualization_msgs::msg::Marker::CUBE;
  marker.action = visualization_msgs::msg::Marker::ADD;
  marker.pose.orientation.w = 1.0;
  marker.pose.position.z = 0.10;
  marker.scale.x = 0.60;
  marker.scale.y = 0.45;
  marker.scale.z = 0.30;
  marker.color.r = 0.1F;
  marker.color.g = 0.8F;
  marker.color.b = 0.2F;
  marker.color.a = 1.0F;
  marker.lifetime = rclcpp::Duration::from_seconds(0.2);

  marker_pub_->publish(marker);
}

}  // namespace rm_oop_demo

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<rm_oop_demo::ChassisNode>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
