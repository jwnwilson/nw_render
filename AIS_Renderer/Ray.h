#pragma once
#include "Vertex_R.h"

class Ray
{
public:
	Ray(void);
	~Ray(void);
	Vector3D getRayPoint(float t) const;
	void setDirection(const Vector3D&);
	Vector3D getDirection()const{return direction;}

	Vector3D position;
	// Will hold it's intersection point's data which makes passing and accessing it
	// more convient.
	Vertex_R *pointHit;
	// Used minT to make sure it has the closest collision point, refraction used
	// for when passign through an object, maxT unused so far.
	float minT,maxT,refractIndex;
private:
	Vector3D direction;
};
