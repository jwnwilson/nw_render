#include "Material.h"

Material::Material()
{
	type= BASICM;
	emission=ColourRGB(0,0,0);
	ambientCoef=ColourRGB(0,0,0);
	textured=false;
	texture= NULL;
}

Material::Material(const ColourRGB& Acoeff,const ColourRGB& Dcoeff):
ambientCoef(Acoeff),emission(Dcoeff)
{
	type= 'l';
}
/*
Material::Material(const ColourRGB& Acoeff,const ColourRGB& Dcoeff,const ColourRGB& Ecoeff,const int& exp):
 ambientCoef(Acoeff),emission(Dcoeff)
{
	type= 'l';
}*/
Material::~Material(void)
{
	texture = NULL;
}
