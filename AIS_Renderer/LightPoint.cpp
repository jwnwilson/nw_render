#include "LightPoint.h"

LightPoint::LightPoint(void)
{
	lightRGB= ColourRGB();
	pos=Vector3D();
	attenCo1=1.0f;
	attenCo2=0.0f;
	attenCo3=0.0f;
	type=POINTLIGHT;
}

LightPoint::~LightPoint(void)
{
}
LightPoint::LightPoint(const ColourRGB& a,const Vector3D& b)
{
	lightRGB= a;
	pos=b;
}
void LightPoint::setAtten(const Vector3D& v1 )
{
	attenCo1=v1.x;
	attenCo2=v1.y;
	attenCo3=v1.z;
}
