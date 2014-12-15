#include "ModelPhong.h"

ModelPhong::ModelPhong(void)
{
}

ModelPhong::~ModelPhong(void)
{
}

ColourRGB ModelPhong::shade(const Ray* r,const vector<int>& lights, int &modelNo)
{
	ColourRGB intensity;
	ColourRGB diffuseCol;
	ColourRGB sumLights(0,0,0);
	Vector3D V,lightVect,R;
	Vertex_R *v= r->pointHit;
	Material *matPtr = scenePtr->models[modelNo]->material;

	if( matPtr->isTextured() )
	{
		diffuseCol = getTextureCol(v, matPtr);
	}
	else
	{
		diffuseCol = matPtr->getDiffuseC();
	}


	int size=lights.size();
	for(int i=0;i<size;i++)
	{
		lightVect=getLightVect(v,lights[i]);//.normalize();

		float LdotN=(lightVect.dot(v->getNorm())),RVn,attenuation;
		if(LdotN<0)
		{
			LdotN=0;
		}
		attenuation =getAttenuation(v,lights[i]);
		R=getReflectVect(v,lights[i]);
		V=getVeiwVect(v,r);

		RVn=(R.dot(V));
		if(RVn<0)
		{
			RVn=0;
		}
		else
		{
			for (int a=1; a<matPtr->getSpecularExp(); a++)
			{
				RVn*=RVn;
					
			}
		}

		sumLights=sumLights+(scenePtr->lights[lights[i]]->getColour()*((diffuseCol*LdotN)
			+(matPtr->getSpecularC()*RVn)))*attenuation;

		
	}
	intensity= scenePtr->ambience*diffuseCol+(sumLights);

	intensity= intensity+matPtr->getEmission();
	
	return intensity;
}
