#pragma once
#include "Vector2D.h"
#include "Vector3D.h"
#include "Vector4D.h"

// Vertex Class used originally before changing to VertexSD
// Used in this renderer to store data temporarally such as points
// a ray will interact with.

class Vertex_R
{
public:
	Vertex_R(void);
	~Vertex_R(void);

	void setUV(Vector2D);
	void setWorld(Vector3D);
	void setNorm(Vector4D);
	void setTan(Vector4D);

	Vector2D getUV()const{return uv;}
	Vector3D getWorld()const{return worldPos;}
	Vector4D getNorm()const{return normal;}
	Vector4D getTan()const{return tangent;}
	
	void standardize();
	bool operator ==(const Vertex_R&);
	Vertex_R operator +(const Vertex_R&);
	Vertex_R operator -(const Vertex_R&);
	Vertex_R operator *(const float&);
	
private:
	//note: tangent unused so far.
	Vector2D uv;
	Vector3D worldPos;
	Vector4D normal,tangent;

};
