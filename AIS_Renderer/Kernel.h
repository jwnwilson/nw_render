#pragma once
#include "Buffer.h"
#include "ColourRGB.h"
#include "Vertex_R.h"
#include "Shader.h"
#include "KernParam.h"

class Scene;
class Material;
class Kernel
{
public:
	Kernel(void);
	void initalise(Buffer<ColourRGB>* col,Buffer<float>* dep);
	void configShader(char,Scene*,Material*);
	virtual void draw(KernParam&);
	virtual void drawLine(KernParam&,ColourRGB&);
	bool depthTest(int x,int y, float z);
	Shader *kShader;
	~Kernel(void);
protected:
	Buffer<ColourRGB> *kColBuff;
	Buffer<float> *kDepBuff;

};
