#include "LineRaster.h"

LineRaster::LineRaster(void)
{
}

LineRaster::~LineRaster(void)
{
}

void LineRaster::draw(Model& d)
{
	rasterMod=&d;
	if(rasterMod->vertices.size()>0)
	{
		for(int i=0;i<rasterMod->index.size();i++)
		{
			if(rasterMod->index[i]!=-1)
			{
				rPolygon.push_back(rasterMod->vertices[rasterMod->index[i]]);		
			}
			else
			{	
				///////////////////////////////////////////////////
				//clip hpos, standardise hpos, veiwport map hpos
				///////////////////////////////////////////////////
				for(int a=0;a<rPolygon.size();a++)
				{
					rPolygon[a].standardize();
				}
				if (rasterClip.clipPolygon(rPolygon)==false)
				{
					for(int a=0;a<rPolygon.size();a++)
					{
						float x,y;
						//rPolygon[a].standardize();
						rPolygon[a].setNorm(rPolygon[a].getNorm().normalize());
						x=((rPolygon[a].getHpos().getX()+1)/2)*(rColBuffer->getWidth()-1);
						y=((rPolygon[a].getHpos().getY()+1)/2)*(rColBuffer->getHeight()-1);
						Vector4D temp(x,y,rPolygon[a].getHpos().getZ(),rPolygon[a].getHpos().getH());
						rPolygon[a].setHpos(temp);
					}
					setShader();
					/////////////////////////////////////////////////////////////////////////
					// draw lines
					/////////////////////////////////////////////////////////////////////////
					Vertex_R *verts[2];
					lineColour=ColourRGB(1,0,1);
					for(int i=0;i<(rPolygon.size()-1);i++)
					{	
						verts[0]=&rPolygon[i];
						verts[1]=&rPolygon[i+1];
						sortVerts(verts);
						drawLine(verts);
					}
					verts[0]=&rPolygon[rPolygon.size()-1];
					verts[1]=&rPolygon[0];
					sortVerts(verts);
					drawLine(verts);
				}
				rPolygon.clear();
				sortedVerts.clear();
			}
		}
	}
	rasterMod=NULL;

}


void LineRaster::sortVerts(Vertex_R *verts[2])
{
	if(verts[0]->getHpos().getY()>verts[1]->getHpos().getY())
	{
		Vertex_R *temp;
		temp=verts[0];
		verts[0]=verts[1];
		verts[1]=temp;
	}
	else if(verts[0]->getHpos().getY()==verts[1]->getHpos().getY())
	{
		if(verts[0]->getHpos().getX()>verts[1]->getHpos().getX())
		{
			Vertex_R *temp;
			temp=verts[0];
			verts[0]=verts[1];
			verts[1]=temp;
		}
	}
}

void LineRaster::drawLine(Vertex_R* p[2])
{
	float dy,dx;
	dy= p[1]->getHpos().getY()-p[0]->getHpos().getY();
	dx= p[1]->getHpos().getX()-p[0]->getHpos().getX();
	kParam.diffA=dx;
	kParam.diffB=dy;
	kParam.xstart=p[0]->getHpos().getX();
	kParam.xend=p[1]->getHpos().getX();
	kParam.ystart=p[0]->getHpos().getY();
	kParam.yend=p[1]->getHpos().getY();
	/*if(dy>dx)
	{
		if(dx==0)
		{
			kParam.diffA=0;
		}
		else
		{
			kParam.diffA=dy/dx;
		}
		kParam.xstart=p[0]->getHpos().getY();
		kParam.xend=p[1]->getHpos().getY();
		kParam.ystart=p[0]->getHpos().getX();
		kParam.yend=p[1]->getHpos().getX();
		
	}
	else
	{
		if(dy==0)
		{
			kParam.diffA=0;
		}
		else
		{
			kParam.diffA=dx/dy;
		}
		kParam.xstart=p[0]->getHpos().getX();
		kParam.xend=p[1]->getHpos().getX();
		kParam.ystart=p[0]->getHpos().getY();
		kParam.yend=p[1]->getHpos().getY();
	}*/
	
	rasterKern->drawLine(kParam,lineColour);
}
