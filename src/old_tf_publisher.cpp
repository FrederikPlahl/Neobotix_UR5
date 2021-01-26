#include <ros/ros.h>
#include <tf2_ros/transform_listener.h>
#include <tf2_ros/transform_broadcaster.h>
#include <geometry_msgs/TransformStamped.h>

int main(int argc, char** argv){
  ros::init(argc, argv, "old_tf_publisher");
  ros::NodeHandle node;
  tf2_ros::Buffer tfBufferOdBaLi;
  tf2_ros::Buffer tfBufferBaLiBa;
  tf2_ros::Buffer tfBufferBaTo;
  tf2_ros::TransformListener tfListenerOdBaLi(tfBufferOdBaLi);
  tf2_ros::TransformListener tfListenerBaLiBa(tfBufferBaLiBa);
  tf2_ros::TransformListener tfListenerBaTo(tfBufferBaTo);
  

  ros::Rate rate(50.0);

  static tf2_ros::TransformBroadcaster br;

  geometry_msgs::TransformStamped tfSOdBaLi;
  geometry_msgs::TransformStamped tfSBaLiBa;
  geometry_msgs::TransformStamped tfSBaTo;
  try{

    tfSOdBaLi = tfBufferOdBaLi.lookupTransform("odom", "base_link", ros::Time(0), ros::Duration(0.5));
    tfSBaLiBa = tfBufferBaLiBa.lookupTransform("base_link", "base", ros::Time(0), ros::Duration(0.5));
    tfSBaTo = tfBufferBaTo.lookupTransform("base", "tool0_controller", ros::Time(0), ros::Duration(0.5));
  }
  catch (tf2::TransformException &ex) {
    ROS_WARN("%s",ex.what());
    ros::Duration(1.0).sleep();
  }
  

  tfSOdBaLi.header.frame_id = "odom";
  tfSOdBaLi.child_frame_id = "old_base_link";
  tfSBaLiBa.header.frame_id = "old_base_link";
  tfSBaLiBa.child_frame_id = "old_base";
  tfSBaTo.header.frame_id = "old_base";
  tfSBaTo.child_frame_id = "old_tool0_controller";

  while (node.ok()){  
    tfSOdBaLi.header.stamp = ros::Time::now();
    tfSBaLiBa.header.stamp = ros::Time::now();
    tfSBaTo.header.stamp = ros::Time::now();

    br.sendTransform(tfSOdBaLi);
    br.sendTransform(tfSBaLiBa);
    br.sendTransform(tfSBaTo);
    
    rate.sleep();
  }
  
  return 0; 
}
