#include "Vector4D.h"
#include "Matrix4D.h"

Vector4D::Vector4D()
{
	x = 0;
	y = 0;
	z = 0;
	h = 1;
}

Vector4D::Vector4D(float a, float b, float c, float d)
{
	x = a;
	y = b;
	z = c;
	h = d;
}

Vector4D::Vector4D(const Vector3D& vec)
{
	x=vec.x;
	y=vec.y;
	z=vec.z;
	h=1;
}
/*
Vector4D::Vector4D(const Vertex& ver)
{
	x=ver.getX();
	y=ver.getY();
	z=ver.getZ();
	h=1;
}*/

Vector4D  Vector4D::operator * (const float& f)const
{
	Vector4D temp1(x*f,y*f,z*f,h);

	return temp1;
}

bool Vector4D:: operator == (const Vector4D& vec)const
{
	if(x==vec.x&&y==vec.y&&z==vec.z&&h==vec.h)
	{
		return true;
	}
	else
	{
		return false;
	}
}

Vector4D Vector4D:: operator + (const Vector4D& vec)const
{
	Vector4D temp1;

	if ( h == 1 && vec.h == 1)
	{
		temp1 = Vector4D(x + vec.x, y + vec.y, z + vec.z, 1);
		return temp1;
	}
	else
	{
		Vector4D temp2(x,y,z,h);
		temp2.standardize();
		temp1=vec;
		temp1.standardize();
		temp1 = Vector4D(temp1.x + temp2.x, temp1.y + temp2.y, temp1.z +temp2.z, 1);
		//cout << "Vectors have been normalised to allow addition.\n";
		return temp1;
	}
}
Vector4D Vector4D:: operator - (const Vector4D& vec) const
{
	Vector4D temp1;

	if ( h == 1 && vec.h == 1)
	{
		temp1 = Vector4D(x - vec.x, y - vec.y, z - vec.z, 1);
		return temp1;
	}
	else
	{
		Vector4D temp2(x,y,z,h);
		temp2.standardize();
		temp1=vec;
		temp1.standardize();
		temp1 = Vector4D(temp2.x - temp1.x, temp2.y - temp1.y, temp2.z -temp1.z, 1);
		//cout << "Vectors have been normalised to allow subtraction.\n";
		return temp1;
	}
}

Vector4D Vector4D:: operator * (const Vector4D& vec)const
{
	Vector4D temp1;

	if ( h == 1 && vec.h == 1)
	{
		temp1 = Vector4D(x * vec.x, y * vec.y, z * vec.z, 1);
		return temp1;
	}
	else
	{
		Vector4D temp2(x,y,z,h);
		temp2.standardize();
		temp1.standardize();
		temp1 = Vector4D(temp1.x * temp2.x, temp1.y * temp2.y, temp1.z * temp2.z, 1);
		//cout << "Vectors have been normalised to allow subtraction.\n";
		return temp1;
	}
}

void Vector4D:: operator * (const Matrix4D& matrix)const
{
	cout<<"(Vector x Matrix) cannot be used as colum vector multiplication is used in this program.\n";

	/*float x, y, z, h;
	x = (getX()* matrix.getMatrix(0,0) + getY()*matrix.getMatrix(0,1) + getZ()*matrix.getMatrix(0,2) + getH()*matrix.getMatrix(0,3));
	y = (getX()* matrix.getMatrix(1,0) + getY()*matrix.getMatrix(1,1) + getZ()*matrix.getMatrix(1,2) + getH()*matrix.getMatrix(1,3));
	z = (getX()* matrix.getMatrix(2,0) + getY()*matrix.getMatrix(2,1) + getZ()*matrix.getMatrix(2,2) + getH()*matrix.getMatrix(2,3));
	h = (getX()* matrix.getMatrix(3,0) + getY()*matrix.getMatrix(3,1) + getZ()*matrix.getMatrix(3,2) + getH()*matrix.getMatrix(3,3));

	Vector4D vec2(x,y,z,h);
	return vec2;*/
}

void Vector4D::standardize() 
{
	x= x/h;
	y = y/h;
	z = z/h;
	h = 1;
}

float Vector4D::modulus()const
{
	float mod;

	mod = sqrt(x*x) + sqrt(y*y) + sqrt(z*z);

	return mod;

}

Vector4D Vector4D::normalize()const
{
	Vector4D vec1(x,y,z,h);
	if(h!=1)
	{
		vec1.standardize();
	}
	float mod = vec1.magnitude();
	vec1= Vector4D(x/mod, (y/mod), (z/mod), h);
	return vec1;
}

float Vector4D::dot(const Vector4D& a)const
{
	if(h!=1 || a.h!=1)
	{
		Vector4D vec1(x,y,z,h),vec2=a;
		vec1.standardize();
		vec2.standardize();

		float dot;

		dot = (vec1.x*vec2.x + vec1.y*vec2.y + vec1.z*vec2.z);

		return dot;
	}
	else
	{
		float dot;

		dot = (x*a.x + y*a.y + z*a.z);

		return dot;

	}
}

Vector4D Vector4D::cross(const Vector4D& a)const
{
	if(h!=1 || a.h!=1)
	{
		Vector4D vec1(x,y,z,h),vec2=a;
		vec1.standardize();
		vec2.standardize();
		vec1 = Vector4D(((vec1.y*vec2.z) - (vec2.y*vec1.z)),-((vec1.x*vec2.z)-(vec2.x*vec1.z)),((vec1.x*vec2.y)-(vec2.x*vec1.y)), 1);
		return vec1;
	}
	else
	{
		Vector4D vec1;
		vec1 = Vector4D(((y*a.z) - (a.y*z)),-((x*a.z)-(a.x*z)),((x*a.y)-(a.x*y)), 1);
		return vec1;
	}
}

void Vector4D::showVect() const
{
	cout<<"("<< x<<"," << y << ","<< z << ","<< h<< ")"<< endl;
}


Vector4D::~Vector4D(void)
{
}
