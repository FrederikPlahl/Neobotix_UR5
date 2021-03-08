#include <ros/ros.h>
#include <tf2_ros/transform_listener.h>
#include <geometry_msgs/TransformStamped.h>
#include <geometry_msgs/Vector3.h>
#include <std_msgs/Float64.h>

double length(geometry_msgs::Vector3 vector){
    double length;
    length = sqrt(pow(vector.x, 2)+pow(vector.y, 2)+pow(vector.z, 2));

    return(length);
}

int main(int argc, char** argv){
  ros::init(argc, argv, "debug_tool");
  ros::NodeHandle node;
  tf2_ros::Buffer tfBuffer_toolTarget;
  tf2_ros::TransformListener tfListenerBaseTool(tfBuffer_toolTarget);
  
  ros::Publisher pub = node.advertise<std_msgs::Float64>("/ur5_cartesian_motion_controller/debug_tool", 1);

  ros::Rate rate(50.0);
  
  while (node.ok()){
        geometry_msgs::TransformStamped tf_toolTarget;
        try{

            tf_toolTarget = tfBuffer_toolTarget.lookupTransform("tool0_controller", "old_tool0_controller", ros::Time(0), ros::Duration(1.0));
        }
        catch (tf2::TransformException &ex) {
            ROS_WARN("%s",ex.what());
            ros::Duration(1.0).sleep();
        }
        
        geometry_msgs::Vector3 vec_toolTarget;
        vec_toolTarget.x = tf_toolTarget.transform.translation.x;
        vec_toolTarget.y = tf_toolTarget.transform.translation.y;
        vec_toolTarget.z = tf_toolTarget.transform.translation.z;

        pub.publish(length(vec_toolTarget));
    }

    return 0;
}