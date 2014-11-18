#include "OutputWin.h"

char * OutputWin::easel=NULL;
int	OutputWin::width=NULL;
int	OutputWin::height=NULL;

OutputWin::OutputWin(void)
{
	easel = NULL;
	winArgc = 0;
	winArgv = '';
}

OutputWin::OutputWin(int argc, char **argv)
{
	winArgc = argc;
	winArgv = argv;
	easel = NULL;
}

OutputWin::~OutputWin(void)
{
}
OutputWin::OutputWin(int x,int y)
{
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
  
	// start the main glut loop, no code runs after this
	glutMainLoop();
}


void OutputWin::setpixel(char *buf, int x, int y, int r, int g, int b) {

  buf[(y*width+x)*3+0] = r;
  buf[(y*width+x)*3+1] = g;
  buf[(y*width+x)*3+2] = b;

}

// main draw function, gets called over and over, as fast as possible
void OutputWin::drawfunc(void) {
  int i,j;

  cout << "in drawfunc" << endl;

  // set first half of buffer to red
  for (i=0; i<width/2; i++) {
    for (j=0; j<height; j++) {
      // set pixel at coord i,j to 'red'
      setpixel(easel, i, j, 255, 0, 0);
    }
  }

  // set second half to green
  for (i=width/2; i<width; i++) {
    for (j=0; j<height; j++) {
      // set pixel at coord i,j to 'green'
      setpixel(easel, i, j, 0, 255, 0);
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
