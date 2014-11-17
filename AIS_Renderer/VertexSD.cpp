#include "VertexSD.h"
#include "Face.h"

VertexSD::VertexSD(void)
{
	startFace = NULL;
	child= NULL;
	uv = NULL;
	worldPos = NULL;
	normal = NULL;
}

VertexSD::~VertexSD(void)
{
}

int VertexSD::valence()
{
	Face *f = startFace;
	if(!boundary)
	{
		int nf = 1;
		while((f=f->nextFace(this)) != startFace)
			nf++;
		return nf;
	}
	else
	{
		int nf = 1;
		while((f=f->nextFace(this)) != NULL)
			nf++;
		f = startFace;
		while((f=f->prevFace(this)) != NULL)
			nf++;
		return nf+1;
	}
}