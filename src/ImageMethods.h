#include "sensor_msgs/Image.h"
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>

using namespace std;

namespace NaoExplorer
{
//vector<bool> getMask(cv_bridge::CvImagePtr cvImagePtr, Color color, int threshold)
//				{
//	cv::Mat &mat = cvImagePtr -> image;
//	cv::Vec3b pixel = mat.at<cv::Vec3b>(0,0);
//
//	ROS_INFO("image[%d,%d] = (r=%d,g=%d,b=%d)",
//	0, 0, pixel[2], pixel[1], pixel[0]);
//
//
//	return vector();
//				}


string getPixel(cv_bridge::CvImagePtr cvImagePtr)
{
	cv::Mat &mat = cvImagePtr -> image;
		cv::Vec3b pixel = mat.at<cv::Vec3b>(0,0);


		stringstream convert;
		convert << int(pixel[2]) << int(pixel[1]) << int(pixel[0]);
		return convert.str();
}
}
