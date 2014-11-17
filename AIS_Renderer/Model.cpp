#include "Model.h"
#include "ImplicitPlane.h"
#include "ImplicitCube.h"
#include <limits>

Model::Model(void)
{
	material=NULL;
	boundingShape=NULL;
	/*float mat1[4][4]= 
	{{1,0,0,0},
	{0,1,0,0},
	{0,0,1,0},
	{0,0,0,1}};*/

	refractionIndex = 0;
	//Matrix4D mat2(mat1);
	//worldTrans=mat2;
	subD=0;

	implicit=false;
	smooth = true;
}

Model::~Model(void)
{
	if(boundingShape!=NULL)
	{
		delete boundingShape;
	}
}
