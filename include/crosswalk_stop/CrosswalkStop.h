#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "opencv2/opencv.hpp"

#ifndef CROSSWALKSTOP_H
#define CROSSWALKSTOP_H

/**
*@brief Definition of the Parking class. It contains all the functions and variables depicted in the
*@brief Activity diagram and UML Class diagram.
*@brief It detects the lanes in an image if a highway and outputs the
*@brief same image with the plotted lane.
*/
class CrosswalkStop {
private:
	bool c_stop = false;
	unsigned int stop_count = 0;
	bool old_value = false;
	unsigned int PIXCEL_N = 16; // number of pixcel to check in stop_detect function.
	unsigned int STOP_THRES = 200; // critria of pixcel values
	unsigned int ROW_LOCATE = 85; // detect point of row axis. the location is the percentage of top to img raw's rows.
	unsigned int COL_LOCATE = 10; // detect point of column axis. the location is the percentage of top to img raw's clos.

public:
	cv::Mat mask(cv::Mat frame);
	bool detectstoppoint(cv::Mat img_filtered_,cv::Mat _img_bgr, int stop_change_count, int detect_layer);
	bool stop_detect(cv::Mat img_filtered, int detect_layer);
	void VisualizeCircle(cv::Mat _img_bgr, cv::Mat _img_filtered, int detect_layer);

};

#endif
