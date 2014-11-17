#include "TimeLine.h"
#include "ModelSys.h"

TimeLine::TimeLine(void)
{
}

TimeLine::~TimeLine(void)
{
}
void TimeLine::initalise(int l, int f)
{
	length = l;
	fps = f;
}
void TimeLine::addKeyFrame(int time, Scene* s)
{
	KeyFrame k;
	k.setKeyFrame(s);
	k.frame = time;
	keyFrames.push_back(k);
	timeLine.push_back( keyFrames.size()-1);
}
void TimeLine::setInbetweens()
{
	for(int i=0; i< (keyFrames.size()-1);i++)
	{
		float time =keyFrames[i+1].frame - keyFrames[i].frame;

		KeyFrame inb;
		for(int j=0; j< keyFrames[i].keyFrame.size();j++)
		{
			ModelParam modp;
			modp.position = (keyFrames[i+1].keyFrame[j].position - keyFrames[i].keyFrame[j].position) *(1/(time*fps)) ;
			modp.rotation = (keyFrames[i+1].keyFrame[j].rotation - keyFrames[i].keyFrame[j].rotation) * (1/(time*fps));
			modp.scale = (keyFrames[i+1].keyFrame[j].scale- keyFrames[i].keyFrame[j].scale)*(1/(time*fps));
			inb.keyFrame.push_back(modp);
			inb.frame = (time*fps)-1;
		}
		inbetweens.push_back(inb);
	}
}
void TimeLine::setScene(int frameNumber, Scene* s)
{
	ModelSys temp;
	int index;
	bool prev = false;
	for(int i=0; i< inbetweens.size();i++)
	{
		if(inbetweens[i].frame> frameNumber)
		{
			index = i;
		}
	}
	for(int i=0;i<s->models.size();i++)
	{
		//temp.rotate(s->models[i],inbetweens[index].keyFrame[i].rotation);
		//temp.scale(s->models[i],inbetweens[index].keyFrame[i].scale);
		//temp.translate(s->models[i],inbetweens[index].keyFrame[i].position);
	}
}