#include "ros/ros.h"
#include "sensor_msgs/Image.h"
#include <cv_bridge/cv_bridge.h>
#include <queue>

using namespace std;

namespace NaoExplorer
{
class ImagePublisher
{
	public:

	queue<cv_bridge::CvImagePtr> toPublish;

	ImagePublisher(ros::NodeHandle n, std::string topic)
		{
		image_pub = n.advertise<sensor_msgs::Image>(topic, 1000);
		count = 0;

		publishMsgs();
		}


	private:
	int count;
	ros::Publisher image_pub;

	void publishMsgs()
	{
		  ros::Rate loop_rate(10);
		  while (ros::ok())
		    {
			  while(!toPublish.empty())
			  {
				  cv_bridge::CvImagePtr image = toPublish.front();
				  toPublish.pop();
				  image_pub.publish(convertToRosImage(image));
			  }

			    ros::spinOnce();

			    loop_rate.sleep();
			    ++count;
		    }

	}

	sensor_msgs::Image convertToRosImage(cv_bridge::CvImagePtr image)
	{
	     ros::Time time = ros::Time::now();

	            // convert OpenCV image to ROS message
	            cv_bridge::CvImage cvi;
	            cvi.header.stamp = time;
	            cvi.header.frame_id = "image";
	            cvi.encoding = "bgr8";
	            cvi.image = image.get();
//
//	            // get camera parameters
//	            sensor_msgs::CameraInfo info = info_mgr.getCameraInfo();
//	            info.header.stamp = cvi.header.stamp;
//	            info.header.frame_id = cvi.header.frame_id; // whatever it is called
//	            info.width = cv_image.cols;
//	            info.height = cv_image.rows;

	            sensor_msgs::Image im;
	            cvi.toImageMsg(im);

	            return im;

	}
//	ros::init(argc, argv, "ImagePublisher");
//
//	ros::NodeHandle n;
//
//
//	  ros::Publisher image_pub = n.advertise<std_msgs::String>("chatter", 1000);
//
//
//
//	ros::spin();
//
//	return 0;
};
}


//#ifndef VISUALIZATION_H_
//#define VISUALIZATION_H_
//
//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
//
//using namespace cv;
//
//namespace NaoExplorer
//{
//
//class Window
//{
//private:
//	Mat image;
//
//public:
//	Window()
//	{
//		char window[] = "Blank Image";
//		image = Mat::zeros( 400, 400, CV_8UC3 );
//		imshow(window, image);
//		cvMoveWindow( window, 0, 200 );
//		waitKey( 0 );
//	}
//
//
//	void Update()
//	{
//		Point pt1(1,1);
//		Point pt2(20,20);
//		Scalar color = Scalar( 255, 255, 255 );
//		rectangle(image, pt1, pt2, color, -1);
//	}
//};
//}
//
//#endif /* VISUALIZATION_H_ */
