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
	raySys.initalise(sc1,bounces);
	phongM.setScene(sc1);
	Vertex_R intersec;
	ColourRGB pixelCol;
	int const per25=width*0.25,const per50=width*0.5, const per75=width*0.75, const per100=width-1;
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
		if( w== per25 || w== per50 || w== per75 || w== per100)
		{
			cout<< ( numberToString(per25) + "% complete...") << endl;
			currentX = w;
			currentY = 0;
			cout<< "Time to render:"<< endl;
			timer = time(NULL);
			cout<< float(timer - start)/60 << " minutes." <<endl;
			break;
		}
	}

	return;
}