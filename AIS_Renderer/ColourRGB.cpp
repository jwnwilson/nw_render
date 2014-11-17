#include "ColourRGB.h"

ColourRGB::ColourRGB(void)
{
	red=0.0f;
	green=0.0f;
	blue=0.0f;
}

ColourRGB::ColourRGB(float r, float g, float b)
{
	red=r;
	green=g;
	blue=b;
}
bool ColourRGB::operator ==(const ColourRGB& c)const
{
	if(red==c.getRed() && green== c.getGreen() && blue ==c.getBlue())
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool ColourRGB::operator !=(const ColourRGB& c)const
{
	if(red!=c.getRed() || green!= c.getGreen() || blue !=c.getBlue())
	{
		return true;
	}
	else
	{
		return false;
	}
}

ColourRGB ColourRGB::operator + (const ColourRGB& add)const
{
	float r,g,b;
	r=red+add.getRed();
	g=green+add.getGreen();
	b=blue+add.getBlue();
	ColourRGB col(r,g,b);

	col.clamp();

	return col;
}

ColourRGB ColourRGB::operator * (const ColourRGB& mult)const
{
	float r,g,b;
	r=red*mult.getRed();
	g=green*mult.getGreen();
	b=blue*mult.getBlue();
	ColourRGB col(r,g,b);

	col.clamp();

	return col;
}
ColourRGB   ColourRGB::operator * (const float& f)const
{
	float r,g,b;
	r=red*f;
	g=green*f;
	b=blue*f;
	ColourRGB col(r,g,b);

	col.clamp();

	return col;
}

ColourRGB ColourRGB::operator - (const ColourRGB& sub)const
{
	float r,g,b;
	r=red-sub.getRed();
	g=green-sub.getGreen();
	b=blue-sub.getBlue();
	ColourRGB col(r,g,b);

	col.clamp();

	return col;
}

void ColourRGB::clamp()
{
	if(red>1)
	{
		red=1;
	}
	else if(red<0)
	{
		red=0;
	}

	if(green>1)
	{
		green=1;
	}
	else if(green<0)
	{
		green=0;
	}

	if(blue>1)
	{
		blue=1;
	}
	else if(blue<0)
	{
		blue=0;
	}
}

void ColourRGB::scale(float scal)
{
	red=red*scal;
	green=green*scal;
	blue=blue*scal;
	clamp();
}

ColourRGB  ColourRGB::modulate(const ColourRGB& col)const
{
	ColourRGB temp((red*col.red),(green*col.green),blue*col.blue);
	return temp;
}	

ColourRGB::~ColourRGB(void)
{
}
