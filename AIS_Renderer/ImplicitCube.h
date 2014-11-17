#pragma once
#include "implicitshape.h"
#include "implicitPlane.h"

class ImplicitCube :
	public ImplicitShape
{
public:
	ImplicitCube(void);
	~ImplicitCube(void);
	//bool rayAgaintModel(Ray*,float &t,Model*);
	//void setPoints(vector<Model*>);
	void setPoints(Model*);

	bool implicitShapeCheck(Ray*,const Model*);
	bool getRayImplicitShapeIntersection(Ray*,float &t,const Model*);
	char getType(){return 'c';}
	bool comparePlanes(Ray* r,float &t,int p1,int p2,const Model*);

	ImplicitPlane sides[6];
	//Vertex_R sidePoints[6];
	int nearSide;
	double Tnear,Tfar;
};
