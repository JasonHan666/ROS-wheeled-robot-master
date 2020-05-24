#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "qisr.h"
#include "msp_cmn.h"
#include "msp_errors.h"
#include "speech_recognizer.h"

#include <ros/ros.h>
#include "std_msgs/String.h"
#include <geometry_msgs/Twist.h> // For geometry_msgs::Twist
#include <sstream>

#define FRAME_LEN	640 
#define	BUFFER_SIZE	4096

int wakeupFlag = 0;
int resultFlag = 0;

int actionMode = 0;


static void show_result(char *string, char is_over)
{
	printf("\rResult: [ %s ]", string);
	if(is_over)
		putchar('\n');
}

static char *g_result = NULL;
static unsigned int g_buffersize = BUFFER_SIZE;

void on_result(const char *result, char is_last)
{
	if (result) {
		size_t left = g_buffersize - 1 - strlen(g_result);
		size_t size = strlen(result);
		if (left < size) {
			g_result = (char*)realloc(g_result, g_buffersize + BUFFER_SIZE);
			if (g_result)
				g_buffersize += BUFFER_SIZE;
			else {
				printf("mem alloc failed\n");
				return;
			}
			// 分配空间
		}
		strncat(g_result, result, size); //向g_result追加result前size个字符
		show_result(g_result, is_last);
		if(!strcmp(g_result, "向前") || !strcmp(g_result, "前进")){
			ROS_INFO("forward recognized");
			actionMode = 1;
		}else if(!strcmp(g_result, "向后") || !strcmp(g_result, "后退")){
			ROS_INFO("backward recognized");
			actionMode = 2;
		}else if(!strcmp(g_result, "向左") || !strcmp(g_result, "左转")){
			ROS_INFO("turn left recognized");
			actionMode = 3;
		}else if(!strcmp(g_result, "向右") || !strcmp(g_result, "右转")){
			ROS_INFO("turn right recognized");
			actionMode = 4;
		}else if(!strcmp(g_result, "停止") || !strcmp(g_result, "停")){
			ROS_INFO("stop recognized");
			actionMode = 0;
		}
	}
}

void on_speech_begin()
{
	if (g_result)
	{
		free(g_result);
	}
	g_result = (char*)malloc(BUFFER_SIZE);
	g_buffersize = BUFFER_SIZE;
	memset(g_result, 0, g_buffersize);

	ROS_INFO("Start Listening...");
}

void on_speech_end(int reason)
{
	if (reason == END_REASON_VAD_DETECT)
		ROS_INFO("Speaking done.");
	else
		printf("\nRecognizer error %d\n", reason);
}

/* demo recognize the audio from microphone */
static void demo_mic(const char* session_begin_params)
{
	int errcode;
	int i = 0;

	struct speech_rec iat;

	struct speech_rec_notifier recnotifier = {
		on_result,
		on_speech_begin,
		on_speech_end
	};

	errcode = sr_init(&iat, session_begin_params, SR_MIC, &recnotifier);
	if (errcode) {
		printf("speech recognizer init failed\n");
		return;
	}
	errcode = sr_start_listening(&iat);
	if (errcode) {
		printf("start listen failed %d\n", errcode);
	}
	/* demo 15 seconds recording */
	while(i++ < 3)
		sleep(1);
	errcode = sr_stop_listening(&iat);
	if (errcode) {
		printf("stop listening failed %d\n", errcode);
	}

	sr_uninit(&iat);
}

void WakeUp(const std_msgs::String::ConstPtr& msg)
{
    ROS_INFO("Waking up...");
    usleep(700*1000);
    wakeupFlag = 1;
}

int main(int argc, char* argv[])
{
	ros::init(argc, argv, "voice_recognition");
	ros::NodeHandle n;
	ros::Rate loop_rate(20);

	ros::Subscriber wakeUpSub = n.subscribe("voiceWakeup", 1000, WakeUp);

	//ros::Publisher voiceWordsPub = n.advertise<std_msgs::String>("voiceWords", 1000);
	ros::Publisher voiceWordsPub = n.advertise<geometry_msgs::Twist>("four_wheel_diff_drive_controller/cmd_vel", 20);

	ROS_INFO("Sleeping...");

	while(ros::ok())
	{
		ROS_INFO("wakeupFlag: %d",wakeupFlag);
		if(wakeupFlag == 0)
		{
		ros::spinOnce();
		loop_rate.sleep();
		}
		else
		{
			ROS_INFO("Waking up sueecssfully!");
			int ret = MSP_SUCCESS;
			const char* login_params = "appid = 5eb8ad7d, work_dir = .";
			
			const char* session_begin_params =
					"sub = iat, domain = iat, language = zh_cn, "
					"accent = mandarin, sample_rate = 16000, "
					"result_type = plain, result_encoding = utf8";

			/* Login first. the 1st arg is username, the 2nd arg is password.
	 		 * Just set them as NULL. the 3rd arg is login paramertes 
	 		 * */
			ret = MSPLogin(NULL, NULL, login_params);
			if(MSP_SUCCESS != ret)
			{
				MSPLogout();
				printf("MSPLogin failed , Error code %d.\n",ret);
			}

			ROS_INFO("Demo recognizing the speech from microphone.");
			ROS_INFO("Speak in 10 seconds.");
			
			demo_mic(session_begin_params);
			
			ROS_INFO("10 sec passed.");
			
			wakeupFlag = 0;
			MSPLogout();
			resultFlag = 1;
		}

		if(resultFlag)
		{
			resultFlag = 0;
			//std_msgs::String msg;
			//msg.data = g_result;
			geometry_msgs::Twist msg;
			msg.angular.z = 0;
			msg.linear.x = 0;
			// set the value of the vel by actionMode, 1:forward, 3:left
			switch(actionMode){
				case 1: msg.linear.x = 0.35;
					msg.angular.z = 0;
				break;
				case 2: msg.linear.x = -0.35;
					msg.angular.z = 0;
				break;
				case 3: msg.angular.z = 0.45;
					msg.linear.x = 0;
				break;
				case 4: msg.angular.z = -0.45;
					msg.linear.x = 0;
				break;
				case 0: msg.linear.x = 0;
					msg.angular.z = 0;
				break;
			}
			voiceWordsPub.publish(msg);
			wakeupFlag = 1;
		}
		//ros::spinOnce();
		loop_rate.sleep();
	}
}
