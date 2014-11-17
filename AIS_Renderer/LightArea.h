#pragma once
#include "light.h"
#include <vector>

// Area Light to allow soft shadows

class LightArea :
	public Light
{
public:
	LightArea(void);
	~LightArea(void);
	void setSegments(int s);
	void setWidthHeight(int w,int h){width = w;height = h;}
	void setInterest(const Vector3D&);
	void setPosition(const Vector3D&);
	void setAtten(const Vector3D& v){attenuation = v.x;}

	Vector3D getAttenCo()const{return Vector3D(attenuation,0,0);}
	int getSegments()const{return segments;}
	vector<Vector3D>* getSegmentPos(){return &segmentPos;}
	float getWidth()const{return width;}
	float getHeight()const{return height;}
	Vector3D* getDirectionX(){return &Xdirect;}
	Vector3D* getDirectionY(){return &Ydirect;}
	Vector3D* getPoint(int i){return &points[i];}
	
private:
	int segments;
	float width,height,attenuation;
	Vector3D direction, points[4],Xdirect,Ydirect;
	vector<Vector3D> segmentPos;
};
