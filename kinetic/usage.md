#	USAGE for Kinetic user
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
Map files (map.pgm and map.yaml will be stored). The map files are crucial in future navigation tasks.
## How to navigate in Rviz
This function is implemented following the guide from GU YUE JU. 
Before we start, the navigation toolbox should be installed.

### Install navigation toolbox
I've tried the apt-get install ros-kinetic-navigation but somehow failed. If you meet the same problem ,
try install with source code:
https://blog.csdn.net/qq_33662195/article/details/85110154

### Rviz navigation
	roslaunch four_wheel_urdf four_wheel_arbotix.launch 
	roslaunch four_wheel_urdf my_navigation_rviz.launch 
If all right, click the "2D Nav Goal" button on top of Rviz and drag in on the map to specify both position and orientation.

`Some Bugs （crossing the wall） remain.`

##	How to navigate in Gazebo
The navigation toolbox is also required.

	roslaunch four_wheel_urdf diffdrive.launch
	roslaunch four_wheel_urdf my_navigation_gazebo.launch
Still use 2D Nav Goal to specify the pose, but this time the costmap will be updated using the data from lidar.

`However, odometr is not accurate so that there are errors in yaw angle.` 
	
