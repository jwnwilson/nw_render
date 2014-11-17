#include "RaySystem.h"
#include "time.h"
#include <iostream>
#include <limits>

using std::cin;

float random()
{
  float scale=RAND_MAX+1.;
  float base=rand()/scale;
  float fine=rand()/scale;
  return base+fine/scale;
}

RaySystem::RaySystem(void)
{
	bounces=1;
	bounce=0;
	illum=NULL;
	shadows = true;
}

RaySystem::~RaySystem(void)
{
	if(illum!=NULL)
	{
		delete illum;
	}
}
ColourRGB RaySystem::rayIntoScene(Ray& ray1)
{
	bounce = 0;
	return fireRay(ray1);
}
ColourRGB RaySystem::fireRay(Ray& ray1)
{
	int modelNo=0;
	bool refl = false;
	ColourRGB sum(0,0,0);

	if(bounce<bounces)
	{	
		bounce++;
		if(scPtr->rayHitModel(&ray1,modelNo)==true)
		{					
			//Ray reflect;
			//reflect = getReflectRay(ray1);
			//sum= sum + fireRay(reflect);
			//bounce--;
			if( scPtr->models[modelNo]->refractionIndex != 0)
			{
				Ray refract;
				refract = getTransmittedRay(ray1,scPtr->models[modelNo]->refractionIndex);
				sum= sum + (fireRay(refract)*scPtr->models[modelNo]->material->transparency);
			}
			else
			{
				Ray reflect;
				reflect = getReflectRay(ray1);
				sum= sum + (fireRay(reflect)*scPtr->models[modelNo]->material->reflectivity);
			}
			sum= sum + rayReturnColour(ray1,modelNo);
			return sum;
		}
	}
	else
	{
		if(scPtr->rayHitModel(&ray1,modelNo)==true)
		{
			sum= sum + rayReturnColour(ray1,modelNo);
			return sum;
		}
	}
	
	return sum;
}

ColourRGB RaySystem::rayReturnColour(const Ray& ray1,int& modelNo)
{
	if(shadows == true)
	{
		shadowFeeler(ray1.pointHit);
		ColourRGB col;
		setIlluminationModel(modelNo);
		col = illum->shade(&ray1,lightsVisible);
		lightsVisible.clear();

		return col;
	}
	else
	{
		for(int i=0;i<scPtr->lights.size();i++)
		{
			lightsVisible.push_back(i);
		}
		ColourRGB col;
		setIlluminationModel(modelNo);
		col = illum->shade(&ray1,lightsVisible);
		lightsVisible.clear();

		return col;
	}
}
bool RaySystem::softShadow(Light* light,const Vertex_R* v)
{
	int seg = light->getSegments();
	int modNo;
	int hitCount =0;
	float atten, randFlo;
	vector<Vector3D> *segmentPoints;

	segmentPoints = light->getSegmentPos();

	for(int i=0; i< seg; i++)
	{
		Vector3D segPos;
		Ray ptToLght;
		segPos = (*segmentPoints)[i];
		segPos = segPos + (*light->getDirectionX() * random());	
		segPos = segPos + (*light->getDirectionY() * random());

		ptToLght.setDirection(segPos - v->getWorld());
		ptToLght.position = v->getWorld() + (ptToLght.getDirection() * 0.001);
		if(scPtr->rayHitModel(&ptToLght,modNo)==false)
		{
			hitCount++;
		}
	}
	if( hitCount > 0)
	{
		atten = hitCount /float(seg);
		light->setAtten( Vector3D(atten,0,0) );
		return true;
	}
	else
	{
		light->setAtten( Vector3D(0,0,0) );
		return false;
	}
	
}

bool RaySystem::shadowFeeler(const Vertex_R* intersec)
{
	Ray ptToLght;
	int modNo;
	float t;

	ptToLght.position=intersec->getWorld();
	vector<Light*> lights = scPtr->lights;

	for(int i=0;i<lights.size();i++)
	{
		if(lights[i]->isArea())
		{
			if(softShadow(lights[i],intersec))
			{
				lightsVisible.push_back(i);
			}
		}
		else
		{
			// Test to see if light reaches point
			ptToLght.setDirection(lights[i]->getPosition()-intersec->getWorld());
			ptToLght.position = ptToLght.position + (ptToLght.getDirection()* 0.0001);
			if(scPtr->rayHitModel(&ptToLght,modNo)==false)
			{
				lightsVisible.push_back(i);
			}
			else
			{
				if(scPtr->models[modNo]->material->transparency != ColourRGB(0,0,0))
				{
					float atten = scPtr->models[modNo]->material->transparency.getRed();
					lights[i]->setAtten( Vector3D(atten,0,0) );
					lightsVisible.push_back(i);
				}
			}

		}
	}
	if(lightsVisible.size()>0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

Ray RaySystem::getTransmittedRay(const Ray& ray1,const float& n2)
{
	/*n1 = index of refraction of original medium
	n2 = index of refraction of new medium
	n = n1 / n2
	c2 = sqrt( 1 - n2 * (1 - c12) )

	Rr = (n * V) + (n * c1 - c2) * N*/ 

	float c2;

	float c1 = -ray1.getDirection().dot(ray1.pointHit->getNorm());

	float n1 = ray1.refractIndex,n;

	n = n1 / n2;

	c2 = sqrt( 1 - (n*n) * (1 - (c1*c1)) );

	Vector3D T = ( ray1.getDirection() * n) +  ray1.pointHit->getNorm() * (n * c1- c2) ;
	T = T.normalize();
	Ray ray2;
	ray2.setDirection(T);
	ray2.position=ray1.pointHit->getWorld()+ (ray2.getDirection()*0.001);
	return ray2;
}

Ray RaySystem::getReflectRay(const Ray& ray1)
{
	Vector3D L= (ray1.position-ray1.pointHit->getWorld()).normalize();
	Ray ray2;
	ray2.setDirection((ray1.pointHit->getNorm()*float(2)*(ray1.pointHit->getNorm().dot(L))-L).normalize());
	ray2.position=ray1.pointHit->getWorld()+ (ray2.getDirection()*0.001);
	return ray2;
}
void  RaySystem::setIlluminationModel(int& modelNo)
{
	switch (scPtr->models[modelNo]->material->getType()){
		case PHONGM:
			illum= new ModelPhong;
			illum->setScene(scPtr);
			illum->setMaterial(scPtr->models[modelNo]->material);
			break;
		default:
			illum= new IlluminationModel;
			break;
	}

}