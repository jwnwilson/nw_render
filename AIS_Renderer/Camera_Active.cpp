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
	int division = 1;
	int w = currentX ,h = currentY;
	int wStep = width/division;
	int hStep = height/division;
	int maxW, maxH;
	bool refresh = false;
	//time_t timer;
	
	//timer = time(NULL);
	//int start = timer;
	
	//cout<< "Starting render of scene." << endl;
	if(currentX + wStep <= width)
	{
		maxW = (currentX + wStep);
	}
	else
	{
		maxW = width;
	}
	if(currentY + hStep <= height)
	{
		maxH = (currentY + hStep);
	} 
	else
	{
		maxH = height;
	}
	
	for(w=currentX;w<maxW;w++)
	{
		for(h=currentY;h<maxH;h++)
		{
			Ray ray1;
			ray1=getRay(w,h);
			pixelCol=raySys.rayIntoScene(ray1);
			screen->getColour()->setPix(w,h,pixelCol);
		}
	}
	int percX = (((float(currentX) / width) * 100));
	int percY = (((float(h) / height) * 100)/ division);
 	cout<< ( numberToString(percX + percY) + "% complete...") << endl;
	if (w== width && refresh)
	{
		currentX = 0;
		currentY = 0;
	}
	else
	{
		if(h == height && w == width)
		{
			currentX = 0;
			currentY = 0;
		}
		if(h == height){
			currentX = w;
			currentY = 0;
		}
		else{
			currentY = h;
			//currentX = 0;
		}		
	}
	
	//cout<< "Time to render:"<< endl;
	//timer = time(NULL);
	//cout<< float(timer - start)/60 << " minutes." <<endl;
		//}
	//}

	return;
}