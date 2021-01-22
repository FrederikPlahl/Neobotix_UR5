# Neobotix_UR5

Using [cartesian_controllers][cc_link] and [Universal_Robots_ROS_Driver][driver_link] as a basis.
You need to have these in your workspace.

The ```tf2_broadcaster.cpp``` publishes the fix transform from base_link to base.

![The neobotix platform with frames.][neo_transparent]

The ```old_tf_publisher.cpp``` publishes the transforms of all links at the moment of starting the node.

![The tf_tree from the neobotix platform.][tf_tree]

In your ```.../config/``` add ```!!!!The cartesian config yaml file!!!!```.
To run ur driver launch ur5_cartesian_bringup.launch. This launches the controllers and starts them after running the ```external_ROS_control``` program on the UR5.
Start ```tf2_broadcaster.cpp``` and ```old_tf_publisher.cpp``` manually (.launch file is following) for publishing the necessary transforms.
Start ```target_frame_publisher.cpp```for publishing the pose of the target to the cartesian controller.

[neo_transparent]: etc/neo_transparent.png "The neobotix platform with frames."
[tf_tree]: etc/tf_tree.png "The tf_tree from the neobotix platform."
[cc_link]: https://github.com/fzi-forschungszentrum-informatik/cartesian_controllers "cartesian_controllers from FZI"
[driver_link]: https://github.com/UniversalRobots/Universal_Robots_ROS_Driver "Universal_Robots_ROS_Driver from FZI"
