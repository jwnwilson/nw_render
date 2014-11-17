#pragma once
#include "Vector3D.h"
#include <math.h>

class RVertex;
class Matrix4D;


class Vector4D :
	public Vector3D
{
public:
	Vector4D();
	Vector4D(float, float, float, float);
	Vector4D(const Vector3D&);
	~Vector4D(void);

	Vector4D operator + (const Vector4D&)const;
	Vector4D operator - (const Vector4D&)const;
	Vector4D operator * (const Vector4D&)const;
	Vector4D operator * (const float&)const;
	bool operator == (const Vector4D&)const;
	//Produces warning message function not used as would be confusing as applies colum vector 
	//multiplication is not used.
	void operator * (const Matrix4D&)const;


	void showVect() const;
	Vector4D normalize()const;
	float dot(const Vector4D&)const;
	Vector4D cross(const Vector4D&)const;
	void  standardize();
	
	float h;

protected:
	float modulus() const;
};
