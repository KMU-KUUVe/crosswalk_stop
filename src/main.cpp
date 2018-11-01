#include "ros/ros.h"
#include <iostream>
#include "crosswalk_stop/CrosswalkStopNode.h"
#include "opencv2/opencv.hpp"

int main(int argc, char** argv)
{
	ros::init(argc, argv, "crosswalk_stop");

#if 1	// using camera
	CrosswalkStopNode crosswalk_stop_node;

	ros::spin();

#else	// using mp4 file
	CrosswalkStopNode lane_detector_node("../challenge.mp4");

	lane_detector_node.run_test();

#endif

	return 0;
}
