#pragma once
#include "material.h"

class MaterialLambert :
	public Material
{
public:
	MaterialLambert(void);
	MaterialLambert(const ColourRGB&,const ColourRGB&);
	void setDiffuse(const ColourRGB& d){diffuseCoef=d;}
	ColourRGB getDiffuseC()const{return diffuseCoef;}
	~MaterialLambert(void);
private:
	ColourRGB diffuseCoef;
};
