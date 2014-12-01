#include "LightSpot.h"

LightSpot::LightSpot()
{
	lightRGB= ColourRGB();
	pos=Vector3D();
	interest=Vector3D();
	angle=(45*3.1415/180);
	attenCo1=1;
	attenCo2=0;
	attenCo3=0;
	attenExp=1;
	type=SPOTLIGHT;
}

LightSpot::LightSpot(const ColourRGB& a,const Vector3D& b,const Vector3D& c,const float& d)
{
	lightRGB= a;
	pos=b;
	interest=c;
	angle=(d*3.1415/180);
	//angle=d;
}
void LightSpot::setInterest(const Vector3D& v)
{
	interest = (v - pos).normalize();
}
void LightSpot::setAngle(float f)
{
	angle=(f*3.1415/180);
	//angle =f;
}
void LightSpot::setAtten(const Vector3D& v1)
{
	attenCo1=v1.x;
	attenCo2=v1.y;
	attenCo3=v1.z;
}

LightSpot::~LightSpot(void)
{
}
