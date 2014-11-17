#include "OutputImage.h"

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
