#pragma once
#include "outputimage.h"
//#include "Window.h"

// Uses Tyrone Davidson's window class to output renders used for debugging perposes.

// Window causes program to crash after it has been closed, for unknown reason. Will have
// to talk to Tyrone about it.

// disabled in release version due to not have release libraries for Window object

class OutputWin :
	public OutputImage
{
public:
	OutputWin(void);
	OutputWin(int x,int y);
	void outputImage(const char* c);
	~OutputWin(void);
};
