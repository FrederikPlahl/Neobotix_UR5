# Neobotix_UR5

Using [cartesian_controllers][cc_link] and [Universal_Robots_ROS_Driver][driver_link] as a basis.
Make sure you have installed these correctly in your workspace.

The ```tf2_broadcaster.cpp``` publishes the fix transform from base_link to base.

![The neobotix platform with frames.][neo_transparent]

The ```old_tf_publisher.cpp``` publishes the transforms of all links at the moment of starting the node.

![The tf_tree from the neobotix platform.][tf_tree]

The ```target_frame_publisher.cpp``` calculates and publishes the target frame.

The ```debug_tool.cpp``` calculates the error between current and target pose and publishes it.

# Set up the controller:

1. In your ```Universal_Robots_ROS_Driver/ur_robot_driver/config/ ``` add [```ur5_cartesian_controllers.yaml```][ur5_cartesian_controllers.yaml] 

2. In your ```Universal_Robots_ROS_Driver/ur_robot_driver/launch/ ``` add [```ur5_cartesian_controllers_bringup.launch```][ur5_cartesian_controllers_bringup.launch], [```ur_common_cartesian.launch```][ur_common_cartesian.launch] and [```ur_control_cartesian.launch```][ur_control_cartesian.launch].

3. Build the packages in your workspace

```bash
$ cd ros_workspace
$ catkin_make
```

# Launch:
1. Start Neobotix PC and its autostart launch file

2. In a new terminal - Launch the driver and provide IP and kinematics configuration on Neobotix PC

```bash
$ roslaunch ur_robots_driver ur5_cartesian_bringup.launch robot_ip:=192.168.1.20 kinematics_config:=($ rospack find ur_calibration)/etc/hska_ur5_calibration.yaml
```

3. Start ```ROS_external_control``` on UR5 touchpad --> driver terminal should confirm with ```Robot ready to receive control commands```

4. In a new terminal - Launch nodes for calculating and publishing the target frame

```bash
$ roslaunch hska_neo hold_tcp.launch
```

# For evaluation:
1. In a new terminal

```bash
$ roslaunch hska_neo debug.launch
```

This should open a window plotting the distance between current and target pose of the endeffector.

[neo_transparent]: etc/neo_transparent.png "The neobotix platform with frames."
[tf_tree]: etc/tf_tree.png "The tf_tree from the neobotix platform."
[ur5_cartesian_controllers.yaml]: config/ur5_cartesian_controllers.yaml "The controllers config."
[ur5_cartesian_controllers_bringup.launch]: launch/ur5_cartesian_controllers_bringup.launch "The launch file for the driver."
[ur_common_cartesian.launch]: launch/ur_common_cartesian.launch "The common-launch file for the driver."
[ur_control_cartesian.launch]: launch/ur_control_cartesian.launch "The control-launch file for the driver."
[cc_link]: https://github.com/fzi-forschungszentrum-informatik/cartesian_controllers "cartesian_controllers from FZI"
[driver_link]: https://github.com/UniversalRobots/Universal_Robots_ROS_Driver "Universal_Robots_ROS_Driver from FZI"
