#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/TransformStamped.h>
#include <tf2_ros/transform_listener.h>

geometry_msgs::PoseStamped transformToPose(geometry_msgs::TransformStamped transformStamped){
  geometry_msgs::PoseStamped poseStamped;

  poseStamped.header.stamp = transformStamped.header.stamp;
  poseStamped.header.frame_id = "base";

  poseStamped.pose.position.x = transformStamped.transform.translation.x;
  poseStamped.pose.position.y = transformStamped.transform.translation.y;
  poseStamped.pose.position.z = transformStamped.transform.translation.z;

  poseStamped.pose.orientation = transformStamped.transform.rotation;

  return(poseStamped);
};

int main(int argc, char** argv){
  ros::init(argc, argv, "target_publisher");
  ros::NodeHandle node;
  tf2_ros::Buffer tf2Buffer;
  tf2_ros::TransformListener tf2Listener(tf2Buffer);
  ros::Publisher pub = node.advertise<geometry_msgs::PoseStamped>("/ur5_cartesian_motion_controller/target_frame", 10);

  ros::Rate rate(50.0);

  geometry_msgs::TransformStamped tf2baseTargetStamped;
  while (node.ok()){
    try{
        tf2baseTargetStamped = tf2Buffer.lookupTransform("base", "old_tool0_controller", ros::Time(0), ros::Duration(0.5));
      }
    catch (tf2::TransformException &ex) {
        ROS_WARN("%s",ex.what());
        ros::Duration(1.0).sleep();
      }

      
    pub.publish(transformToPose(tf2baseTargetStamped));
    
    rate.sleep();
  }
  
  return 0;
}
