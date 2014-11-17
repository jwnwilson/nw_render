#pragma once
#include <iostream>
#include <math.h>

using namespace std;

//Simple class does exactly as expected.
class Vector4D;
class Vector3D
{
public:
	Vector3D();
	Vector3D(float, float, float);
	//Vector3D(const RVertex&);
	virtual ~Vector3D();

	Vector3D operator + (const Vector3D&)const;
	Vector3D operator - (const Vector3D&)const;
	Vector3D operator * (const Vector3D&)const;
	Vector3D operator * (const float&)const;
	Vector3D operator / (const float&)const;
	bool operator ==(const Vector3D&)const;
	void operator = (const Vector4D&);

	virtual void showVect() const;
	
	float angle(const Vector3D&)const;
	Vector3D normalize()const;
	float dot(const Vector3D&)const;
	Vector3D cross(const Vector3D&)const;
	//Vector3D modulate() const;
	float modulus()const;
	float magnitude()const;
	Vector3D modulate() const;
	void roundToDP(int);
	
	float x;
	float y;
	float z;

};
