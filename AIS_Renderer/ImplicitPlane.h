#pragma once
#include "ImplicitShape.h"
#include "Vertex_R.h"
#include "Ray.h"
#include "Intersection.h"
#include <vector>

class ImplicitPlane:
	public ImplicitShape
{
public:
	ImplicitPlane(void);
	~ImplicitPlane(void);
	void setPoints(Model*);
	
	bool implicitShapeCheck(Ray*,const Model*);
	bool getRayImplicitShapeIntersection(Ray*,float &t,const Model*);
	float getTIntersect(const Ray*);
	char getType(){return 'p';}

	Vector3D getNormal(){return normal;}

	//bool getRayShapeIntersection(Ray*,float &t, Model*);
	bool rayAgaintModel(Ray*,float &t,Model*);
	//Vector3D getNormal(){return (normal*(1/D));}
	//float getRayShapeIntersection(const Ray*);
private:

	float A,B,C,D;
	Vector3D normal;
	//bool rayInsideShape(const Ray*,float &t,const Model*);
};
