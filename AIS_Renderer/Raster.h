#pragma once
#include "Kernel.h"
#include "ColourRGB.h"
#include "Clipper.h"
#include "Scene.h"
#include "KernParam.h"


class Raster
{
public:
	Raster(void);
	void initalise(Scene&);
	void configure(Buffer<ColourRGB> *col,Buffer<float> *dep, Kernel *);
	virtual void draw(Model&);
	~Raster(void);
protected:
	bool checkPolygon();
	void sortVerts();
	void setShader();
	void drawPolygon();
	void drawTriangle(Vertex_R*[3]);
	//void flatTopTri(Vertex_R*[3]);
	//void flatBotTri(Vertex_R*[3]);

	vector<Vertex_R*> sortedVerts;
	vector<Vertex_R> rPolygon;
	Buffer<ColourRGB> *rColBuffer;
	Buffer<float> *rDepBuffer;
	Kernel *rasterKern;
	Clipper rasterClip;
	Model *rasterMod;
	Scene *rasterScene;
	KernParam kParam;


};
