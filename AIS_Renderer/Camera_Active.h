#pragma once
#include "Camera.h"
#include "ModelPhong.h"

// Active camera used for rendering the scene

class Camera_Active :
	public Camera
{
public:
	Camera_Active(void);
	void drawScene(int threadId);
	void RayBounces(int i);
	void setBounces(int b){bounces = b;}
	void setScene(Scene *s);
	~Camera_Active(void);
private:
	int bounces;
	ModelPhong phongM;
	RaySystem raySys;
};
