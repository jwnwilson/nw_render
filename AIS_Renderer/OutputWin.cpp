#include "OutputWin.h"

char * OutputWin::easel=NULL;
int	OutputWin::width=NULL;
int	OutputWin::height=NULL;
OutputWin* OutputWin::output=NULL;

#include <windows.h>
#include <iostream>

DWORD WINAPI renderThread(LPVOID lpVariable)
{
	CamParams* params = (CamParams*)lpVariable;
	params->cam->setParams(*params, params->threadId);
	params->cam->drawScene(NULL, params->threadId);
	return 0;
}

OutputWin::OutputWin(void)
{
	easel=NULL;
	winArgc=0;
	winArgv=NULL;
	camera=NULL;
	output=this;
}

OutputWin::OutputWin(int argc, char **argv)
{
	winArgc = argc;
	winArgv = argv;
	easel = NULL;
	camera=NULL;
	output=this;
}

OutputWin::~OutputWin(void)
{
}
OutputWin::OutputWin(int x,int y)
{
}

void OutputWin::readBuff(const Buffer<ColourRGB>* inputBuffPtr)
{
	tempBuff=inputBuffPtr;

	/*tempBuff.resize(inputBuffPtr->getSize());
	for(int i=0;i<inputBuffPtr->getSize();i++)
	{
		tempBuff.setPix(i,inputBuffPtr->getPix(i));
	}
	tempBuff.setHeight(inputBuffPtr->getHeight());
	tempBuff.setWidth(inputBuffPtr->getWidth());*/
}

void OutputWin::outputImage(const char*c)
{
	// width and height of the window
	width = height = 512;

	// create a char buffer, 3 bytes per pixel of the window
	easel = new char[width*height*3];
  
	// initialize the glut system and create a window
	glutInitWindowSize(width, height);
	glutInit(&winArgc, winArgv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutCreateWindow("Render");

	// initialize some OpenGL state
	myglinit();
  
	// set callback functions.  drawfunc is the function that gets
	// called automatically as fast as possible.  keyfunc only is
	// invoked if the user hits a keyboard key.

	glutDisplayFunc(drawfunc);
	glutKeyboardFunc(keyfunc);

	//DWORD myThreadID1, myThreadID2 ;
	CamParams p1, p2;
	p1.threadId = 1;
	p1.xStart = 0;
	p1.xEnd = width/2;
	p1.yStart = 0;
	p1.yEnd = height;
	p1.cam = camera;
	p1.currentX = 0;
	p1.currentY = 0;

	p2.threadId = 2;
	p2.xStart = width/2;
	p2.xEnd = width;
	p2.yStart = 0;
	p2.yEnd = height;
	p2.cam = camera;
	p2.currentX = 0;
	p2.currentY = 0;

	HANDLE myHandle1 = CreateThread(0, 0, renderThread, &p1, 0, 0);
	HANDLE myHandle2 = CreateThread(0, 0, renderThread, &p2, 0, 0);
	// start the main glut loop, no code runs after this
	glutMainLoop();

	CloseHandle(myHandle1);
	CloseHandle(myHandle2);
}


void OutputWin::setpixel(char *buf, int x, int y, int r, int g, int b) {

  buf[(y*width+x)*3+0] = r;
  buf[(y*width+x)*3+1] = g;
  buf[(y*width+x)*3+2] = b;

}

// main draw function, gets called over and over, as fast as possible
void OutputWin::drawfunc(void) {
  int i,j;

  //cout << "in drawfunc" << endl;

  //output->camera->drawScene(NULL);

  // set pixels from temp buffer
  for (i=0; i<width; i++) {
    for (j=0; j<height; j++) {
      // set pixel at coord i,j to 'green'
	  ColourRGB buffPix = tempBuff->getPix(i,j);
      setpixel(easel, i, j, buffPix.getRed()*255, buffPix.getGreen()*255, buffPix.getBlue()*255);
    }
  }

  // drawpixels draws the rgb data stored in 'easel' to the screen
  glDrawPixels(width, height, GL_RGB, GL_UNSIGNED_BYTE, easel);


  // in double buffer mode so we swap to avoid a flicker
  glutSwapBuffers();

  // instruct event system to call 'drawfunc' again
  glutPostRedisplay();
}

void OutputWin::keyfunc(unsigned char k, int x, int y) {

  cout << "in keyfunc" << endl;

  switch (k) {
  case 27:
    // escape key
    exit(0);
    break;
  case GLUT_KEY_UP:
    // up arrow
    break;
  case 'a':
    // 'a' key
    break;
  }

}

// set some OpenGL state variables
void OutputWin::myglinit() {

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);

}
