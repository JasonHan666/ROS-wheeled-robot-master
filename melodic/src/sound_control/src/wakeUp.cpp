#include <ros/ros.h>
#include "std_msgs/String.h"

int main(int argc, char* argv[])
{
    ros::init(argc, argv, "wakeup_publisher");
	ros::NodeHandle n;
	ros::Rate loop_rate(10);

	ros::Publisher wakeUpPub = n.advertise<std_msgs::String>("voiceWakeup", 1000);

	while(ros::ok())
    {
        std_msgs::String msg;
        msg.data = "Data: 'any thing'";
        wakeUpPub.publish(msg);

        ros::spinOnce();
        loop_rate.sleep();
    }
}