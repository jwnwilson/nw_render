#include "Light.h"

Light::Light()
{
	type=BASICL;
	lightRGB= ColourRGB(0.5,0.5,0.5);
}

Light::Light(const ColourRGB& a,const Vector3D& b)
{
	lightRGB= a;
	pos=b;
}
void Light::setPosition(const Vector3D& vert)
{
	pos=vert;

}


void Light::setColour(const ColourRGB& col)
{
	lightRGB=col;
}

Light::~Light(void)
{
}

bool Light::isSpot()const
{
	if(type==SPOTL)
	{
		return true;
	}
	return false;
}
bool Light::isPoint()const
{
	if(type==POINTL)
	{
		return true;
	}
	return false;
}
bool Light::isArea()const
{
	if(type==AREAL)
	{
		return true;
	}
	return false;
}
