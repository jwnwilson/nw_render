#pragma once
#include "ModelAdv.h"

class ModelSys
{
public:
	ModelSys(void);
	void createPlane(float wid,float hei,Vector3D pos,Model*);
	void createSphere(float rad,Vector3D pos,Model*);
	void createCube(float size, Vector3D pos,Model*);
	void mergeModels(Model*,Model*);
	void translate(Model*,Vector3D trans);
	void rotate(Model*,Vector3D rot);
	void scale(Model*,Vector3D rot);

	bool LoopSubD(Model*, int subD);

	~ModelSys(void);

private:

	vector<Face*> *origFaces;
	vector<Vector3D> *origPos;
	vector<Vector4D> *origNorm;
	vector<Vector2D> *origUv;
	vector<VertexSD> *origVerts;
	vector<int> *origIndex;
	vector<EdgeSD> *origEdges;

	static float beta(int val);
	bool subDModel(Model* mod);
	void FacesToTriangles(Face *f,vector<Face*> &vf);
	bool prepareForSubD(Model* mod);
	void averageNorms(Model* mod);
	vector<VertexSD*> getVerts(VertexSD* v);
	void weightRing(VertexSD* v, float beta, Vertex_R&);

	void createPlane(vector<Vertex_R*> verts,Model&);
};
