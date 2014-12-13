#pragma once
#include "Camera.h"
#include "Model.h"

// passive camera used to draw wireframe, needs updating as no longer compatable with renderer
// used for early tests and debugging.

class Camera_Passive :
	public Camera
{
public:
	Camera_Passive(void);
	void drawScene(Scene*, int threadId);
	~Camera_Passive(void);

private:
	int x,y;

	void drawWireFrame(Model* mesh);
	void setScreen(const Vector3D& BL,const Vector3D& BR,const Vector3D& TR,const Vector3D& TL);
	void vertToEyeScreenPos(const Vertex_R&);
	void drawLine(const Vertex_R&,const Vertex_R&);
	
};
