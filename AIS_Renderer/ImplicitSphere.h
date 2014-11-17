#pragma once
#include "implicitshape.h"

class ImplicitSphere :
	public ImplicitShape
{
public:
	ImplicitSphere(void);
	~ImplicitSphere(void);
	void setPoints(Model*);

	bool implicitShapeCheck(Ray*,const Model*);
	bool rayAgaintModel(Ray*,float &t,const Model*);
	bool getRayImplicitShapeIntersection(Ray*,float &t,const Model*);	
	char getType(){return 's';}

	//float getTIntersect(const Ray*);

	float radius;
	Vector3D origin;
};
