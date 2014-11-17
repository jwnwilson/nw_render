#pragma once
#include "light.h"

class LightSpot :
	public Light
{
public:
	LightSpot(void);
	~LightSpot(void);
	LightSpot(const ColourRGB&,const Vector3D&,const Vector3D&,const float&);
	// colour of light , position, direction of light, angle of cone.

	int getAttenExp()const{return attenExp;}
	Vector3D getAttenCo()const{return Vector3D(attenCo1,attenCo2,attenCo3);}
	Vector3D getInterest()const{return interest;}
	float getAngle()const{return angle;}

	void setInterest(const Vector3D& v);
	void setAngle(float f);
	void setAtten(const Vector3D&);
	void setAttenExp(int i){attenExp = i;}

private:
	Vector3D interest;
	float angle;
	int attenExp;
	float attenCo1,attenCo2,attenCo3;

};
