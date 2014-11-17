#include "Kernel.h"
#include "LambertShader.h"
#include "PhongShader.h"
#include "ConstantShader.h"

Kernel::Kernel(void)
{
	kColBuff=NULL;
	kDepBuff=NULL;
	kShader=NULL;
}

Kernel::~Kernel(void)
{
	if(kShader!=NULL)
	{
		delete kShader;
	}
}

void Kernel::initalise(Buffer<ColourRGB>* col,Buffer<float>* dep)
{
	kColBuff=col;
	kDepBuff=dep;
}

void Kernel::configShader(char a,Scene* b,Material* c)
{
	switch (a){
		case 'l':
			kShader=new LambertShader;
			break;
		case'p':
			kShader=new PhongShader;
			break;
		case'c':
			kShader=new ConstantShader;
			break;
		default:
			kShader=new LambertShader;
	}
	kShader->setScene(b);
	kShader->setMaterial(c);
}
bool Kernel::depthTest(int x,int y, float z)
{
	if(kDepBuff->getPix(x,y)>z)
	{
		kDepBuff->setPix(x,y,z);
		return true;
	}
	return false;
}

void Kernel::draw(KernParam& kParam)

{
	
}

void Kernel::drawLine(KernParam& kParam, ColourRGB& col)
{
	float stepAx,secAx;
	Vertex_R vert;

	if(kParam.diffA<0)
	{
		float posDA=0-kParam.diffA;
		if(posDA>kParam.diffB)
		{
			if(kParam.diffB==0)
			{
				kParam.diffA=0;
			}
			else
			{
				kParam.diffA= kParam.diffB/kParam.diffA;
			}
			secAx=kParam.ystart;
			stepAx=kParam.xstart;
			while(stepAx>kParam.xend)
			{
				//col=ColourRGB(1,1,1);//kShader->shade(&vert);
				kColBuff->setPix(int(stepAx),int(secAx),col);
				stepAx--;
				secAx-=kParam.diffA;

			}
		}
		else
		{
			if(kParam.diffA==0)
			{
				kParam.diffA=0;
			}
			else
			{
				kParam.diffA= kParam.diffA/kParam.diffB;
			}
			secAx=kParam.xstart;
			stepAx=kParam.ystart;
			while(stepAx<kParam.yend)
			{
				//col=ColourRGB(1,1,1);//kShader->shade(&vert);
				kColBuff->setPix(int(secAx),int(stepAx),col);
				stepAx++;
				secAx+=kParam.diffA;

			}
		}
	}
	else if(kParam.diffA>kParam.diffB)
	{
		if(kParam.diffB==0)
		{
			kParam.diffA=0;
		}
		else
		{
			kParam.diffA= kParam.diffB/kParam.diffA;
		}
		secAx=kParam.ystart;
		stepAx=kParam.xstart;
		while(stepAx<kParam.xend)
		{
			//col=ColourRGB(1,1,1);//kShader->shade(&vert);
			kColBuff->setPix(int(stepAx),int(secAx),col);
			stepAx++;
			secAx+=kParam.diffA;

		}
	}
	else
	{
		if(kParam.diffA==0)
		{
			kParam.diffA=0;
		}
		else
		{
			kParam.diffA= kParam.diffA/kParam.diffB;
		}
		secAx=kParam.xstart;
		stepAx=kParam.ystart;
		while(stepAx<kParam.yend)
		{
			//col=ColourRGB(1,1,1);//kShader->shade(&vert);
			kColBuff->setPix(int(secAx),int(stepAx),col);
			stepAx++;
			secAx+=kParam.diffA;

		}
	}
}


