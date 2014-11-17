#include "Camera_Passive.h"
#include "ModelBase.h"

Camera_Passive::Camera_Passive(void)
{
	eyePos=Vector3D(0,0,0);
	screenBotLef=Vector3D(-1,-1,1);
	screenBotRig=Vector3D(1,-1,1);
	screenTopLef=Vector3D(-1,1,1);
	screenTopRig=Vector3D(1,1,1);
	Vx=screenBotRig-screenBotLef;
	Vy=screenTopLef-screenBotLef;
	width=1024;
	height=512;
}

Camera_Passive::~Camera_Passive(void)
{
}
void Camera_Passive::drawScene(Scene* sc1)
{
	for (int i =0; i< sc1->models.size(); i++)
	{
		drawWireFrame(sc1->models[i]);
	}	
}
void Camera_Passive::setScreen(const Vector3D& BL,const Vector3D& BR,const Vector3D& TR,const Vector3D& TL)
{
	screenBotLef=BL;
	screenBotRig=BR;
	screenTopLef=TL;
	screenTopRig=TR;
	screenCenter=screenBotLef+(screenTopRig*0.5);
}
void Camera_Passive::drawWireFrame(Model* mesh)
{
	int count=0;
	for(int i=0;i< mesh->getIndex()->size();i++)
	{
		if((*mesh->getIndex())[i]!=-1)
		{
			if((*mesh->getIndex())[i+1]!=-1)
			{
				count++;
				drawLine((*mesh->getVertices())[(*mesh->getIndex())[i]],(*mesh->getVertices())[(*mesh->getIndex())[i+1]]);
			}
			else
			{
				drawLine((*mesh->getVertices())[(*mesh->getIndex())[i]],(*mesh->getVertices())[(*mesh->getIndex())[i-count]]);
			}
		}

	}

}
void Camera_Passive::vertToEyeScreenPos(const Vertex_R& v)
{
	//finds world co-ord for Screen intersect positon
	double eyeToCenDist,centerToPosDist,eyeToPosDist,hypot,theta,opp,adj;
	Vector3D eyeToCent,eyeToPos,screenPos;
	eyeToCent=screenCenter-eyePos;
	eyeToPos=v.getWorld()-eyePos;
	eyeToCenDist=(screenCenter-eyePos).modulus();
	theta=acos(eyeToPos.dot(eyeToCent)/(eyeToPos.modulus()*eyeToCent.modulus()));
	hypot=eyeToCenDist/cos(theta);
	screenPos=eyeToPos*(hypot/eyeToPos.modulus());


	//finds pixel which represents the screen intersect position
	double botLToBotRDist,botLToTopLDist;
	Vector3D botLefToPos;

	botLToBotRDist=(Vx).modulus();
	botLToTopLDist=(Vy).modulus();	
	botLefToPos=screenPos-screenBotLef;
	theta=acos(botLefToPos.dot(Vx)/(botLefToPos.modulus()*Vx.modulus()));
	hypot=botLefToPos.modulus();
	opp=sin(theta)*hypot;
	adj=cos(theta)*hypot;
	x=(adj/botLToBotRDist)*width;
	y=(opp/botLToTopLDist)*height;

}

void Camera_Passive::drawLine(const Vertex_R& v0,const Vertex_R& v1)
{
	int xstart,ystart,xend,yend;
	vertToEyeScreenPos(v0);
	xstart=x;
	ystart=y;
	vertToEyeScreenPos(v1);
	xend=x;
	yend=y;

	ColourRGB col(1,1,1);
	float stepAx,gradAx,diffA(xend-xstart),diffB(yend-ystart),dydx,dxdy,stepInc,stepEnd;
	int yPosNeg(1),xPosNeg(1);
	if(diffB==0||diffA==0)
	{
		if(diffB>0)
		{
			dydx=1;
			dxdy=0;
		}
		else
		{
			dydx=0;
			dxdy=0;
		}
	}
	else
	{
		dydx=diffB/diffA;
		dxdy=diffA/diffB;
	}
	
	if(diffA>=0)
	{
		if(diffB<0)
		{
			yPosNeg=-1;			
		}	
	}
	else
	{
		xPosNeg=-1;
		if(diffB<0)
		{
			yPosNeg=-1;		
		}	
	}

	if((sqrt(dydx*dydx))<1)
	{	
		stepAx=xstart;
		gradAx=ystart;
		stepInc=xPosNeg;
		stepEnd=xend;

		while(stepAx!=stepEnd)
		{
			screen->getColour()->setPix(int(stepAx),int(gradAx),col);
			stepAx+=stepInc;
			gradAx+=dydx;

		}
	}
	else
	{
		stepAx=ystart;
		gradAx=xstart;
		stepInc=yPosNeg;
		stepEnd=yend;

		while(stepAx!=stepEnd)
		{
			screen->getColour()->setPix(int(gradAx),int(stepAx),col);
			stepAx+=stepInc;
			gradAx+=dxdy;

		}
	}

	
	
}