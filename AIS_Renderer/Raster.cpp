#include "Raster.h"
#include "Line.h"

Raster::Raster(void)
{
	rColBuffer=NULL;
	rDepBuffer=NULL;
	rasterKern=NULL;
	rasterMod=NULL;
	rasterScene=NULL;
}

Raster::~Raster(void)
{
	if(rasterKern!=NULL)
	{
		delete rasterKern;
	}
}

void Raster::initalise(Scene& s)
{
	rasterScene=&s;
}

void Raster::configure(Buffer<ColourRGB> *a,Buffer<float> *b, Kernel *c)
{
	rColBuffer=a;
	rDepBuffer=b;
	rasterKern=c;
	rasterKern->initalise(rColBuffer,rDepBuffer);
	
}

void Raster::draw(Model& d)
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
						rPolygon[a].setNorm(rPolygon[a].getNorm().normalize());
						x=((rPolygon[a].getHpos().getX()+1)/2)*(rColBuffer->getWidth()-1);
						y=((rPolygon[a].getHpos().getY()+1)/2)*(rColBuffer->getHeight()-1);
						Vector4D temp(x,y,rPolygon[a].getHpos().getZ(),rPolygon[a].getHpos().getH());
						rPolygon[a].setHpos(temp);
					}
					sortVerts();
					setShader();
					drawPolygon();
				}
				rPolygon.clear();
				sortedVerts.clear();
			}
		}
	}
	rasterMod=NULL;

}
void Raster::drawPolygon()
{
	
	for(int i=0;i<(sortedVerts.size()-2);i++)
	{
		Vertex_R *verts[3];
		verts[0]=sortedVerts[0];
		verts[1]=sortedVerts[i+1];
		verts[2]=sortedVerts[i+2];
		drawTriangle(verts);
	}

}
void Raster::sortVerts()
{
	/*
	int lowest;
	lowest=0;
	for(int a=0;a<rPolygon.size();a++)
	{
		for(int b=a+1;b<rPolygon.size();b++)
		{
			if(rPolygon[a].getHpos().getY()>rPolygon[b].getHpos().getY())
			{
				lowest=b;
			}
			else if(rPolygon[a].getHpos().getY()==rPolygon[b].getHpos().getY())
			{
				if(rPolygon[a].getHpos().getX()>rPolygon[b].getHpos().getX())
				{
					lowest=b;
				}
			}
		}
	}*/
	int lowest=0;
	for(int i=1;i<rPolygon.size();i++)
	{
		if(rPolygon[lowest].getHpos().getY()>rPolygon[i].getHpos().getY())
		{
			lowest=i;
		}
		else if(rPolygon[lowest].getHpos().getY()==rPolygon[i].getHpos().getY())
		{
			if(rPolygon[lowest].getHpos().getX()>rPolygon[i].getHpos().getX())
			{
				lowest=i;
			}
		}
	}
	for(lowest;lowest<rPolygon.size();lowest++)
	{
		sortedVerts.push_back(&rPolygon[lowest]);
	}
	int i=0;
	while(sortedVerts.size()<rPolygon.size())
	{
		sortedVerts.push_back(&rPolygon[i]);
		i++;
	}


}
void Raster::drawTriangle(Vertex_R* p[3])
{
	//if 2nd point is highest
	if(p[2]->getHpos().getY()<p[1]->getHpos().getY())
	{
		Line line1(p[0]->getHpos().getX(),p[0]->getHpos().getY(),p[2]->getHpos().getX(),p[2]->getHpos().getY()),
			line2(p[0]->getHpos().getX(),p[0]->getHpos().getY(),p[1]->getHpos().getX(),p[1]->getHpos().getY());
		kParam.xstart=p[0]->getHpos().getX();
		kParam.xend=p[0]->getHpos().getX();
		kParam.ystart=p[0]->getHpos().getY();
		kParam.yend=p[2]->getHpos().getY();
		kParam.diffA=line1.dydx();
		kParam.diffB=line2.dydx();
		kParam.zA=p[0]->getHpos().getZ();
		kParam.zB=p[0]->getHpos().getZ();
		kParam.zDiffA=(p[2]->getHpos().getZ()-p[0]->getHpos().getZ())/(p[2]->getHpos().getY()-p[0]->getHpos().getY());
		kParam.zDiffB=(p[1]->getHpos().getZ()-p[0]->getHpos().getZ())/(p[1]->getHpos().getY()-p[0]->getHpos().getY());
		kParam.posA=p[0]->getWorld();
		kParam.posB=p[0]->getWorld();
		kParam.posDiffA=(p[2]->getWorld()-p[0]->getWorld())*(float(1)/(p[2]->getHpos().getY()-p[0]->getHpos().getY()));
		kParam.posDiffB=(p[1]->getWorld()-p[0]->getWorld())*(float(1)/(p[1]->getHpos().getY()-p[0]->getHpos().getY()));
		kParam.normA=p[0]->getNorm();
		kParam.normB=p[0]->getNorm();
		kParam.normDiffA=(p[2]->getNorm()-p[0]->getNorm())*(float(1)/(p[2]->getHpos().getY()-p[0]->getHpos().getY()));
		kParam.normDiffB=(p[1]->getNorm()-p[0]->getNorm())*(float(1)/(p[1]->getHpos().getY()-p[0]->getHpos().getY()));
	
		rasterKern->draw(kParam);

		line1=Line(p[2]->getHpos().getX(),p[2]->getHpos().getY(),p[1]->getHpos().getX(),p[1]->getHpos().getY());
		kParam.ystart=p[2]->getHpos().getY();
		kParam.xstart=p[2]->getHpos().getX();
		kParam.yend=p[1]->getHpos().getY();
		kParam.normA=p[2]->getNorm();
		kParam.zA=p[2]->getHpos().getZ();
		kParam.posA=p[2]->getWorld();
		kParam.diffA=line1.dydx();
		kParam.zDiffA=(p[1]->getHpos().getZ()-p[2]->getHpos().getZ())/(p[1]->getHpos().getY()-p[2]->getHpos().getY());
		kParam.posDiffA=(p[1]->getWorld()-p[2]->getWorld())*(float(1)/(p[1]->getHpos().getY()-p[2]->getHpos().getY()));
		kParam.normDiffA=(p[1]->getNorm()-p[2]->getNorm())*(float(1)/(p[1]->getHpos().getY()-p[2]->getHpos().getY()));
		
		rasterKern->draw(kParam);	
	}
	// if 3rd point is highest
	else if(p[2]->getHpos().getY()>p[1]->getHpos().getY())
	{
		Line line1(p[0]->getHpos().getX(),p[0]->getHpos().getY(),p[2]->getHpos().getX(),p[2]->getHpos().getY()),
			line2(p[0]->getHpos().getX(),p[0]->getHpos().getY(),p[1]->getHpos().getX(),p[1]->getHpos().getY());
		kParam.xstart=p[0]->getHpos().getX();
		kParam.xend=p[0]->getHpos().getX();
		kParam.ystart=p[0]->getHpos().getY();
		kParam.yend=p[1]->getHpos().getY();
		kParam.diffA=line1.dydx();
		kParam.diffB=line2.dydx();
		kParam.zA=p[0]->getHpos().getZ();
		kParam.zB=p[0]->getHpos().getZ();
		kParam.zDiffA=(p[2]->getHpos().getZ()-p[0]->getHpos().getZ())/(p[2]->getHpos().getY()-p[0]->getHpos().getY());
		kParam.zDiffB=(p[1]->getHpos().getZ()-p[0]->getHpos().getZ())/(p[1]->getHpos().getY()-p[0]->getHpos().getY());
		kParam.posA=p[0]->getWorld();
		kParam.posB=p[0]->getWorld();
		kParam.posDiffA=(p[2]->getWorld()-p[0]->getWorld())*(float(1)/(p[2]->getHpos().getY()-p[0]->getHpos().getY()));
		kParam.posDiffB=(p[1]->getWorld()-p[0]->getWorld())*(float(1)/(p[1]->getHpos().getY()-p[0]->getHpos().getY()));
		kParam.normA=p[0]->getNorm();
		kParam.normB=p[0]->getNorm();
		kParam.normDiffA=(p[2]->getNorm()-p[0]->getNorm())*(float(1)/(p[2]->getHpos().getY()-p[0]->getHpos().getY()));
		kParam.normDiffB=(p[1]->getNorm()-p[0]->getNorm())*(float(1)/(p[1]->getHpos().getY()-p[0]->getHpos().getY()));
	
		rasterKern->draw(kParam);

		line1=Line(p[1]->getHpos().getX(),p[1]->getHpos().getY(),p[2]->getHpos().getX(),p[2]->getHpos().getY());
		kParam.ystart=p[1]->getHpos().getY();
		kParam.xend=p[1]->getHpos().getX();
		kParam.yend=p[2]->getHpos().getY();
		kParam.zB=p[1]->getHpos().getZ();
		kParam.posB=p[1]->getWorld();
		kParam.normB=p[1]->getNorm();
		kParam.diffB=line1.dydx();
		kParam.zDiffB=(p[2]->getHpos().getZ()-p[1]->getHpos().getZ())/(p[2]->getHpos().getY()-p[1]->getHpos().getY());
		kParam.posDiffB=(p[2]->getWorld()-p[1]->getWorld())*(float(1)/(p[2]->getHpos().getY()-p[1]->getHpos().getY()));
		kParam.normDiffB=(p[2]->getNorm()-p[1]->getNorm())*(float(1)/(p[2]->getHpos().getY()-p[1]->getHpos().getY()));
		
		rasterKern->draw(kParam);

	}
	//if flat top triangle
	else if(p[1]->getHpos().getY()==p[2]->getHpos().getY())
	{
		Line line1(p[0]->getHpos().getX(),p[0]->getHpos().getY(),p[2]->getHpos().getX(),p[2]->getHpos().getY()),
			line2(p[0]->getHpos().getX(),p[0]->getHpos().getY(),p[1]->getHpos().getX(),p[1]->getHpos().getY());
		kParam.xstart=p[0]->getHpos().getX();
		kParam.xend=p[0]->getHpos().getX();
		kParam.ystart=p[0]->getHpos().getY();
		kParam.yend=p[2]->getHpos().getY();
		kParam.diffA=line1.dydx();
		kParam.diffB=line2.dydx();
		kParam.zA=p[0]->getHpos().getZ();
		kParam.zB=p[0]->getHpos().getZ();
		kParam.zDiffA=(p[2]->getHpos().getZ()-p[0]->getHpos().getZ())/(p[2]->getHpos().getY()-p[0]->getHpos().getY());
		kParam.zDiffB=(p[1]->getHpos().getZ()-p[0]->getHpos().getZ())/(p[1]->getHpos().getY()-p[0]->getHpos().getY());
		kParam.posA=p[0]->getWorld();
		kParam.posB=p[0]->getWorld();
		kParam.posDiffA=(p[2]->getWorld()-p[0]->getWorld())*(float(1)/(p[2]->getHpos().getY()-p[0]->getHpos().getY()));
		kParam.posDiffB=(p[1]->getWorld()-p[0]->getWorld())*(float(1)/(p[1]->getHpos().getY()-p[0]->getHpos().getY()));
		kParam.normA=p[0]->getNorm();
		kParam.normB=p[0]->getNorm();
		kParam.normDiffA=(p[2]->getNorm()-p[0]->getNorm())*(float(1)/(p[2]->getHpos().getY()-p[0]->getHpos().getY()));
		kParam.normDiffB=(p[1]->getNorm()-p[0]->getNorm())*(float(1)/(p[1]->getHpos().getY()-p[0]->getHpos().getY()));

	
		rasterKern->draw(kParam);

	}
	else 
	{
		cout<<"Problem with drawTriangle function\n";
	}
	
}
/*
void Raster::flatTopTri(Vertex_R* p[3])
{

	float zDA=(p[2]->getHpos().getZ()-[p0]->getHpos().getZ())/(p[2]->getHpos().getY()-p[0]->getHpos().getY());
	float zDB=(p[1]->getHpos().getZ()-[p0]->getHpos().getZ())/(p[1]->getHpos().getY()-p[0]->getHpos().getY());
	Line line1(p[0]->getHpos()->getX,p[0]->getHpos()->getY,p[2]->getHpos()->getX,p[2]->getHpos()->getY),
		line2(p[0]->getHpos()->getX,p[0]->getHpos()->getY,p[1]->getHpos()->getX,p[1]->getHpos()->getY);
	rasterKern->draw(p[0]->getHpos()->getX(),p[0]->getHpos()->getX(),p[0]->getHpos()->getY(),p[1]->getHpos()->getY(),
		line1.dydx(),line2.dydx(),p[0]->getHpos()->getZ(),p[0]->getHpos()->getZ(),zDA,zDB);

}
void Raster::flatBotTri(Vertex_R* p[3])
{
	float zDA=(p[2]->getHpos().getZ()-[p0]->getHpos().getZ())/(p[2]->getHpos().getY()-p[0]->getHpos().getY());
	float zDB=(p[2]->getHpos().getZ()-[p1]->getHpos().getZ())/(p[2]->getHpos().getY()-p[1]->getHpos().getY());
	Line line1(p[0]->getHpos()->getX,p[0]->getHpos()->getY,p[2]->getHpos()->getX,p[2]->getHpos()->getY),
		line2(p[1]->getHpos()->getX,p[1]->getHpos()->getY,p[2]->getHpos()->getX,p[2]->getHpos()->getY);
	rasterKern->draw(p[0]->getHpos()->getX(),p[1]->getHpos()->getX(),p[0]->getHpos()->getY(),p[2]->getHpos()->getY(),
		line1.dydx(),line2.dydx(),p[0]->getHpos()->getZ(),p[1]->getHpos()->getZ(),zDA,zDB);
}
*/
void Raster::setShader()
{
	rasterKern->configShader(rasterMod->material->getType(),rasterScene,rasterMod->material);
}