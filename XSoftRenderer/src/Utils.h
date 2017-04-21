/*
 * Utils.h
 *
 *  Created on: Feb 6, 2017
 *      Author: coder
 */

#ifndef UTILS_H_
#define UTILS_H_

union RGBA
{
	unsigned long int dword;
    unsigned char RGBA[4];
    struct _RGBAstruct
    {
        unsigned char b;
        unsigned char g;
        unsigned char r;
        unsigned char a;
    } RGBAstruct;
};

class PointF
{
public:
	PointF(float x, float y, float z)
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}
	PointF(float x, float y)
		{
			this->x = x;
			this->y = y;
			this->z = 0;
		}
	PointF ()
	{
		this->x = 0;
		this->y = 0;
		this->z = 0;
	}

public:
	float x;
	float y;
	float z;
};

class Point
{
public:
	Point(int x, int y, int z)
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}
	Point(int x, int y)
		{
			this->x = x;
			this->y = y;
			this->z = 0;
		}
	Point ()
	{
		this->x = 0;
		this->y = 0;
		this->z = 0;
	}

public:
	int x;
	int y;
	int z;
};

#endif /* UTILS_H_ */
