#pragma once
#include "Buffer.h"
#include "ColourRGB.h"

// Will output image as required according to it's derived children

class OutputImage
{
public:
	OutputImage(void);
	OutputImage(const Buffer<ColourRGB>*);
	~OutputImage(void);
	virtual void readBuff(const Buffer<ColourRGB>*);
	virtual void outputImage(const char*){;}

protected:
	const Buffer<ColourRGB> *tempBuff;
};
