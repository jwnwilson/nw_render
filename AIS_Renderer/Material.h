#pragma once
#include <vector>
#include "Vector3D.h"
#include "ColourRGB.h"
#include "Texture.h"
#include "Buffer.h"

#define BASICM 0
#define LAMBERTM 1
#define PHONGM 2
#define BLINNM 2

class Light;
class Camera;

// simple Material class

class Material
{
public:
	Material();
	Material(const ColourRGB&,const ColourRGB&);
	// colours = in order: ambient co-ef, diffuse co-ef,
	
	bool isTextured(){return textured;}
	void setTexture(Texture* t){texture=t;textured=true;}
	void setName(const string& s){name=s;}
	void setEmission(const ColourRGB& e){emission=e;}
	void setAmbientC(const ColourRGB& a){ambientCoef=a;}
	virtual void setDiffuse(const ColourRGB& d){;}
	virtual void setSpecular(const ColourRGB& a){;}
	virtual void setSpecularExp(const float& f){;}
	virtual void setConstant(const ColourRGB& d){;}

	virtual ColourRGB getConstant()const{return ColourRGB(0,0,0);}
	virtual ColourRGB getSpecularC()const{return ColourRGB(0,0,0);}
	virtual float getSpecularExp()const{return int(0);}
	virtual ColourRGB getDiffuseC()const{return ColourRGB(0,0,0);}
	Texture * getTexture()const{return texture;}
	
	
	//void setType(const char& c){type=c;}
	int getType(){return type;}
	string getName(){return name;}

	ColourRGB getEmission()const{return emission;}
	ColourRGB getAmbientC()const{return ambientCoef;}
	
	


	~Material(void);
	ColourRGB reflectivity, transparency;

	
protected:

	//used char to store what type of material an object is.
	int type;
	bool textured;

	string name;
	ColourRGB ambientCoef,emission;
	Texture *texture;

};

