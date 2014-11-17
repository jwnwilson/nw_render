#pragma once
#include <iostream>
#include <math.h>
#define PI 3.141592653

using namespace std;

class Point;
class Vector2D
{
public:
	Vector2D(void);
	Vector2D(float,float);
	Vector2D(const Point&);

	Vector2D operator + (const Vector2D&)const;
	Vector2D operator - (const Vector2D&)const;
	Vector2D operator * (const Vector2D&)const;
	Vector2D operator * (const float&)const;
	Vector2D operator / (const float&)const;

	float angle(const Vector2D&)const;
	Vector2D normalize()const;
	float dot(const Vector2D&)const;
	Vector2D cross(const Vector2D&)const;
	float modulus()const;

	~Vector2D(void);

	
	float x;
	float y;
	
};
