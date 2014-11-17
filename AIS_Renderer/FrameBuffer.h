#pragma once
#include "Buffer.h"
#include "ColourRGB.h"

// holds main image.

class FrameBuffer
{
public:
	FrameBuffer(void);
	~FrameBuffer(void);
	void initialise(int w,int h);
	Buffer<ColourRGB>* getColour(){return &colourBuff;}
	//Buffer<float>* getDepth(){return &depthBuff;}
private:
	Buffer<ColourRGB> colourBuff;
	//Buffer<float> depthBuff;
};
