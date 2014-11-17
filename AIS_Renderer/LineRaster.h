#pragma once
#include "raster.h"

class LineRaster :
	public Raster
{
public:
	LineRaster(void);
	void draw(Model&);
	void sortVerts(Vertex_R *[2]);
	void drawLine(Vertex_R*[2]);
	void setLineColour(ColourRGB& c){lineColour=c;}
	~LineRaster(void);
private:
	ColourRGB lineColour;

};
