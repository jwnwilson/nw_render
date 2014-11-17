#pragma once
#include "illuminationmodel.h"



class ModelPhong :
	public IlluminationModel
{
public:
	ModelPhong(void);
	~ModelPhong(void);
	ColourRGB shade(const Ray*,const vector<int>&);
};
