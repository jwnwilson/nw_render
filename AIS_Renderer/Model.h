#pragma once
#include "Vector4D.h"
#include "Vertex_R.h"
#include "VertexSD.h"
#include "Material.h"
#include "Matrix4D.h"
#include "ImplicitShape.h"
#include "Intersection.h"
#include "Face.h"
#include "EdgeSD.h"

struct ModelParam
{
	Vector3D position;
	Vector3D rotation;
	Vector3D scale;
	float radius;
	float sizeX;
	float sizeY;
	float sizeZ;
};

#define MODBASE 0
#define MODADV 1

class Model
{
public:
	Model(void);
	~Model(void);
	virtual void operator=(Model&);

	int getType(){return type;}
	virtual bool rayAgaintModel(Ray*,float &t)=0;
	virtual bool rayIntersectInModel(Ray* ray1,float &t)const=0;
	virtual bool getRayIntersecPoint(Ray* ray1,const Intersection* inter,float &t)const=0;

	virtual vector<int>* getIndex(){return NULL;}
	virtual vector<Vertex_R>* getVertices(){return NULL;}
	virtual vector<Vector3D>* getPositions(){return NULL;}
	virtual vector<Vector4D>* getNormals(){return NULL;}
	virtual vector<Vector2D>* getUVs(){return NULL;}
	virtual vector<Face*>* getFaces(){return NULL;}
	virtual vector<VertexSD>* getSDVertices(){return NULL;}

	virtual Vector3D getPositions(int& i)const=0;
	virtual Vector4D getNormals(int& i)const=0;
	virtual Vector2D getUVs(int& i)const=0;
	virtual Face getFaces(int& i)const=0;
	virtual Vertex_R getVertices(int& i){return Vertex_R();}
	virtual int getIndex(int& i){return NULL;}

	virtual int getFacesSize()const{return NULL;}
	virtual int getVerticesSize()const{return NULL;}
	virtual void increaseSubD(){;}
	virtual void decreaseSubD(){;}
	virtual vector<EdgeSD>* getEdges(){return NULL;}

	Model* getChildModel()const{return childModel;}
	Model* getParentModel()const{return parentModel;}
	void setChildModel(Model* m){childModel = m;}
	void setParentModel(Model* m){parentModel = m;}

	bool implicit,smooth,visible;
	int subD;
	int type;
	float refractionIndex;

	ModelParam parameters;
	Material* material;
	ImplicitShape* boundingShape;
	Model* parentModel;
	Model* childModel;
};
