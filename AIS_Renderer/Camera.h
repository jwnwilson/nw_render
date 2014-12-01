#pragma once
#include "Vector3D.h"
#include "Vertex_R.h"
#include "ColourRGB.h"
#include "FrameBuffer.h"
#include "Ray.h"
#include "Scene.h"
#include "RaySystem.h"
#include "OutputImage.h"
#include <math.h>

// used to controll camera's in the scene.

class Camera
{
public:
	Camera(void);
	void initialise(FrameBuffer *);	
	void setEye(const Vector3D& a){eyePos=a;}
	void setScreen(const Vector3D& BL,const Vector3D& BR,const Vector3D& TR,const Vector3D& TL);
	void translate(const Vector3D& trans);
	void setTarget(const Vector3D& a);
	void setScene(Scene *s){scene=s;}
	virtual void setBounces(int b){;}
	virtual void drawScene(Scene* s){;}
	Ray getRay(int x,int y);
	
	//void setScreenRes(int x,int y){width=x;height=y;}
	~Camera(void);
protected:
	
	float findRot(const Vector2D&,const Vector2D&);
	void initaliseSys();
	Vector3D getRayVec(int x,int y);
	Vector3D eyePos,screenBotLef,screenBotRig,screenTopLef,screenTopRig,
		Vx,Vy,screenCenter;
	int width,height;
	FrameBuffer *screen;
	Scene *scene;
	bool delBuffer;
	int currentX, currentY;


};
