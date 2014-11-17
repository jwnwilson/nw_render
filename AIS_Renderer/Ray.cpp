#include "Ray.h"
#include <limits>

Ray::Ray(void)
{
	pointHit=NULL;
	minT = std::numeric_limits<float>::infinity();
	maxT = -std::numeric_limits<float>::infinity();
	refractIndex = 1;
}

Ray::~Ray(void)
{
	if(pointHit!=NULL)
	{
		delete pointHit;
	}
}
void Ray::setDirection(const Vector3D& d)
{
	direction=d.normalize();
}

Vector3D Ray::getRayPoint(float t) const
{
	return (position+(direction*t));
}