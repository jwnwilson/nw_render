#include "Camera.h"
#include "FrameBuffer.h"
#include "OutputWin.h"
#include "Camera_Passive.h"
#include "Camera_Active.h"
#include "Scene.h"
#include "implicitPlane.h"
#include "ImplicitSphere.h"
#include "LightPoint.h"
#include "LightArea.h"
#include "LightSpot.h"
#include "MaterialPhong.h"
#include "ModelSys.h"
#include "ModelAdv.h"
#include "ObjReader.h"
#include "JWRT.h"
#include <iostream>
#include <cstdlib>

using namespace std;

static JWRT *render;
static Configure c;

void saveRender()
{
	char res;
	//cout << render;
	cout << "Do you want to save the image to file?(y/n)";
	cin >> res;
	if( res == 'y' || res == 'Y')
	{
		c.output='t';
		render->configure(c);
		render->render();
	}
	cout << "Press any key to exit.";
	cin >> res;
}

int main(int argc, char **argV)
{
	int w=512,h=512;

	atexit(saveRender);
	
	cout<<"Please select a width and height for image:\n";
	cout<<"Width:\n";
	//cin>> w;
	cout<<"Height:\n";
	//cin>> h;
	cout<<"Please select a scene to render:\n";
	cout<<"1. Reflection \n";
	cout<<"2. Refraction \n";
	cout<<"3. softShadows \n";
	cout<<"4. customObjects \n";
	cout<<"5. subDivided cube \n";
	cout<<"6. animation \n";
	int choice;
	cin>> choice;

	if(w > 5000)
	{
		w = 5000;
	}
	if(w <=0)
	{
		w = 1024;
	}
	if(h > 5000)
	{
		h = 5000;
	}
	if(h <=0)
	{
		h = 512;
	}

	c.w=w;
	c.h=h;
	c.bounces=2;
	c.camera='a';
	c.output='w';

	render = new JWRT(argc, argV);
	//JWRT render;
	render->configure(c);
	render->initalise(choice);
	render->render();

	return 0;
}