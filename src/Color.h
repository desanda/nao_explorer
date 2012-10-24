#ifndef COLOR_H_
#define COLOR_H_

typedef char byte;
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
		//sqrt((R-0)^2 + (G-255)^2 + (B-0)^2)

		int redDiff   = abs((int)(r) - (int)(two.r));
		int greenDiff = abs((int)(g) - (int)(two.g));
		int blueDiff  = abs((int)(b) - (int)(two.b));

		return sqrt(pow(redDiff,2) + pow(greenDiff,2) + pow(blueDiff,2));
	}


};

#endif
