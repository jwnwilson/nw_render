#include "Vector2D.h"
#include "Point.h"
Vector2D::Vector2D(void)
{
}

Vector2D::~Vector2D(void)
{
}
Vector2D::Vector2D(float f0,float f1)
{
	x=f0;
	y=f1;
}
Vector2D::Vector2D(const Point& p) 
{
	x=p.getX();
	y=p.getY();
}

float Vector2D::angle(const Vector2D& v)const
{
	float ang;
	ang=acos((this->dot(v)/(this->modulus()*v.modulus())));
	ang=(ang*180)/3.1415;
	return ang;
}

Vector2D Vector2D::operator + (const Vector2D& v)const
{
	Vector2D temp2D(v.x+x,v.y+y);
	return temp2D;
}
Vector2D Vector2D::operator - (const Vector2D& v)const
{
	Vector2D temp2D(x-v.x,y-v.y);
	return temp2D;
}

float Vector2D::dot(const Vector2D& a)const
{
	float dot;

	dot = (x*a.x + y*a.y);

	return dot;
}
float Vector2D::modulus()const
{
	float mod;

	mod = sqrt(x*x + y*y);

	return mod;
}
Vector2D Vector2D::cross(const Vector2D& a)const
{
	Vector2D vec1;
	//vec1 = Vector2D((y*a.z - a.y*z),(-(x*a.z-a.x*z)));
	cout<<"Cross product of 2D vector not implemented\n";
	return vec1;
}

Vector2D Vector2D::normalize()const
{
	float mod = modulus();
	Vector2D temp(x/mod,y/mod);
	return temp;
}

Vector2D Vector2D::operator * (const Vector2D& v)const
{
	Vector2D temp2D(v.x*x,v.y*y);
	return temp2D;
}
Vector2D Vector2D::operator * (const float& v)const
{
	Vector2D temp2D(x*v,y*v);
	return temp2D;
}
Vector2D Vector2D::operator / (const float& v)const
{
	Vector2D temp2D(x/v,y/v);
	return temp2D;
}
