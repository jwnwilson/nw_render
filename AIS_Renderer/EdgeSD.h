#pragma once
#include "VertexSD.h"
#include "FaceSD.h"

// Edge class is used to find face's niebours, not stored but used and 
// destroyed as required.

class EdgeSD
{
public:
	EdgeSD(void);
	~EdgeSD(void);

	EdgeSD(VertexSD*,VertexSD*);
	// used to organise edges in order of memory location
	// required for parts of sorting algorithm.
	bool operator < (const EdgeSD & e2) const;

	VertexSD *v[2];
	Face *f[2];
	int f0EdgeNum;
};
