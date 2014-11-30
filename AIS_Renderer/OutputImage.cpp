#include "OutputImage.h"

const Buffer<ColourRGB> * OutputImage::tempBuff;
//const Camera * OutputImage::camera=NULL;

OutputImage::OutputImage(void)
{
	tempBuff=NULL;
	camera=NULL;
}
OutputImage::OutputImage(const Buffer<ColourRGB>* b)
{
	tempBuff=b;
}

OutputImage::~OutputImage(void)
{
}

void OutputImage::readBuff(const Buffer<ColourRGB>* b)
{
	tempBuff=b;
}
