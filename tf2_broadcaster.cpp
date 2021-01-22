#include <ros/ros.h>
#include <tf2_ros/transform_broadcaster.h>
#include <geometry_msgs/TransformStamped.h>
#include <tf2/LinearMath/Quaternion.h>
#define _USE_MATH_DEFINES

int main(int argc, char** argv){
  ros::init(argc, argv, "baseBase_link_broadcaster");

  static tf2_ros::TransformBroadcaster br;
  geometry_msgs::TransformStamped transformStamped;
  ros::NodeHandle node;
  ros::Rate rate(120.0);
  while (node.ok()){
    transformStamped.header.stamp = ros::Time::now();
    transformStamped.header.frame_id = "base_link";
    transformStamped.child_frame_id = "base";
    transformStamped.transform.translation.x = 0.18;
    transformStamped.transform.translation.y = 0;
    transformStamped.transform.translation.z = 0.805;
    tf2::Quaternion q;
    q.setRPY(0, 0, M_PI_2);
    transformStamped.transform.rotation.x = q.x();
    transformStamped.transform.rotation.y = q.y();
    transformStamped.transform.rotation.z = q.z();
    transformStamped.transform.rotation.w = q.w();

    br.sendTransform(transformStamped);
    rate.sleep();
  }
  return 0;
  
}