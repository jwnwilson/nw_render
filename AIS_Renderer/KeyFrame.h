#pragma once
#include "Scene.h"
#include <vector>

class KeyFrame
{
public:
	KeyFrame(void);
	~KeyFrame(void);
	void setKeyFrame(Scene* s);
	vector<ModelParam> keyFrame;
	int frame;
};
