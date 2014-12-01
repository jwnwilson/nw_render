#include "OutputWin.h"

char * OutputWin::easel=NULL;
int	OutputWin::width=NULL;
int	OutputWin::height=NULL;
OutputWin* OutputWin::output=NULL;

#include <windows.h>
#include <iostream>

DWORD WINAPI myThread(LPVOID lpVariable)
{
	OutputWin *output = OutputWin::getOutput();
	Camera * cam = output->getCamera();
	cam->drawScene(NULL);
	return 0;
}

/*int main(int argc, char* argv[])
{
	using namespace std;

	unsigned int myCounter = 0;
	DWORD myThreadID, myThreadID2, myThreadID3;
	HANDLE myHandle = CreateThread(0, 0, myThread, &myCounter, 0, &myThreadID);
	HANDLE myHandle2 = CreateThread(0, 0, myThread, &myCounter, 0, &myThreadID2);
	HANDLE myHandle3 = CreateThread(0, 0, myThread, &myCounter, 0, &myThreadID3);
	char myChar = ' ';
	while(myChar != 'q') {
		cout << myCounter << endl;
		myChar = getchar();
	}
	
	CloseHandle(myHandle);
	CloseHandle(myHandle2);
	CloseHandle(myHandle3);
	return 0;
}*/

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
	glutCreateWindow("example");

	// initialize some OpenGL state
	myglinit();
  
	// set callback functions.  drawfunc is the function that gets
	// called automatically as fast as possible.  keyfunc only is
	// invoked if the user hits a keyboard key.

	glutDisplayFunc(drawfunc);
	glutKeyboardFunc(keyfunc);

	DWORD myThreadID;
	HANDLE myHandle = CreateThread(0, 0, myThread, NULL, 0, &myThreadID);
  
	// start the main glut loop, no code runs after this
	glutMainLoop();

	CloseHandle(myHandle);
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
