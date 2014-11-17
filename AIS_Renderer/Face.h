#pragma once
#include <vector>
#include "Vector4D.h"
#include "Vector2D.h"
#include "VertexSD.h"

#define NEXT(i) (((i)+1)%3)
#define PREV(i) (((i)+2)%3)

// Face class stores data for each face, used to render models,
// also used in subDivision to navigate the model once pointers are set.

class FaceSD;

class Face
{
public:
	Face(void);
	~Face(void);

	//virtual FaceSD* getF(int i){return NULL;}
	//virtual FaceSD* getChildren(int i){return NULL;}
	//virtual VertexSD* getV(int i){return NULL;}
	int vnum(VertexSD* vert);
	Face* nextFace(VertexSD*);
	Face* prevFace(VertexSD*);
	VertexSD* nextVert(VertexSD*);
	VertexSD* prevVert(VertexSD*);
	VertexSD* otherVert(VertexSD*,VertexSD*);

	vector<Vector3D*> vertexPos;
	vector<Vector4D*> vertexNorm;
	vector<Vector2D*> vertexUV;

	Face *f[3];
	Face *children[4];
	VertexSD *v[3];
};
