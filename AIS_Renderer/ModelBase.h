#pragma once
#include "model.h"

class ModelBase :
	public Model
{
public:
	ModelBase(void);
	~ModelBase(void);

	bool rayAgaintModel(Ray*,float &t);
	bool rayIntersectInModel(Ray* ray1,float &t)const;
	bool getRayIntersecPoint(Ray* ray1,const Intersection* inter,float &t)const;

	vector<int>* getIndex(){return &index;}
	vector<Vertex_R>* getVertices(){return &vertices ;}
	

	Vertex_R getVertex(int& i)const{return vertices[i];}
	int getIndex(int& i)const{return index[i];}
	int getVerticesSize()const{return vertices.size();}

	vector<Vertex_R> vertices;
	vector<int> index;
};
