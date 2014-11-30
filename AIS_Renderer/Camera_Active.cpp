#include "Camera_Active.h"
#include "Ray.h"
#include "time.h"
#include <string>
#include <sstream>

template <typename T>
string numberToString ( T Number )
{
	stringstream ss;
	ss << Number;
	return ss.str();
}

Camera_Active::Camera_Active(void)
{
	bounces = 1;
}

Camera_Active::~Camera_Active(void)
{
}
void Camera_Active::RayBounces(int i)
{
	bounces = i;
}

void Camera_Active::drawScene(Scene* sc1)
{
	if( sc1 != NULL)
	{
		scene = sc1;
	}
	raySys.initalise(scene,bounces);
	phongM.setScene(scene);
	Vertex_R intersec;
	ColourRGB pixelCol;
	int const per25=width*0.25,const per50=width*0.5, const per75=width*0.75, const per100=width-1;
	int percent = 10;
	int step = width/percent;
	time_t timer;
	
	timer = time(NULL);
	int start = timer;
	
	cout<< "Starting render of scene." << endl;

	for(int w=currentX;w<width;w++)
	{
		for(int h=currentY;h<height;h++)
		{
			Ray ray1;
			ray1=getRay(w,h);
			pixelCol=raySys.rayIntoScene(ray1);
			screen->getColour()->setPix(w,h,pixelCol);
		}
		if( w % step == 0)
		{
			cout<< ( numberToString(((w / step) * percent)) + "% complete...") << endl;
			if (w== per100)
			{
				currentX = 0;
			}
			else
			{
				currentX = w+1;
			}
			currentY = 0;
			cout<< "Time to render:"<< endl;
			timer = time(NULL);
			cout<< float(timer - start)/60 << " minutes." <<endl;
			break;
		}
	}

	return;
}