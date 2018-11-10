#include "ros/ros.h"
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "opencv2/opencv.hpp"
#include "lane_detector/LaneDetector.h"
#include "crosswalk_stop/CrosswalkStop.h"
#include <std_msgs/String.h>
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>
#include <sensor_msgs/image_encodings.h>
#include <ackermann_msgs/AckermannDriveStamped.h>
#include <signal.h>
#include <actionlib/server/simple_action_server.h>
#include <u_turn/u_turnAction.h>

#ifndef CrosswalkStopNode_H
#define CrosswalkStopNode_H

#define resize_n 1 // variable for image(frame) resize
#define Mask_method 0 // method 0 :
// method 1 :

class CrosswalkStopNode
{
	public:
		CrosswalkStopNode();

		void imageCallback(const sensor_msgs::ImageConstPtr& image);
		void actionCallback(const u_turn::u_turnGoalConstPtr& goal);

	protected:
		
		void getRosParamForUpdate();
		void parseRawimg(const sensor_msgs::ImageConstPtr& ros_img, cv::Mat& cv_img);
		bool crosswalk_start();


	protected:
		ros::NodeHandle nh_;
		ros::Publisher control_pub_;	// Controll 메시지를 Publish하는 Publisher
		ros::Subscriber image_sub_;		// 가공되지 않은 raw image 메시지를 Subscribe하는 Subscriber
		actionlib::SimpleActionServer<u_turn::u_turnAction> as_;

		bool mission_cleared = false;
		bool mission_start = false;
		LaneDetector lanedetector;  // Create the class object
		CrosswalkStop crosswalk_stop;

		cv::Mat frame;
		cv::Mat img_denoise;
		cv::Mat img_mask;
		cv::Mat img_filtered;

		double avg = 0;
		double sum = 0;
		int frame_count = 0;

		bool cwross_stop = false;
		int throttle_ = 3;
		int steer_control_value_= 0;
		cv::String test_video_path = "";
};

#endif
