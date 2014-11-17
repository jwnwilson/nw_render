#pragma once
#include "light.h"

class SpotLight :
	public Light
{
public:
	SpotLight(void);
	~SpotLight(void);
	SpotLight(const ColourRGB&,const Vector3D&,const Vector3D&,const float&);
	// colour of light , position, direction of light, angle of cone.

	float getAttenExp()const{return attenExp;}
	Vector3D getInterest()const{return interest;}
	float getAngle()const{return angle;}

	bool isSpot()const;
	bool isPoint()const;
	void setInterest(const Vector3D v){interest=v;}
	void setAtten(float);
	void setAngle(float);
	float getAttenCo1()const{return attenCo1;}
	float getAttenCo2()const{return attenCo2;}
	float getAttenCo3()const{return attenCo3;}

	void setAtten(float,float,float);

private:
	//intrest instead of direction?
	Vector3D interest;
	float angle;
	int attenExp;
	float attenCo1,attenCo2,attenCo3;

};
