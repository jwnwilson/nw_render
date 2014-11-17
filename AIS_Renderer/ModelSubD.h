#pragma once
#include "modelAdv.h"
#include "FaceSD.h"
#include "EdgeSD.h"
#include "VertexSD.h"
#include <vector>



class ModelSubD :
	public ModelAdv
{
public:
	ModelSubD(void);
	~ModelSubD(void);


	/*vector<int>* getIndex(){return &index;}
	vector<Vertex_R>* getVertices(){return &vertices;}

	Vertex_R getVertices(int& i){return vertices[i];}
	int getIndex(int& i){return index[i];}
	int getVerticesSize()const{return vertices.size();}*/

};
