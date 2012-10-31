#include "sensor_msgs/Image.h"
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include "VectorHelper.h"
#include "Color.h"
#include "ros/ros.h"
#include <opencv2/core/core.hpp>

using namespace std;
using namespace cv;

namespace NaoExplorer
{
vector<bool> getMask(cv_bridge::CvImagePtr cvImagePtr, Color color, int threshold)
	{
	cv::Mat &mat = cvImagePtr -> image;


	int width = mat.cols;

	vector<bool>mask(width * mat.rows);

	for(int i = 0; i < mat.rows; i++)
	{
		for(int j = 0; j < width; j++)
		{
			cv::Vec3b pixel = mat.at<cv::Vec3b>(i,j);

			Color pixelColor(pixel[2], pixel[1], pixel[0]);

			if(pixelColor.compare(color) < threshold)
			{
				mask[VectorHelper::twoIndexToOne(i,j, width)] = true;
			}

		}
	}

	return mask;
	}


cv_bridge::CvImage maskToImage(vector<bool> mask, int imageWidth)
{
	cv_bridge::CvImage image;
	image.encoding = "bgr8";
	int width = imageWidth;
	int height = mask.size() / imageWidth;
	image.image = Mat::zeros(height, width, CV_8UC3 );


	for(int i = 0; i < mask.size(); i++)
	{
		if(mask[i])
		{
			vector<int>indexes = VectorHelper::oneIndexToTwo(i, width);
			image.image.at<cv::Vec3b>(indexes[0],indexes[1]) = Vec3b(255,255,255);
		}

	}

	//image.image.at<cv::Vec3b>(0,0) = Vec3b(255,255,255);

	return image;


}



string getPixel(cv_bridge::CvImagePtr cvImagePtr)
{
	cv::Mat &mat = cvImagePtr -> image;
		cv::Vec3b pixel = mat.at<cv::Vec3b>(0,0);


		stringstream convert;
		convert << int(pixel[2]) << int(pixel[1]) << int(pixel[0]);
		return convert.str();
}
}
