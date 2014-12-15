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

void Camera_Active::setScene(Scene *s)
{
	scene = s;
	raySys.initalise(scene,bounces);
	phongM.setScene(scene);

}

void Camera_Active::drawScene(int threadId)
{
	ColourRGB pixelCol;
	int division = 1;
	int w = currentX ,h = currentY;
	int wStep = width/division;
	int hStep = height/division;
	int maxW, maxH;
	bool refresh = false;
	CamParams *param;
	if( threadId != 0){
		param = &params[threadId];
	}

	param->currentX == 0 ? param->currentX = param->xStart : param->currentX = param->currentX; 
	param->currentY == 0 ? param->currentY = param->yStart : param->currentY = param->currentY; 
	//time_t timer;
	
	//timer = time(NULL);
	//int start = timer;
	
	//cout<< "Starting render of scene." << endl;
	if(param->currentX + wStep <= param->xEnd)
	{
		maxW = (param->currentX + wStep);
	}
	else
	{
		maxW = param->xEnd;
	}
	if(param->currentY + hStep <= param->yEnd)
	{
		maxH = (param->currentY + hStep);
	} 
	else
	{
		maxH = param->yEnd;
	}
	
	for(w=param->currentX;w<maxW;w++)
	{
		for(h=param->currentY;h<maxH;h++)
		{
			//cout<< "ThreadId: " << threadId;
			//cout << endl;
			//cout << "w and h values: " << w << "," << h;
			//cout << endl;
			Ray ray1;
			ray1=getRay(w,h);
			pixelCol=raySys.rayIntoScene(ray1);
			//pixelCol = ColourRGB(1.0,0.0,0.0);
			screen->getColour()->setPix(w,h,pixelCol);
		}
	}
	ColourPixCount += ((maxW - param->currentX) * (maxH - param->currentY));
 	cout<< ( numberToString(float(ColourPixCount) / (width * height) *100) + "% complete...") << endl;
	if (w== width && refresh)
	{
		param->currentX = 0;
		param->currentY = 0;
	}
	else
	{
		if(h == height && w == width)
		{
			param->currentX = 0;
			param->currentY = 0;
		}
		if(h == height){
			param->currentX = w;
			param->currentY = 0;
		}
		else{
			param->currentY = h;
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