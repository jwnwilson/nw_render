#pragma once
#include "Scene.h"
#include "Camera_Active.h"
#include "Camera_Passive.h"
#include "FrameBuffer.h"
#include "OutputTGA.h"
#include "TimeLine.h"


// configure structure used to set render options
struct Configure{
	int w;
	int h;
	int bounces;
	char camera;
	char output;
};

class JWRT
{
public:
	JWRT(void);
	void initalise(int);
	void configure(Configure&);
	void render();
	~JWRT(void);
private:

	TimeLine timeLine;
	void setScene(int i);

	bool error;
	Configure config;
	Scene mainScene;
	VeiwSys *camera;
	FrameBuffer image;
	OutputImage* output;
};
