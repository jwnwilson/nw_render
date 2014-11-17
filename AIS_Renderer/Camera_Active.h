#pragma once
#include "veiwsys.h"
#include "ModelPhong.h"

// Active camera used for rendering the scene

class Camera_Active :
	public VeiwSys
{
public:
	Camera_Active(void);
	void drawScene(Scene*);
	void RayBounces(int i);
	void setBounces(int b){bounces = b;}
	~Camera_Active(void);
private:
	int bounces;
	ModelPhong phongM;
	RaySystem raySys;
};
