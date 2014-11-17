#pragma once
#include "ColourRGB.h"

// Point class used to store a 2D co-ord and pixel colour

class Point
{
public:
	Point();
	Point(int,int);
	Point(int,int,ColourRGB);
	void changeCoord(int, int);
	int getX() const{return x;}
	int getY() const{return y;}
	ColourRGB getColour()const{return colour;}
	void setX(int i){x=i;}
	void setY(int i){y=i;}
	void setCol(ColourRGB col){colour=col;}
	
	~Point(void);

	Point operator + (const Point&)const;
	Point operator - (const Point&)const;
	Point operator * (const Point&)const;
	Point operator * (const float&)const;
private:
	int x, y;
	ColourRGB colour;
};
