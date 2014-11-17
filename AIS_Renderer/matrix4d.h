#pragma once
#include "Vector4D.h"
#include <math.h>

class Camera;
class Vertex_R;

class Matrix4D
{
public:
	Matrix4D();
	Matrix4D(float [4][4]);
	~Matrix4D(void);

	float getMatrix(int, int)const;

	Vector4D operator * (const Vector4D&)const;
	Matrix4D operator * (const Matrix4D&)const;
	/*
	RVertex operator *(const RVertex&)const;*/
	//friend Vector4D Vector4D::operator *(const Matrix4D&)const;

	//turns into a rotation matrix for angle float
	void rotX(float); 
	void rotY(float);
	void rotZ(float);
	void rotXYZ(float degx,float degy,float degz);

	//turns into a transaltion/scale matrix for angle float
	void trans(float,float,float);
	void scale(float,float,float);
	Matrix4D persp(float,float,float,float,float)const;// In order of parameter list
	// floats = field of view (degrees), aspect ratio: ,aspect ratio, near plane, far plane.
	Matrix4D inverse()const;
	Matrix4D veiwTrans(const Vector3D&, const Vector3D&, const Vector3D&)const; 
	Matrix4D veiwTrans(const Camera& cam,const Vector3D& upV)const;
	//Input position of camera and position of interest and up vector
	//Note: is 3D Vector necessary?
	//Note: Saves memory no problems found.
	void standardise();
	void emptyMatrix();


	void ShowMat()const;


private:

	Matrix4D projectionX()const;
	Matrix4D projectionY()const;
	Matrix4D projectionZ()const;
	float matrix[4][4];

};
