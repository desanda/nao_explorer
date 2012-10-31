#ifndef COLOR_H_
#define COLOR_H_

#include "ColorConversion.h"
#include "ros/ros.h"

typedef unsigned char byte;
class Color {
public:
	byte r;
	byte g;
	byte b;

	Color(byte r, byte g, byte b)
	{
		this->r = r;
		this->g = g;
		this->b = b;
	}


	int compare(Color two)
	{

		hsv_color hsvOne = rgb_to_hsv(convertToConversionType(*this));
		hsv_color hsvTwo = rgb_to_hsv(convertToConversionType(two));

		ROS_INFO("HSV Color 1 %d", hsvOne);
		ROS_INFO("HSV Color 2 %d", hsvTwo);



		//sqrt((R-0)^2 + (G-255)^2 + (B-0)^2)

		int redDiff   = abs((int)(r) - (int)(two.r));
		int greenDiff = abs((int)(g) - (int)(two.g));
		int blueDiff  = abs((int)(b) - (int)(two.b));

		return sqrt(pow(redDiff,2) + pow(greenDiff,2) + pow(blueDiff,2));
	}

	rgb_color convertToConversionType(Color c)
	{
		rgb_color color;
		color.r = c.r;
		color.b = c.b;
		color.g = c.g;
	}




};

#endif
