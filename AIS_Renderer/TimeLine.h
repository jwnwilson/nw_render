#pragma once
#include <vector>
#include "KeyFrame.h"

class TimeLine
{
public:
	TimeLine(void);
	~TimeLine(void);
	void initalise(int length, int fps);
	void addKeyFrame(int time, Scene* s);
	void setInbetweens();
	void setScene(int frameNumber, Scene* s);

	int length;
	int fps;
	vector<int> timeLine;
	vector<KeyFrame> keyFrames;
	vector<KeyFrame> inbetweens;

};
