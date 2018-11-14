#include "crosswalk_stop/CrosswalkStopNode.h"

using namespace std;
using namespace cv;

CrosswalkStopNode::CrosswalkStopNode()
	:as_(nh_,"crosswalk_stop", boost::bind(&CrosswalkStopNode::actionCallback, this, _1), false)
{
	nh_ = ros::NodeHandle("~");
	as_.start();
}


void CrosswalkStopNode::actionCallback(const u_turn::u_turnGoalConstPtr& goal)
{
	cout <<"crosswalk_stop actionCallback called" << endl;
	image_sub_ = nh_.subscribe("/usb_cam/image_raw", 1, &CrosswalkStopNode::imageCallback, this);
	mission_start = true;

	ros::Rate r(10);

	while(ros::ok()) {
		if(mission_cleared) {
			mission_start = false;
			u_turn::u_turnResult result;
			destroyAllWindows();
			as_.setSucceeded(result);
			break;
		}
		r.sleep();	// sleep 0.1 sec
	}
}
void CrosswalkStopNode::imageCallback(const sensor_msgs::ImageConstPtr& image)
{
	if(mission_start)
	{
	try{
		parseRawimg(image, frame);
	} catch(const cv_bridge::Exception& e) {
		ROS_ERROR("cv_bridge exception: %s", e.what());
		return ;
	} catch(const std::runtime_error& e) {
		cerr << e.what() << endl;
	}

	crosswalk_start();

/* ////////////////original code////////////////////
	//getRosParamForUpdate();
	//cout << "crosswalk_stop_node" << endl;
	bool x = parkingstart();
	cout << "x : " << x << endl;
	if(!parkingstart()){
			cout << "do lane detecting" << endl;
			steer_control_value_ = laneDetecting();
	}
	else{
		cout << "parking" << endl;
		steer_control_value_ = 0;
	}
//////////////////////////////////////////////// */

	}
}


void CrosswalkStopNode::getRosParamForUpdate()
{
}

bool CrosswalkStopNode::crosswalk_start()
{
	int throttle;
	int ncols = frame.cols;
	int nrows = frame.rows;

	int64 t1 = getTickCount();
	frame_count++;

	resize(frame, frame, Size(ncols / resize_n, nrows / resize_n));
	img_denoise = lanedetector.deNoise(frame);
	lanedetector.filter_colors(img_denoise, img_filtered);
/*
	//indoor test
	bitwise_not(img_mask2,img_mask2); // test for black white invert
*/
	img_mask = crosswalk_stop.mask(img_filtered);
	//imshow("original", frame);
	//imshow("color_filter", img_filtered);
	//imshow("img_filter", img_mask);

	cout << "crosswalk detect start" << endl;
	if(crosswalk_stop.detectstoppoint(img_mask, frame, 1, 2)){
		if(!mission_cleared){
				mission_cleared = true;
			}
		return true;
	}
	crosswalk_stop.VisualizeCircle(frame, img_mask, 2);

	int64 t2 = getTickCount();
	double ms = (t2 - t1) * 1000 / getTickFrequency();
	sum += ms;
	avg = sum / (double)frame_count;
	waitKey(3);

	return false;
}


void CrosswalkStopNode::parseRawimg(const sensor_msgs::ImageConstPtr& ros_img, cv::Mat& cv_img)
{
	cv_bridge::CvImagePtr cv_ptr = cv_bridge::toCvCopy(ros_img, sensor_msgs::image_encodings::BGR8);

	cv_img = cv_ptr->image;

	if (cv_img.empty()) {
		throw std::runtime_error("frame is empty!");
	}
}
