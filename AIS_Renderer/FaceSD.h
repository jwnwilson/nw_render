#pragma once
#include "Face.h"

// Face class to be used with subDivisions, no longer used due to 
// problems caused with polymorphic behavior

class FaceSD:
		public Face
{
public:
	FaceSD(void);
	~FaceSD(void);

	/*FaceSD* getF(int i){return f[i];}
	FaceSD* getChildren(int i){return children[i];}
	VertexSD* getV(int i){return v[i];}

	void getF(int i){return f[i];}
	void getChildren(int i){return children[i];}
	void getV(int i){return v[i];}*/
	/*Face *nextFace(VertexSD*);
	Face *prevFace(VertexSD*);*/

	Face *f[3];
	Face *children[4];
	VertexSD *v[3];
};
