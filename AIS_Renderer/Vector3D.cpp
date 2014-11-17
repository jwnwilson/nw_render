#include "Vector3D.h"
#include "Vector4D.h"
#include "Matrix4D.h"

Vector3D::Vector3D()
{
	x = 0;
	y = 0;
	z = 0;
}
Vector3D::Vector3D(float a, float b , float c): x(a), y(b), z(c)
{}/*
Vector3D::Vector3D(const Vertex& ver)
{
	x=ver.getX();
	y=ver.getY();
	z=ver.getZ();
}*/
Vector3D::~Vector3D(void)
{
}
void Vector3D::roundToDP(int dp)
{
	int a,b,c,d=1;
	for(int i=0;i<dp;i++)
	{
		d=dp*10;
	}
	a=x*d;
	b=y*d;
	c=z*d;
	x=a/d;
	y=b/d;
	z=c/d;
}
float Vector3D::angle(const Vector3D& v)const
{
	float ang;
	ang=acos((this->dot(v)/(this->modulus()*v.modulus())));
	ang=(ang*180)/3.1415;
	return ang;
}

void Vector3D::operator = (const Vector4D& temp)
{
	float a,b,c,d;
	a= temp.x;
	b= temp.y;
	c= temp.z;
	d= temp.h;
	x=a/d;
	y=b/d;
	z=c/d;


}
bool Vector3D::operator ==(const Vector3D& a)const
{
	if(x==a.x)
	{
		if(y==a.y)
		{
			if(z==a.z)
			{
				return true;
			}
		}
	}
	return false;
}
Vector3D Vector3D:: operator + (const Vector3D& temp)const
{
		Vector3D vec1;
		vec1 = Vector3D(x + temp.x, y + temp.y, z + temp.z);
		return vec1;
}
Vector3D Vector3D:: operator - (const Vector3D& temp)const
{
	Vector3D vec1;
	vec1 = Vector3D(x - temp.x, y - temp.y, z - temp.z);
	return vec1;
}
Vector3D Vector3D:: operator * (const Vector3D& temp)const
{
	Vector3D vec1;
	vec1 = Vector3D(x * temp.x, y * temp.y, z * temp.z);
	return vec1;
}

Vector3D Vector3D::operator * (const float& a)const
{
	Vector3D vec1;
	vec1 = Vector3D(x * a, y * a, z * a);
	return vec1;
}
Vector3D  Vector3D::operator / (const float& a)const
{
	Vector3D vec1;
	vec1 =Vector3D((x/a),(y/a),(z/a));

	return vec1;
}


float Vector3D::modulus()const
{
	float mod;

	mod = sqrt(x*x) + sqrt(y*y) + sqrt(z*z);

	return mod;
}
float Vector3D::magnitude()const
{
	float xpos=(x*x),ypos=(y*y),zpos=(z*z),sum;
	sum=sqrt(xpos+ypos+zpos);
	return sum;
}


Vector3D Vector3D::normalize() const
{
	Vector3D vec1(x,y,z);
	float sum=magnitude();
	if(sum!=0)
	{
		vec1=Vector3D(x/sum,y/sum,z/sum);
	}

	return vec1;
	
}
Vector3D Vector3D::modulate() const
{
	Vector3D vec1(x,y,z);
	float f=vec1.modulus();
	if(f!=0)
	{
		vec1=Vector3D(x/f,y/f,z/f);
	}

	return vec1;
	
}

float Vector3D::dot(const Vector3D& a)const
{
	float dot;

	dot = (x*a.x + y*a.y + z*a.z);

	return dot;
}

Vector3D Vector3D::cross(const Vector3D& a)const
{
	Vector3D vec1;
	vec1 = Vector3D((y*a.z - a.y*z),(-(x*a.z-a.x*z)),(x*a.y-a.x*y));
	return vec1;
}
/*
Vector3D Vector3D::normalize()const
{
	float mod = modulus();
	Vector3D temp(x/mod,y/mod,z/mod);
	return temp;
}*/

void Vector3D::showVect() const
{
	cout<<"("<< x<<"," << y << ","<< z << ")"<< endl;
}