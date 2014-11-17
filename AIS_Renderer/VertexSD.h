#pragma once
#include "Vector2D.h"
#include "Vector4D.h"

// New vertex class to store pointers to data, more efficient than
// Vertex_R, originally create for sub division but then
// used throughout project.

class Face;

class VertexSD
{
public:
	VertexSD(void);
	~VertexSD(void);

	void setUV(Vector2D* v){uv = v;}
	void setWorld(Vector3D* v){worldPos = v;}
	void setNorm(Vector4D* v){normal = v;}

	Vector2D getUV()const{return *uv;}
	Vector3D getWorld()const{return *worldPos;}
	Vector4D getNorm()const{return *normal;}

	Vector2D *uv;
	Vector3D *worldPos;
	Vector4D *normal;

	int valence();

	Face *startFace;
	VertexSD *child;
	bool regular, boundary;
	int subDlevel;
};
