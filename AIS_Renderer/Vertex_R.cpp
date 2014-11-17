#include "Vertex_R.h"

Vertex_R::Vertex_R(void)
{
	uv=Vector2D(0,0);
	worldPos= Vector3D(0,0,0);
	//hpos= Vector4D(0,0,0,0);
	//normal=hpos;
	//tangent=hpos;
}

Vertex_R::~Vertex_R(void)
{
}

void Vertex_R::setUV(Vector2D v)
{
	uv=v;
}
void Vertex_R::setWorld(Vector3D v)
{
	worldPos=v;
}
//void Vertex_R::setHpos(Vector4D v)
//{
//	hpos=v;
//}
void Vertex_R::setNorm(Vector4D v)
{
	normal=v;
}
void Vertex_R::setTan(Vector4D v)
{
	tangent=v;
}

bool Vertex_R::operator ==(const Vertex_R& vert)
{
	if(worldPos==vert.getWorld())
	{
		if(normal==vert.getNorm())
		{
			return true;
		}
	}
	return false;
}
//void Vertex_R::standardize()
//{
//	hpos= Vector4D((hpos.x/hpos.h),
//	(hpos.y/hpos.h),
//	(hpos.z/hpos.h),
//	1);
//}
Vertex_R Vertex_R::operator +(const Vertex_R& vert)
{
	Vertex_R newVert;
	newVert.setUV(uv+vert.getUV());
	newVert.setWorld(worldPos+vert.getWorld());
	//newVert.setHpos(hpos+vert.getHpos());
	newVert.setNorm(normal+vert.getNorm());
	newVert.setTan(tangent+vert.getTan());
	return newVert;
}
Vertex_R Vertex_R::operator -(const Vertex_R& vert)
{
	Vertex_R newVert;
	newVert.setUV(uv-vert.getUV());
	newVert.setWorld(worldPos-vert.getWorld());
	//newVert.setHpos(hpos-vert.getHpos());
	newVert.setNorm(normal-vert.getNorm());
	newVert.setTan(tangent-vert.getTan());
	return newVert;
}
Vertex_R Vertex_R::operator *(const float& flo)
{
	Vertex_R newVert;
	newVert.setUV(uv*flo);
	newVert.setWorld(worldPos*flo);
	//newVert.setHpos(hpos*flo);
	newVert.setNorm(normal*flo);
	newVert.setTan(tangent*flo);
	return newVert;
}