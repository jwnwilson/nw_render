#pragma once
#include "Ray.h"
#include "ModelPhong.h"
#include "Scene.h"
#include "ColourRGB.h"
#include "Vertex_R.h"
#include "IlluminationModel.h"
#include <vector>
#include <map>

class RaySystem 
{
public:
	RaySystem(void);
	~RaySystem(void);

	void initalise(Scene* s,const int& b);
	ColourRGB rayIntoScene(Ray&);	
	
private:

	// main ray functions
	ColourRGB fireRay(Ray&);
	ColourRGB rayReturnColour(const Ray& ray1,int&);
	//ColourRGB rayOntoModel(const Ray&,int&);
	

	// ray shadow functions
	vector<LightParam> shadowFeeler(const Vertex_R*);
	bool softShadow(Light*,const Vertex_R*);

	// ray finding functions
	Ray getReflectRay(const Ray&);
	Ray getTransmittedRay(const Ray& ray1,const float& index);
	//void setIlluminationModel(int&);
	IlluminationModel* getIlluminationModel(int&);

	int bounces, bounce, modelNo;
	bool shadows;
	// stored which lights are visable to current point ray has hit.
	//vector<int> lightsVisible;
	// holds illumination of model collised with.
	map<int, IlluminationModel*> illumModels;
	Scene *scPtr;
};
