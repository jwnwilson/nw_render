#pragma once
#include "Ray.h"
#include "Vertex_R.h"
#include <vector>


class Model;

// implicit shapes used to speed up rendering by quickly failing objects


class ImplicitShape
{
public:
	ImplicitShape(void);
	// set implicit object from model positions (assumes correct model data is sent)
	virtual void setPoints(Model*){;}
	virtual void setPoints(vector<Model*>){;}

	// quick check to fail tests quickly
	virtual bool implicitShapeCheck(Ray*,const Model*){return false;}
	// get intersection point on implicit object
	virtual bool getRayImplicitShapeIntersection(Ray*,float &t,const Model*){return false;}
	// return t even if it is negative or fails test
	virtual float getTIntersect(const Ray*){return 0;}
	// find implicit shape type
	virtual char getType(){return 'd';}

	virtual bool rayAgaintModel(Ray*,float &t,Model*){return false;}
	//virtual bool getRayShapeIntersection(Ray*,float &t){return false;}

	Vertex_R intersection;
	float t;

	~ImplicitShape(void);

private:
	virtual bool rayInsideShape(const Ray*,float &t,const Model*){return false;}

};
