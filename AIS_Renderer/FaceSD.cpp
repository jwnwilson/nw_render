#include "FaceSD.h"

FaceSD::FaceSD(void)
{
	for(int i=0;i<3;i++)
	{
		f[i] = NULL;
	}
	for(int i=0;i<4;i++)
	{
		children[i] = NULL;
	}
	for(int i=0;i<3;i++)
	{
		v[i] = NULL;
	}
}

FaceSD::~FaceSD(void)
{
}

