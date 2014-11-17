#pragma once
#include "Buffer.h"
#include "ColourRGB.h"
#include <string>

// simple texture class to read and store a texture as a buffer.

class Texture
{
public:
	Texture(void);
	~Texture(void);
	bool readTexture(char* fileName);

	Buffer<ColourRGB> colourBuff;
	string fileName;
private:

	bool readTGA();
};
