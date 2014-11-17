// TGA file manager. Inport / export .tga files as binary streams.
#pragma once
#include "OutputImage.h"


class OutputTGA:
	public OutputImage
{
public:
	OutputTGA();
	OutputTGA(const Buffer<ColourRGB>*);
	void readBuff(const Buffer<ColourRGB>*);
	//readFile function obsolete but functional
	//void readFile(const char*);
	void outputImage(const char* s);
	~OutputTGA();
private:
	// WARNING. Remember to close file when using file pointers
	// Note: file closed after use now.
	//write to file closes file after executing
	void writeToFile(const char*);
	void readFile(FILE *);
	// WARNING. Remember to close file!!
	void writeToFile(FILE *);
	//file name

	Buffer<char> charBuff;

	
};