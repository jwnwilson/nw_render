#include "MaterialPhong.h"

MaterialPhong::MaterialPhong(void)
{
	type=PHONGM;
	emission=ColourRGB(0,0,0);
	ambientCoef=ColourRGB(0,0,0);
	diffuseCoef=ColourRGB(0,0,0);
	specularCoef=ColourRGB(0,0,0);
	specularExp=0;
}
MaterialPhong::MaterialPhong(const ColourRGB& a,const ColourRGB& d,const ColourRGB& s,const int& se)
{
	type=PHONGM;
	emission=ColourRGB(0,0,0);
	ambientCoef=a;
	diffuseCoef=d;
	specularCoef=s;
	specularExp=se;

}

MaterialPhong::~MaterialPhong(void)
{
}
