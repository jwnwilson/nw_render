#include "ModelBase.h"

ModelBase::ModelBase(void)
{
	type = MODBASE;
}

ModelBase::~ModelBase(void)
{
}
bool ModelBase::rayAgaintModel(Ray* r,float &t)
{
	//if(boundingShape->rayAgaintShape(r,t,this))
	if(implicit==true)
	{
		if(boundingShape->getRayImplicitShapeIntersection(r,t,this)==true)
		{
			//r->pointHit->setNorm(r->pointHit->getNorm().normalize());
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		if(rayIntersectInModel(r,t))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}
bool ModelBase::rayIntersectInModel(Ray* ray1,float &t)const
{
	//Model *m=models[modelNo];
	int v[4],vIter=0;
	bool hit;
	//t=std::numeric_limits<double>::infinity();
	for(int i=0;i<index.size();i++)
	{
		if(index[i]==-1)
		{
			for(int a=1;a<3;a++)
			{
				Intersection inter;
				inter.indexNo[0]=v[0];
				inter.indexNo[1]=v[a];
				inter.indexNo[2]=v[a+1];
				//inter.modelNo=modelNo;
				if(getRayIntersecPoint(ray1,&inter,t))
					hit = true;
			}
			vIter=0;
		}
		else
		{
			v[vIter]=index[i];
			vIter++;
		}
	}
	if(hit == true)
	{
		return true;
	}
	else
	{
		return false;
	}

}
bool ModelBase::getRayIntersecPoint(Ray* ray1,const Intersection* inter,float &t)const
{
	const Vertex_R* v[3];
	float b3;
	for(int i=0;i<3;i++)
	{
		v[i]=&vertices[inter->indexNo[i]];
	}
	Vector3D tb1b2,s1,s2,e1,e2,s,normal;
	e1=v[1]->getWorld()-v[0]->getWorld();
	e2=v[2]->getWorld()-v[0]->getWorld();
	s= ray1->position-v[0]->getWorld();
	s1=ray1->getDirection().cross(e2);
	s2=s.cross(e1);
	tb1b2=Vector3D(s2.dot(e2),s1.dot(s),s2.dot(ray1->getDirection()))*((1/(s1.dot(e1))));
	b3=(1-tb1b2.y-tb1b2.z);
	normal=(e2.cross(e1)).modulate();

	if(tb1b2.x>0)
	{
		if(tb1b2.y>=0&&tb1b2.y<=1&&tb1b2.z>=0&&tb1b2.z<=1&&b3>=0&&b3<=1)
		{	
			if(tb1b2.x< ray1->minT)
			{
				if(ray1->pointHit!=NULL)
				{
					delete ray1->pointHit;
					ray1->pointHit=NULL;
				}
				ray1->pointHit= new Vertex_R;
				ray1->pointHit->setWorld(ray1->getRayPoint(tb1b2.x));
				ray1->pointHit->setNorm(normal);
				Vector2D uv = ((v[0]->getUV() * b3) + (v[1]->getUV() * tb1b2.y) + (v[2]->getUV() * tb1b2.z));
				ray1->pointHit->setUV(uv);
				ray1->minT = tb1b2.x;
			}
			//t=tb1b2.x;
			
			return true;
		}
	}
	return false;
}
