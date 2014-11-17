#include "MaterialLambert.h"

MaterialLambert::MaterialLambert(void)
{
	type=LAMBERTM;
	emission=ColourRGB(0,0,0);
	ambientCoef=ColourRGB(0,0,0);
	diffuseCoef=ColourRGB(0,0,0);
}
MaterialLambert::MaterialLambert(const ColourRGB& a,const ColourRGB& d)
{
	type=LAMBERTM;
	emission=ColourRGB(0,0,0);
	ambientCoef=a;
	diffuseCoef=d;

}

MaterialLambert::~MaterialLambert(void)
{
}
