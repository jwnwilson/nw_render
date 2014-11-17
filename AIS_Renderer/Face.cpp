#include "Face.h"

Face::Face(void)
{
}

Face::~Face(void)
{
}
int Face::vnum(VertexSD* vert)
{
	for(int i=0;i<3;i++)
	{
		if(v[i]==vert) return i;
	}
	cout<< "Error in Face::vnum function" << endl;
}

Face * Face::nextFace(VertexSD* vert)
{
	return f[vnum(vert)];
}
Face * Face::prevFace(VertexSD* vert)
{
	return f[PREV(vnum(vert))];
}
VertexSD* Face::nextVert(VertexSD* vert)
{
	return v[NEXT(vnum(vert))];
}
VertexSD* Face::prevVert(VertexSD* vert)
{
	return v[PREV(vnum(vert))];
}
VertexSD* Face::otherVert(VertexSD* v0,VertexSD* v1)
{
	for(int i=0; i<3;i++)
	{
		if(v[i] != v0 && v[i] != v1)
		{
			return v[i];
		}
	}
	cout<< "Error in face::otherVert" << endl;
	return NULL;
}
