#include "StdAfx.h"
#include "SpotLight.h"

SpotLight::SpotLight()
{
	lightRGB= ColourRGB();
	pos=Vector3D();
	interest=Vector3D();
	angle=(45*3.1415/180);
	attenCo1=1;
	attenCo2=0;
	attenCo3=0;
	attenExp=1;
	type = 1;
}

SpotLight::SpotLight(const ColourRGB& a,const Vector3D& b,const Vector3D& c,const float& d)
{
	lightRGB= a;
	pos=b;
	interest=c;
	angle=(d*3.1415/180);
	//angle=d;
}
void SpotLight::setAngle(float f)
{
	angle=(f*3.1415/180);
	//angle =f;
}
void SpotLight::setAtten(float a,float b,float c)
{
	attenCo1=a;
	attenCo2=b;
	attenCo3=c;
}
bool SpotLight::isSpot() const
{
	return true;
}
bool SpotLight::isPoint()const
{
	return false;
}
void SpotLight::setAtten(float a)
{
	attenExp=a;
}

SpotLight::~SpotLight(void)
{
}
