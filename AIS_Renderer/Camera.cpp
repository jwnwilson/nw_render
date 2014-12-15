#include "Camera.h"
#include "Matrix4D.h"

Camera::Camera(void)
{
	width=1024;
	height=512;
	initaliseSys();
	delBuffer=false;
	Vector3D BLtoTR;
	BLtoTR=screenTopRig-screenBotLef;
	screenCenter=screenBotLef+(BLtoTR*0.5);
	currentX = 0;
	currentY = 0;
	CamParams param;
	param.xStart = 0;
	param.xEnd = width;
	param.yStart = 0;
	param.yEnd = height;
	param.threadId = 0;
	params[0] = param;
	ColourPixCount = 0;
	
}
void Camera::initaliseSys()
{
	float ratio= width/height;
	eyePos=Vector3D(0,0,0);
	screenBotLef=Vector3D(-1*ratio,-1,1);
	screenBotRig=Vector3D(1*ratio,-1,1);
	screenTopLef=Vector3D(-1*ratio,1,1);
	screenTopRig=Vector3D(1*ratio,1,1);
	Vx=screenBotRig-screenBotLef;
	Vy=screenTopLef-screenBotLef;
}
void Camera::translate(const Vector3D& trans)
{
	eyePos=eyePos+trans;
	screenBotLef=screenBotLef+trans;
	screenBotRig=screenBotRig+trans;
	screenTopLef=screenTopLef+trans;
	screenTopRig=screenTopRig+trans;
	screenCenter=screenCenter+trans;
	Vx=screenBotRig-screenBotLef;
	Vy=screenTopLef-screenBotLef;
}
void Camera::setScreen(const Vector3D& BL,const Vector3D& BR,const Vector3D& TR,const Vector3D& TL)
{
	screenBotLef=BL;
	screenBotRig=BR;
	screenTopLef=TL;
	screenTopRig=TR;
	Vector3D BLtoTR;
	BLtoTR=screenTopRig-screenBotLef;
	screenCenter=screenBotLef+(BLtoTR*0.5);
	Vx=screenBotRig-screenBotLef;
	Vy=screenTopLef-screenBotLef;
}
void Camera::initialise(FrameBuffer* fb)
{
	if(fb!=NULL)
	{
		screen=fb;
		width=fb->getColour()->getWidth();
		height=fb->getColour()->getHeight();
	}
	else
	{
		screen= new FrameBuffer;
		screen->initialise(1024,512);
		width=1024;
		height=512;
		delBuffer=true;
	}
}
float Camera::findRot(const Vector2D& v1,const Vector2D& v2)
{
	float ang;
	if((v1.x==0&&v1.y==0)||(v2.x==0&&v2.y==0))
	{
		ang=0;
	}
	else
	{
		Vector2D normal;
		normal=Vector2D(-(v1.x),v1.y);
		if(normal.angle(v2)>90)
		{
			ang=v1.angle(v2);
		}
		else
		{
			ang=360-v1.angle(v2);
		}
	}

	return ang;
}

void Camera::setTarget(const Vector3D& target)
{
	Vector3D eyeToScreen,eyeToTarget;
	eyeToScreen=screenCenter-eyePos;
	eyeToTarget=target-eyePos;
	float degX,degY,degZ;
	Vector2D axis1(eyeToScreen.y,eyeToScreen.z),axis2(eyeToTarget.y,eyeToTarget.z);
	degX= findRot(axis1,axis2);
	axis1=Vector2D(eyeToScreen.x,eyeToScreen.z);
	axis2=Vector2D(eyeToTarget.x,eyeToTarget.z);
	degY= findRot(axis1,axis2);
	axis1=Vector2D(eyeToScreen.x,eyeToScreen.y);
	axis2=Vector2D(eyeToTarget.x,eyeToTarget.y);
	degZ= findRot(axis1,axis2);

	Matrix4D rotMat;
	rotMat.rotXYZ(degX,degY,degZ);
	Vector3D newsc1=screenBotLef-eyePos,newsc2=screenBotRig-eyePos,
		newsc3=screenTopLef-eyePos,newsc4=screenTopRig-eyePos;
	newsc1=rotMat*newsc1;
	newsc2=rotMat*newsc2;
	newsc3=rotMat*newsc3;
	newsc4=rotMat*newsc4;

	newsc1=newsc1+eyePos;
	newsc2=newsc2+eyePos;
	newsc3=newsc3+eyePos;
	newsc4=newsc4+eyePos;

	screenBotLef=newsc1;
	screenBotRig=newsc2;
	screenTopLef=newsc3;
	screenTopRig=newsc4;

	Vector3D BLtoTR;
	BLtoTR=screenTopRig-screenBotLef;
	screenCenter=screenBotLef+(BLtoTR*0.5);
	Vx=screenBotRig-screenBotLef;
	Vy=screenTopLef-screenBotLef;

}

Vector3D Camera::getRayVec(int x,int y)
{
	Vector3D rayVec;
	rayVec=(screenBotLef-eyePos)+(Vx*(float(x)/width))+(Vy*(float(y)/height));
	return rayVec;
}

Ray Camera::getRay(int x,int y)
{
	Ray ray1;
	ray1.position=eyePos;
	ray1.setDirection(getRayVec(x,y));
	return ray1;
}

Camera::~Camera(void)
{
	if(delBuffer==true)
	{
		delete screen;
	}
}
