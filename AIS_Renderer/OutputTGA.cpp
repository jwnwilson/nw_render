#include "OutputTGA.h"
#include <string>
#include <fstream>

#ifndef BYTE
  #define BYTE unsigned char
#endif

#ifndef WORD
  #define WORD unsigned short
#endif

OutputTGA::OutputTGA()
{
	tempBuff=NULL;
	//tempBuff.resize(0);
}

OutputTGA::OutputTGA(const Buffer<ColourRGB>* inputBuffPtr)
{
	tempBuff=inputBuffPtr;
	/*
	tempBuff.resize(inputBuffPtr->getSize());
	for(int i=0;i<inputBuffPtr->getSize();i++)
	{
		tempBuff.setPix(i,inputBuffPtr->getPix(i));
	}
	tempBuff.setHeight(inputBuffPtr->getHeight());
	tempBuff.setWidth(inputBuffPtr->getWidth());
	*/

}

OutputTGA::~OutputTGA(void)
{
}

void OutputTGA::readBuff(const Buffer<ColourRGB>* inputBuffPtr)
{
	tempBuff=inputBuffPtr;
	charBuff.resize(inputBuffPtr->getSize()*3);
	for(int i=0;i<inputBuffPtr->getSize();i++)
	{
		charBuff.setPix(i*3,char(inputBuffPtr->getPix(i).getBlue()*255));
		charBuff.setPix((i*3)+1,char(inputBuffPtr->getPix(i).getGreen()*255));
		charBuff.setPix((i*3)+2,char(inputBuffPtr->getPix(i).getRed()*255));
	}
	charBuff.setHeight(inputBuffPtr->getHeight());
	charBuff.setWidth(inputBuffPtr->getWidth());

	/*tempBuff.resize(inputBuffPtr->getSize());
	for(int i=0;i<inputBuffPtr->getSize();i++)
	{
		tempBuff.setPix(i,inputBuffPtr->getPix(i));
	}
	tempBuff.setHeight(inputBuffPtr->getHeight());
	tempBuff.setWidth(inputBuffPtr->getWidth());*/
}
/*
void OutputTGA::readFile(FILE * fp)
{
	long fileSize;

	fseek(fp,0,SEEK_END);
	fileSize= ftell(fp);
	rewind(fp);

	tempBuff.resize(fileSize);
	fread(tempBuff.getBuffPtr(), 1,fileSize, fp);

}
void OutputTGA::readFile(const char* imageName)
{
	FILE * fp1 = fopen(imageName,"rb");
	readFile(fp1);

	fclose (fp1);
}*/

void OutputTGA::writeToFile(FILE * fp)
{

   //DEFINE HEADER
    BYTE idLength = 0;        //no Image Identification Field is included
    BYTE colourMapType = 0;       //no colour map
    BYTE dataType = 2;          //uncompressed RGB
    WORD colourMapOrigin = 0;
    WORD colourMapLength = 0;
    BYTE colourMapDepth = 0;
    WORD Xorig = 0;
    WORD Yorig = 0;
	WORD width = (charBuff.getWidth());
    WORD height = (charBuff.getHeight());
    BYTE bitsPerPixel = 24;
    BYTE imageDescriptionByte = 0;

	BYTE header[18];
	header[0]=idLength;
	header[1]=colourMapType;
	header[2]=dataType;
	header[3]=colourMapOrigin;
	header[4]=colourMapOrigin;
	header[5]=colourMapLength;
	header[6]=colourMapLength;
	header[7]=colourMapDepth;
	header[8]=Xorig;
	header[9]=Xorig;
	header[10]=Yorig;
	header[11]=Yorig;
	header[12]=width & 0x00FF;
	header[13]=(width & 0xFF00)/ 256;
	header[14]=height& 0x00FF;
	header[15]=(height& 0xFF00)/ 256;
	header[16]=bitsPerPixel;
	header[17]=imageDescriptionByte;

	fwrite(&header,1,18,fp);
	//fwrite(tempBuff.getBuffPtr(),1,tempBuff.getSize(),fp);
	fwrite(charBuff.getBuffPtr(),1,charBuff.getSize(),fp);
}
void OutputTGA::outputImage(const char* imageName)
{
	string temp;
	temp= imageName;
	temp=temp+ + ".tga";
	FILE * fp1 = fopen(&temp[0],"wb");
	writeToFile(fp1);

	fclose (fp1);
}



