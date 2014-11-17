#include "FrameBuffer.h"

FrameBuffer::FrameBuffer(void)
{
}

FrameBuffer::~FrameBuffer(void)
{
}

void FrameBuffer::initialise(int w,int h)
{
	colourBuff.resize(w,h);
	//depthBuff.resize(w,h);
	//depthBuff.setAll(float(1));

}
