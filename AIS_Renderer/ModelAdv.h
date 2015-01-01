#pragma once
#include "VertexSD.h"
#include "Model.h"

class ModelAdv:
	public Model
{
public:
	ModelAdv(void);
	~ModelAdv(void);
	// check ray collision against model
	virtual void operator=(ModelAdv&);
	bool rayAgaintModel(Ray*,float &t);
	bool rayIntersectInModel(Ray* ray1,float &t)const;
	bool getRayIntersecPoint(Ray* ray1,const Intersection* inter,float &t)const;
	bool getRayIntersecPoint2(Ray* ray1,const Intersection* inter,float &t)const;

	vector<Vector3D>* getPositions(){return &positions[subD];}
	vector<Vector4D>* getNormals(){return &normals[subD];}
	vector<Vector2D>* getUVs(){return &UVs[subD];}
	vector<Face*>* getFaces(){return &faces[subD];}
	vector<int>* getIndex(){return &Index[subD];}
	vector<EdgeSD>* getEdges(){return &subDEdges[subD];}
	virtual vector<VertexSD>* getSDVertices(){return &Vertices[subD];}

	Vector3D getPositions(int& i)const{return positions[subD][i];}
	Vector4D getNormals(int& i)const{return normals[subD][i];}
	Vector2D getUVs(int& i)const{return UVs[subD][i];}
	Face getFaces(int& i)const{return *(faces[subD])[i];}
	int getFacesSize()const{return faces.size();}
	//ModelAdv* getChildModel()const{return childModel;}
	//ModelAdv* getParentModel()const{return parentModel;}
	//void setChildModel(ModelAdv* m){childModel = m;}
	//void setParentModel(ModelAdv* m){parentModel = m;}

	void increaseSubD();
	void decreaseSubD();

	vector<vector<Vector3D>> positions;
	vector<vector<Vector4D>> normals;
	vector<vector<Vector2D>> UVs;
	vector<vector<Face*>> faces;

private:

	vector<vector<int>> Index;
	vector<vector<VertexSD>> Vertices;
	vector<vector<EdgeSD>> subDEdges;
};
