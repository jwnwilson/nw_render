#include "Point.h"

Point::Point()
{
	x=0;
	y=0;
}
Point::Point(int a,int b,ColourRGB c)
{
	x=a;
	y=b;
	colour=c;
}
Point::Point(int a,int b)
{
	x=a;
	y=b;
}

Point Point::operator + (const Point& v)const
{
	Point temp2D(v.getX()+x,v.getY()+y);
	return temp2D;
}
Point Point::operator - (const Point& v)const
{
	Point temp2D(x-v.getX(),y-v.getY());
	return temp2D;
}
Point Point::operator * (const Point& v)const
{
	Point temp2D(x*v.getX(),y*v.getY());
	return temp2D;
}
Point Point::operator * (const float& v)const
{
	Point temp2D(x*v,y*v);
	return temp2D;
}

Point::~Point(void)
{
}

void Point::changeCoord(int a, int b)
{
	x=a;
	y=b;
}
