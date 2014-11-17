#include "IlluminationModel.h"

IlluminationModel::IlluminationModel(void)
{
}

IlluminationModel::~IlluminationModel(void)
{
}
ColourRGB IlluminationModel::getTextureCol(const Vertex_R* v1)
{
	Texture* tex = matPtr->getTexture();
	int u = (v1->getUV().x * (tex->colourBuff.getWidth()-1)), v = (v1->getUV().y * (tex->colourBuff.getHeight()-1));
	return tex->colourBuff.getPix(u,v);
}
Vector3D IlluminationModel::getHalfVect(const Vector3D& L,const Vector3D& V)
{
	Vector3D H;

	H= (L+V).modulate();
	return H;
}
Vector3D IlluminationModel::getLightVect(const  Vertex_R* vertex1,int i)
{
	Vector3D lightVect=(scenePtr->lights[i]->getPosition()- vertex1->getWorld()).normalize();

	return lightVect;
	
}
Vector3D IlluminationModel::getVeiwVect(const  Vertex_R* vertex1,const Ray* r)
{
	Vector3D vertPos = vertex1->getWorld();
	Vector3D veiwVect= ( r->position - vertPos).normalize();
	return veiwVect;
	
}

Vector3D IlluminationModel::getReflectVect(const  Vertex_R* vertex1,int i)
{
	Vector3D L= getLightVect(vertex1,i);
	Vector3D reflectVect= (vertex1->getNorm()*float(2)*(vertex1->getNorm().dot(L))-L);
	return reflectVect;
}

float IlluminationModel::getAttenuation(const  Vertex_R* v, int i)
{
	float attenuation=0;
	Vector4D vecPos;
	vecPos= v->getWorld();
	if( scenePtr->lights[i]->isArea())
	{
		attenuation = scenePtr->lights[i]->getAttenCo().x;
	}
	if( scenePtr->lights[i]->isPoint())
	{
		float distance = ((scenePtr->lights[i]->getPosition()-vecPos).modulus());
		attenuation= 1/((scenePtr->lights[i]->getAttenCo().x)+(scenePtr->lights[i]->getAttenCo().y*distance)+
			(scenePtr->lights[i]->getAttenCo().z*(distance*distance)));
	}
	if(scenePtr->lights[i]->isSpot())
	{
		Vector4D V, D;
		V= (vecPos-(scenePtr->lights[i]->getPosition())).normalize();
		D= scenePtr->lights[i]->getInterest();
		if (V.dot(D)> (cos(scenePtr->lights[i]->getAngle()/2)))
		{
			attenuation=((V.dot(D)-cos(scenePtr->lights[i]->getAngle()/2))/(1-cos(scenePtr->lights[i]->getAngle()/2)));

			if(scenePtr->lights[i]->getAttenExp()==0)
			{
				attenuation=1;
			}
			else
			{
				for(int a=1;a<(scenePtr->lights[i]->getAttenExp());a++)
				{
					attenuation= attenuation*attenuation;
				}
			}
			float distance = ((scenePtr->lights[i]->getPosition()-vecPos).modulus());
			attenuation*=(1/(scenePtr->lights[i]->getAttenCo().x+(scenePtr->lights[i]->getAttenCo().y*distance)+
				(scenePtr->lights[i]->getAttenCo().z*(distance*distance))));
		}
		else
		{
			attenuation=0;
		}
	}
	return attenuation;
}