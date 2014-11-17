#pragma once
#include "light.h"

class LightPoint :
	public Light
{
public:
	LightPoint(void);
	LightPoint(const ColourRGB&,const Vector3D&);
	~LightPoint(void);

	Vector3D getAttenCo()const{return Vector3D(attenCo1,attenCo2,attenCo3);}
	void setAtten(const Vector3D&);

private:
	float attenCo1,attenCo2,attenCo3;
};
