#pragma once
#include "outputimage.h"
#include "Camera.h"
#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>

using namespace std;

class OutputWin :
	public OutputImage
{
public:
	OutputWin(void);
	OutputWin(int argc, char **argv);
	OutputWin(int x,int y);
	void outputImage(const char* c);
	void readBuff(const Buffer<ColourRGB>*);
	~OutputWin(void);

private:
	static void drawfunc(void);
	static void keyfunc(unsigned char, int, int);
	void myglinit(void);
	static void setpixel(char *buf, int x, int y, int r, int g, int b);

	static char *easel;
	static int width, height;
	static OutputWin *output;
	int winArgc;
	char **winArgv;
};
