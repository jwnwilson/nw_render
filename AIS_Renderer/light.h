#pragma once
#include "Vertex_R.h"
#include "Vector3D.h"
#include "ColourRGB.h"
#include <vector>

#define BASICLIGHT 0
#define SPOTLIGHT 1
#define POINTLIGHT 2
#define AREALIGHT 3

// Simple light class

class Light
{
public:
	Light();
	Light(const ColourRGB&,const Vector3D&);

	bool isSpot()const;
	bool isPoint()const;
	bool isArea() const;
	int getType(){return type;}

	virtual void setPosition(const Vector3D&);
	virtual void setColour(const ColourRGB&);

	virtual void setAtten(const Vector3D&){;}
	virtual void setAttenExp(int){;}
	virtual	void setAngle(float){;}
	virtual void setInterest(const Vector3D&){;}
	
	virtual void setSegments(int s){;}
	virtual void setWidthHeight(int w,int h){;}

	virtual Vector3D getInterest()const{return Vector3D(1,0,0);}
	virtual float getAngle()const{return float(1);}	
	virtual int getAttenExp()const{return 1;}
	virtual Vector3D getVector()const {return Vector3D(1,0,0);}
	virtual Vector3D getAttenCo()const{return Vector3D(1,0,0);}

	virtual int getSegments()const{return 0;}
	virtual vector<Vector3D>* getSegmentPos(){return NULL;}
	virtual float getWidth()const{return 0;}
	virtual float getHeight()const{return 0;}
	virtual Vector3D* getDirectionX(){return NULL;}
	virtual Vector3D* getDirectionY(){return NULL;}
	virtual Vector3D* getPoint(int i){return NULL;}

	ColourRGB getColour()const{return lightRGB;}
	Vector3D getPosition()const{return pos;}

	~Light(void);
protected:
	int type;
	ColourRGB lightRGB;
	Vector3D pos;

};
