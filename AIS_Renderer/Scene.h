#pragma once
#include "Material.h"
#include "Model.h"
#include "Ray.h"
#include "Intersection.h"
#include "Texture.h"
#include "Light.h"

class Scene
{
public:
	Scene(void);
	~Scene(void);
	void clearScene();
	bool rayHitModel(Ray* ray1,int& modelNo);
	//bool rayIntersectInModel(const Ray* ray1,const int& modelNo,Vertex_R& vecReturn);
	vector<Material*> materials;
	vector<Texture*> textures;
	vector<Model*> models;
	vector<Light*> lights;
	ColourRGB ambience;

private:
	//bool getRayIntersecPoint(const Ray* ray1,const Intersection* inter,Vertex_R& returnVec);
	
};
