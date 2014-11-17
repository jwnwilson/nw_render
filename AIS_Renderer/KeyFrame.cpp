#include "KeyFrame.h"

KeyFrame::KeyFrame(void)
{
}

KeyFrame::~KeyFrame(void)
{
}
void KeyFrame::setKeyFrame(Scene* s)
{
	for(int i=0;i< s->models.size();i++)
	{
		keyFrame.push_back( s->models[i]->parameters);
	}
}