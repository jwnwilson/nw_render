#include "ImplicitPlane.h"
#include "Model.h"

ImplicitPlane::ImplicitPlane(void)
{
}

ImplicitPlane::~ImplicitPlane(void)
{
}
void ImplicitPlane::setPoints(Model* plane)
{
	Vector3D p1,p2,p3;

	if(plane->getType() == MODBASE)
	{
		/*Vector3D p1,p2,p3;
		p1=(*plane->getVertices())[0].getWorld();
		p2=(*plane->getVertices())[2].getWorld();
		p3=(*plane->getVertices())[1].getWorld();*/
	
	}
	else
	{
		p1 = (*plane->getPositions())[0];
		p2 = (*plane->getPositions())[2];
		p3 = (*plane->getPositions())[1];
	}

	A=(p1.y*(p2.z-p3.z)+p2.y*(p3.z-p1.z)+p3.y*(p1.z-p2.z));
	B=(p1.z*(p2.x-p3.x)+p2.z*(p3.x-p1.x)+p3.z*(p1.x-p2.x));
	C=(p1.x*(p2.y-p3.y)+p2.x*(p3.y-p1.y)+p3.x*(p1.y-p2.y));
	D=-(p1.x*(p2.y*p3.z-p3.y*p2.z)+p2.x*(p3.y*p1.z-p1.y*p3.z)+p3.x*(p1.y*p2.z-p2.y*p1.z));
	normal=Vector3D(A,B,C);
	
}

bool ImplicitPlane::rayAgaintModel(Ray* ray1,float &t,Model* mod)
{
	float vD=normal.dot(ray1->getDirection()),vO;
	if(vD<0)
	{
		vO=-(normal.dot(ray1->position)+D);
		t=vO/vD;
		if(t>0)
		{
			if(mod->rayIntersectInModel(ray1,t))
			{
				return true;
			}
		}
	}
	return false;
}

bool ImplicitPlane::implicitShapeCheck(Ray* ray1,const Model* mod)
{
	float vD=normal.dot(ray1->getDirection()),vO;
	if(vD<0)
	{
		vO=-(normal.dot(ray1->position)+D);
		t=vO/vD;
		if(t>0)
		{
			return true;
		}
	}
	return false;

}
bool ImplicitPlane::getRayImplicitShapeIntersection(Ray* ray1,float &t,const Model* m)
{
	float vD=normal.dot(ray1->getDirection()),vO;
	vO=-(normal.dot(ray1->position)+D);
	t=vO/vD;
	if(t>0)
	{
		if(t< ray1->minT)
		{
			float vD=normal.dot(ray1->getDirection()),vO;
			if(vD<0)
			{
				vO=-(normal.dot(ray1->position)+D);
				t=vO/vD;
				if(t>0)
				{
					if(m->rayIntersectInModel(ray1,t))
					{
						return true;
					}
				}
			}
			return false;
		}
	}
	else
	{
		return false;
	}
}
float ImplicitPlane::getTIntersect(const Ray* ray1)
{
	float vD=normal.dot(ray1->getDirection()),vO,t2;
	vO=-(normal.dot(ray1->position)+D);
	t2=vO/vD;
	return t2;
}
