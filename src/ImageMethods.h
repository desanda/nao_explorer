#include "sensor_msgs/Image.h"
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include "VectorHelper.h"
#include "ros/ros.h"
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
using namespace cv_bridge;

namespace NaoExplorer
{
//TODO: Pass CV Scalars
cv_bridge::CvImagePtr getMask(cv_bridge::CvImagePtr cvImagePtr)
	{
	Mat mat = cvImagePtr -> image;
	//CvMat oldMat = mat;
	IplImage originalImage = mat;
	IplImage *hsvImage = cvCreateImage(cvGetSize(&originalImage), 8, 3);
	IplImage* imgThreshed = cvCreateImage(cvGetSize(&originalImage), 8, 1);

	cvCvtColor(&originalImage, hsvImage, CV_BGR2HSV);

	cvInRangeS(hsvImage, cvScalar(15, 153, 127), cvScalar(30, 255, 255), imgThreshed);
//
//	int width = mat.cols;
//
//	vector<bool>mask(width * mat.rows);
//
//	for(int i = 0; i < mat.rows; i++)
//	{
//		for(int j = 0; j < width; j++)
//		{
//			cv::Vec3b pixel = hsvImage->imageData-
//
//
//
//			if(pixelColor.compare(color) < threshold)
//			{
//				mask[VectorHelper::twoIndexToOne(i,j, width)] = true;
//			}
//
//		}
//	}

	//ROS_INFO(imgThreshed->colorModel);

	Mat mask(imgThreshed);

	CvImagePtr imagePointer(new CvImage);

	mask.copyTo(imagePointer->image);

	//ROS_INFO(imagePointer->encoding.c_str());

	imagePointer->encoding= string("mono8");


	return imagePointer;
	}


CvImagePtr resizeImage(CvImagePtr inputImage, int width, int height)
{
	Mat mat = inputImage -> image;
	IplImage originalImage = mat;

	CvSize resizedImageSize;
	resizedImageSize.width = width;
	resizedImageSize.height = height;

	IplImage* resizedImage = cvCreateImage(resizedImageSize, 8, 1);
	//TODO:Play around with samping option paramaters on cvResize
	cvResize(&originalImage, resizedImage);

	CvImagePtr imagePointer(new CvImage);
	Mat resizedImageMatrix(resizedImage);

	resizedImageMatrix.copyTo(imagePointer->image);
	imagePointer->encoding= string("mono8");

	return imagePointer;

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
