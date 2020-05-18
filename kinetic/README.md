#	USAGE for Kinetic user
By Yu Zhuotong

Currently packages in kinetic workspace have implemented arbotiX diff_controllder, diffdrive controller in Gazebo, gmapping for constructing 2D maps for Gazebo world,and navigation in both Rviz and Gazeabo. The navigation toolbox is installed in the 
src folder of kinetic ws.
  
##	How to launch diffdrive controller
This is a built in controller of which the source code is not found.
	
To use it with out model, simply type:

	roslaunch four_wheel_urdf diffdrive.launch
This command will load the model and open both Rviz and Gazebo
## How to create 2D map
Here we use the diffdrive.launch for simplicity.
	
	roslaunch four_wheel_urdf diffdrive.launch
	roslaunch four_wheel_urdf gmapping_lidar.launch
or you can use kinect instead of lidar:

	roslaunch four_wheel_urdf gmapping_kinect.launch
Add map in Rviz and then use the steer interface to move the robot around.(Caution: do not collide with any obstacles)

When the map in Rviz becomes satisfactory, run the following:
	
	rosrun map_server map_saver
Map files (map.pgm and map.yaml will be stored). The map files are crucial in future navigation tasks. Maps are then stored under four_wheel_urdf/maps, be sure you have the correct path in launch files.
## How to navigate in Rviz
This function is implemented following the guide from GU YUE JU. 
Before we start, the navigation toolbox should be installed.

### Install navigation toolbox
Theoretically once you cloned this project the navigation toolbox will be download together with the kinetic workspace. You can choose to install on yourself.
I've tried the apt-get install ros-kinetic-navigation but somehow failed. If you meet the same problem ,
try install with source code:
https://blog.csdn.net/qq_33662195/article/details/85110154

### Rviz navigation
	roslaunch four_wheel_urdf four_wheel_arbotix.launch 
	roslaunch four_wheel_urdf my_navigation_rviz.launch 
If all right, click the "2D Nav Goal" button on top of Rviz and drag in on the map to specify both position and orientation.

##	How to navigate in Gazebo
The navigation toolbox is also required.

	roslaunch four_wheel_urdf diffdrive.launch
	roslaunch four_wheel_urdf my_navigation_gazebo.launch
Tricky thing is, if your move controller subscribes to `/XX/cmd_vel`,not directly `/cmd_vel`, you can go to `navigation/move_base/src/move_base.cpp` and change the pubshlish topic `/cmd_vel` into `/XX/cmd_vel` Then catkin_make. In our case, I make two targets with different names `move_base` and `move_base_four_wheel` pointing to `/cmd_vel` and `four_wheel_diff_controller/cmd_vel` respectively. You don't need to modify.

Still use 2D Nav Goal to specify the pose, but this time the costmap will be updated using the data from lidar.

`However, odometr is not accurate so that there are errors in yaw angle.` 

## About files in launch and config
### launch
`gazebo_new_world.launch` required by diffdrive.launch, help to build up Gazebo world.

`diffdrive.launch` for diffdrive control, which will switch on Rviz and Gazebo and a steering GUI.

`four_wheel_arbotix.launch` for ArbotiX diffdrive,which is only used in Rviz(no physical properties),and switch on nothing. Works in pair with "my_navigation_rviz.launch".

`gmapping_lidar.launch` calls gamapping for map generation base on lidar.

`gmapping_kinect.launch`calls gamapping for map generation base on kinect.

`my_move_base.launch` calls the move_base node and load bunches of parameters for navigation.

`my_navigation_gazebo.launch` calls my_move_base.launch and other navigation nodes to work with Gazebo environment.

`my_navigation_rviz.launch` calls my_move_base.launch and other navigation nodes to work with Rviz with no physics.

`display.launch` `gazebo.launch.bak` created by solidworks Exporter to urdf. No use now.

### config
`base_local_planner_params.yaml` `costmap_common_params.yaml` `global_costmap_params.yaml` `local_costmap_params.yaml` are parameters for navigation toolbox.

`diffdrive.yaml` and `joints.yaml`  for diffdrive controller

`four_wheel_arbotix.yaml` for ArbotiX diffdrive controller

`nav_config.rviz` config for Rviz in Rviz navigation

`joint_names_four_wheel_urdf.yaml` no use now, just keep it here







