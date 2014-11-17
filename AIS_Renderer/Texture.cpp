#include "Texture.h"
#include <fstream>

Texture::Texture(void)
{
}

Texture::~Texture(void)
{
	fileName = "";
}
bool Texture::readTexture(char* name)
{
	fileName = name;
	string extension;
	int length= fileName.length();
	char *temp = &fileName[length-3];
	extension = temp;

	if( extension == "tga" || extension =="TGA" )
	{
		if (readTGA() == true)
		{
			return true;
		}
	}

	return false;

}
bool Texture::readTGA()
{
	unsigned short width = 0, height = 0;
	unsigned char length = 0;     // The length in bytes to the pixels
	unsigned char imageType = 0;  // The image type (RLE, RGB, Alpha...)
	unsigned char bits = 0;       // The bits per pixel for the image (16, 24, 32)
	FILE *pFile = NULL;
	int channels = 0;             // The channels of the image (3 = RGA : 4 = RGBA)
	int stride = 0;               // The stride (channels * width)
	int i = 0;                    

	if ((pFile = fopen (&fileName[0], "rb")) == NULL)
	{
		cout << "error reading" << fileName << endl;
		return false;
    }

    // Read in the length in bytes from the header to the pixel data
    fread (&length, sizeof (unsigned char), 1, pFile);

    // Jump over one byte
    fseek (pFile, 1, SEEK_CUR);

    // Read in the imageType (RLE, RGB, etc...)
    fread (&imageType, sizeof (unsigned char), 1, pFile);

    // Skip past general information we don't care about
    fseek (pFile, 9, SEEK_CUR);

    // Read the width, height and bits per pixel (16, 24 or 32)
    fread (&width, sizeof (unsigned short), 1, pFile);

    fread (&height, sizeof (unsigned short), 1, pFile);

    fread (&bits, sizeof (unsigned char), 1, pFile);

    // Now we move the file pointer to the pixel data
    fseek (pFile, length + 1, SEEK_CUR);

    // Check if the image is RLE compressed or not
    if (imageType == 2 ||imageType == 10 )
    {
		/* Allocate space for the image */
		colourBuff.resize(width,height);
		char r,g,b;
		int d,e,f;
		float x,y,z;

		for( i = 0; i< colourBuff.getSize(); i++)
		{
			
			fread(&b,1,sizeof(char),pFile);
			fread(&g,1,sizeof(char),pFile);
			fread(&r,1,sizeof(char),pFile);
			if( r < 0)
				d = 256 + int(r);
			else
				d=int(r);
			if( g < 0)
				e = 256 + int(g);
			else
				e=int(g);
			if( b < 0)
				f = 256 + int(b);
			else
				f=int(b);

			x = float(d)/255;
			y = float(e)/255;
			z = float(f)/255;
			colourBuff.setPix(i,ColourRGB(x,y,z));

		}	
    }
	else
	{
		cout<<"Don't do compressed TGA files, "<< fileName <<" is compressed."<<endl;
		return false;
	}

    // Close the file pointer that opened the file
    fclose (pFile);

	return true;

}
