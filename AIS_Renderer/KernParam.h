#pragma once
#include "Vector4D.h"

class KernParam
{
public:
	KernParam(void);
	~KernParam(void);
	float xstart,xend,ystart,yend,diffA,
		diffB,zA,zB,zDiffA,zDiffB;
	Vector4D posA,posB,posDiffA,posDiffB,normA,normB,normDiffA,normDiffB;
};
