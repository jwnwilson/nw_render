#pragma once
#include "material.h"

class MaterialPhong :
	public Material
{
public:
	MaterialPhong(void);
	MaterialPhong(const ColourRGB&,const ColourRGB&,const ColourRGB&,const int&);
	void setDiffuse(const ColourRGB& d){diffuseCoef=d;}
	void setSpecular(const ColourRGB& a){specularCoef=a;}
	void setSpecularExp(const float& f){specularExp=f;}

	ColourRGB getSpecularC()const{return specularCoef;}
	float getSpecularExp()const{return specularExp;}
	ColourRGB getDiffuseC()const{return diffuseCoef;}
	~MaterialPhong(void);
private:
	ColourRGB  specularCoef, diffuseCoef;
	float specularExp;
};
