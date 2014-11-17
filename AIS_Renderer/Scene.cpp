#include "Scene.h"
#include <limits>


Scene::Scene(void)
{
	//ambience=ColourRGB(0.2,0.2,0.2);
}

Scene::~Scene(void)
{	
	clearScene();
}

void Scene::clearScene()
{
	models.clear();
	for(int i=0;i<lights.size();i++)
	{
		if(lights[i]!=NULL)
		{
			delete lights[i];
		}
	}
	for(int i=0;i<models.size();i++)
	{
		if(models[i]!=NULL)
		{
			delete models[i];
		}
	}
	for(int i=0;i<materials.size();i++)
	{
		if(materials[i]!=NULL)
		{
			delete materials[i];
		}
	}
	for(int i=0;i<textures.size();i++)
	{
		if(textures[i]!=NULL)
		{
			textures[i]->fileName = "";
			delete textures[i];
		}
	}
}
bool Scene::rayHitModel(Ray* ray1,int& modelNo)
{
	float t = std::numeric_limits<float>::infinity(),test=0;
	modelNo=-1;
	for(int i=0;i<models.size();i++)
	{
		if(models[i]->rayAgaintModel(ray1,test)==true)
		{
			if(ray1->minT < t)
			{
				t = ray1->minT;
				modelNo=i;
			}
		}
	}
	if(modelNo!=-1)
	{	
		return true;
	}
	else
	{
		return false;
	}

}
/*
bool Scene::rayIntersectInModel(const Ray* ray1,const int& modelNo,Vertex_R& verReturn)
{
	Model *m=models[modelNo];
	int v[4],vIter=0;
	for(int i=0;i<m->index.size();i++)
	{
		if(m->index[i]==-1)
		{
			for(int a=1;a<3;a++)
			{
				Intersection inter;
				inter.indexNo[0]=v[0];
				inter.indexNo[1]=v[a];
				inter.indexNo[2]=v[a+1];
				inter.modelNo=modelNo;
				if(getRayIntersecPoint(ray1,&inter,verReturn)==true)
				{
					return true;
				}
			}
			vIter=0;
		}
		else
		{
			v[vIter]=m->index[i];
			vIter++;
		}
	}
	return false;

}
bool Scene::getRayIntersecPoint(const Ray* ray1,const Intersection* inter,Vertex_R& returnVer)
{
	Vertex_R* v[3];
	float b3;
	for(int i=0;i<3;i++)
	{
		v[i]=&models[inter->modelNo]->vertices[inter->indexNo[i]];
	}
	Vector3D tb1b2,s1,s2,e1,e2,s,normal;
	e1=v[1]->getWorld()-v[0]->getWorld();
	e2=v[2]->getWorld()-v[0]->getWorld();
	s= ray1->position-v[0]->getWorld();
	s1=ray1->getDirection().cross(e2);
	s2=s.cross(e1);
	tb1b2=Vector3D(s2.dot(e2),s1.dot(s),s2.dot(ray1->getDirection()))*((1/(s1.dot(e1))));
	b3=(1-tb1b2.y-tb1b2.z);
	normal=(e1.cross(e2)).modulate();

	if(tb1b2.x>0)
	{
		if(tb1b2.y>=0&&tb1b2.y<=1&&tb1b2.z>=0&&tb1b2.z<=1&&b3>=0&&b3<=1)
		{		
			returnVer.setWorld(ray1->getRayPoint(tb1b2.x));
			returnVer.setNorm(normal);
			return true;
		}
	}
	return false;
}*/

