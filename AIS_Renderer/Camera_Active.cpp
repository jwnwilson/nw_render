#include "Camera_Active.h"
#include "Ray.h"
#include "time.h"

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

	for(int w=0;w<width;w++)
	{
		for(int h=0;h<height;h++)
		{
			Ray ray1;
			ray1=getRay(w,h);
			pixelCol=raySys.rayIntoScene(ray1);
			screen->getColour()->setPix(w,h,pixelCol);
		}
		if( w== per25)
			cout<< "25% complete..." << endl;
		if( w== per50)
			cout<< "50% complete..." << endl;
		if( w== per75)
			cout<< "75% complete..." << endl;
		if( w== per100)
		{
			char cont;
			cout<< "100% complete." << endl;
			cout<< "Time to render:"<< endl;
			timer = time(NULL);
			cout<< float(timer - start)/60 << " minutes." <<endl;
			cout<< "Enter Any key to continue\n";
			cin >>cont;
		}
	}
}