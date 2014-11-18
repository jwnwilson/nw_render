#include "OutputImage.h"

const Buffer<ColourRGB> * OutputImage::tempBuff;

OutputImage::OutputImage(void)
{
	tempBuff=NULL;
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
