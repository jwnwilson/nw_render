#include "Light.h"

Light::Light()
{
	type=BASICLIGHT;
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
	if(type==SPOTLIGHT)
	{
		return true;
	}
	return false;
}
bool Light::isPoint()const
{
	if(type==POINTLIGHT)
	{
		return true;
	}
	return false;
}
bool Light::isArea()const
{
	if(type==AREALIGHT)
	{
		return true;
	}
	return false;
}
