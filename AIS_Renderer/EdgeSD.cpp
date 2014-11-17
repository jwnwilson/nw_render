#include "EdgeSD.h"

EdgeSD::EdgeSD(void)
{
	v[0]=NULL;
	v[1]=NULL;
	f[0]=NULL;
	f[1]=NULL;
	f0EdgeNum = -1;
}

EdgeSD::~EdgeSD(void)
{
}

EdgeSD::EdgeSD(VertexSD* v1, VertexSD* v2 )
{
	v[0] = min(v1,v2);
	v[1] = max(v1,v2);
	f[0]= f[1] = NULL;
	f0EdgeNum = -1;
}

bool EdgeSD::operator < (const EdgeSD & e2) const
{
	if(v[0] == e2.v[0])
	{
		return v[1] < e2.v[1];
	}
	return v[0] < e2.v[0];
};

