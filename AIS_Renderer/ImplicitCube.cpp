#include "ImplicitCube.h"
#include "ModelAdv.h"
#include "ModelBase.h"
#include <limits>

ImplicitCube::ImplicitCube(void)
{
	Tnear=-std::numeric_limits<double>::infinity(),Tfar=std::numeric_limits<double>::infinity();
}

ImplicitCube::~ImplicitCube(void)
{
}
bool ImplicitCube::implicitShapeCheck(Ray* r,const Model* mod)
{
	t=-std::numeric_limits<double>::infinity();
	if(comparePlanes(r,t,0,5,mod)==false)
	{
		Tnear=-std::numeric_limits<double>::infinity(),Tfar=std::numeric_limits<double>::infinity();
		return false;
	}
	if(comparePlanes(r,t,1,2,mod)==false)
	{
		Tnear=-std::numeric_limits<double>::infinity(),Tfar=std::numeric_limits<double>::infinity();
		return false;
	}
	if(comparePlanes(r,t,3,4,mod)==false)
	{
		Tnear=-std::numeric_limits<double>::infinity(),Tfar=std::numeric_limits<double>::infinity();
		return false;
	}
	//if(sides[nearSide].getRayImplicitShapeIntersection(r,t,mod)==true)
	//{
	//	Tnear=-std::numeric_limits<double>::infinity(),Tfar=std::numeric_limits<double>::infinity();
	//	return true;
	//}
	return true;
}

bool ImplicitCube::getRayImplicitShapeIntersection(Ray* r,float &t1,const Model* m)
{
	implicitShapeCheck(r,m);

	if(sides[nearSide].getRayImplicitShapeIntersection(r,t,m)==true)
	{
		Tnear=-std::numeric_limits<double>::infinity(),Tfar=std::numeric_limits<double>::infinity();
		return true;
	}
	else
	{
		return false;
	}

}
void ImplicitCube::setPoints(Model* cube)
{
	vector<Face*> *faces = cube->getFaces();
	for(int i=0;i<6;i++)
	{
		Model *temp = new ModelAdv;
		temp->getPositions()->push_back(*(*faces)[i]->vertexPos[0]);
		temp->getPositions()->push_back(*(*faces)[i]->vertexPos[1]);
		temp->getPositions()->push_back(*(*faces)[i]->vertexPos[2]);
		sides[i].setPoints(temp);
		delete temp;
		//sidePoints[i]=planes[i]->vertices[0];
	}
}
//void ImplicitCube::setPoints(Model* cube)
//{
//	vector<Vertex_R> *vertices = cube->getVertices();
//	int sideSize=vertices->size()/6;
//	ModelBase side;
//
//	for(int i=0;i<6;i++)
//	{
//		for(int a=0;a<4;a++)
//		{
//			side.vertices.push_back((*vertices)[(i*sideSize)+a]);
//			side.index.push_back(side.vertices.size()-1);
//		}
//		side.index.push_back(-1);
//		sides[i].setPoints(&side);
//		side.vertices.clear();
//		side.index.clear();
//	}
//}
bool ImplicitCube:: comparePlanes(Ray* r,float &t,int i1,int i2,const Model* mod)
{
	int nearPl=i1, sideSize= mod->getFacesSize()/6;
	ImplicitPlane* p1=&sides[i1],*p2=&sides[i2];
	Face f1 = mod->getFaces(i1);
	Face f2 = mod->getFaces(i2);
	//Vertex_R v1=mod->getVertices())[(i1*sideSize)*mod->subD],const *v2=&(*mod->getVertices())[(i2*sideSize)*mod->subD];

	int dot=(r->getDirection().dot(*f1.vertexNorm[0])*10000);
	if(dot==0)
	{
		Vector3D rayToPlane= (*f1.vertexPos[0])-r->position;
		if((*f1.vertexNorm[0]).dot(rayToPlane)<0)
		{
			return false;
		}
		rayToPlane= (*f2.vertexPos[0])-r->position;
		if((*f2.vertexPos[0]).dot(rayToPlane)<0)
		{
			return false;
		}
	}
	else
	{
		float T1,T2,temp;
		T1=p1->getTIntersect(r);
		T2=p2->getTIntersect(r);
		if(T1>T2)
		{
			temp=T1;
			T1=T2;
			T2=temp;
			nearPl=i2;
		}
		if(T1>Tnear)//&&T1>0)
		{
			Tnear=T1;
			nearSide=nearPl;
		}
		if(T2<Tfar)//&&T2>0)
		{
			Tfar=T2;
		}
		if(Tnear>Tfar)
		{
			return false;
		}
		if(Tfar<0.00001)
		{
			return false;
		}
	}
	t=Tnear;
	return true;
}
