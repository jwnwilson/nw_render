#include "VeiwSys.h"
#include "FrameBuffer.h"
#include "OutputWin.h"
#include "Camera_Passive.h"
#include "Camera_Active.h"
#include "Scene.h"
#include "implicitPlane.h"
#include "ImplicitSphere.h"
#include "LightPoint.h"
#include "LightArea.h"
#include "LightSpot.h"
#include "MaterialPhong.h"
#include "ModelSys.h"
#include "ModelAdv.h"
#include "ObjReader.h"
#include "JWRT.h"
#include <iostream>

using namespace std;

int main()
{
	int w,h;
	
	cout<<"Please select a width and height for image:\n";
	cout<<"Width:\n";
	cin>> w;
	cout<<"Height:\n";
	cin>> h;
	cout<<"Please select a scene to render:\n";
	cout<<"1. Reflection \n";
	cout<<"2. Refraction \n";
	cout<<"3. softShadows \n";
	cout<<"4. customObjects \n";
	cout<<"5. subDivided cube \n";
	cout<<"6. animation \n";
	int choice;
	cin>> choice;

	if(w > 5000)
	{
		w = 5000;
	}
	if(w <=0)
	{
		w = 1024;
	}
	if(h > 5000)
	{
		h = 5000;
	}
	if(h <=0)
	{
		h = 512;
	}


	Configure c;
	c.w=w;
	c.h=h;
	c.bounces=1;
	c.camera='a';
	c.output='w';

	JWRT render;
	render.configure(c);
	render.initalise(choice);
	render.render();

	//
	//FrameBuffer* image= new FrameBuffer;
	//OutputWin output;
	//image->initialise(1024,512);
	//Model mesh;
	//Vertex_R v1,v2,v3,v4;
	//v1.setWorld(Vector3D(-1,-1,2));
	//v2.setWorld(Vector3D(1,-1,2));
	//v3.setWorld(Vector3D(1,1,2));
	//v4.setWorld(Vector3D(-1,1,2));
	//mesh.vertices.push_back(v1);
	//mesh.vertices.push_back(v2);
	//mesh.vertices.push_back(v3);
	//mesh.vertices.push_back(v4);
	//mesh.index.push_back(0);
	//mesh.index.push_back(1);
	//mesh.index.push_back(2);
	//mesh.index.push_back(3);
	//mesh.index.push_back(-1);

	//Camera_Passive camera;
	//camera.initialise(image);
	//camera.drawWireFrame(mesh);
	//output.readBuff(image->getColour());
	//output.outputImage("test");*/
	//
	//FrameBuffer* image= new FrameBuffer;
	//OutputWin output;
	//Material *mat1= new MaterialPhong,*mat2= new MaterialPhong;
	//mat1->setDiffuse(ColourRGB(0.5,0.5,0.5));
	//mat1->setAmbientC(ColourRGB(0.2,0.2,0.2));
	//mat1->setSpecular(ColourRGB(0.5,0.5,0.5));
	//mat1->setSpecularExp(2);
	//mat2->setDiffuse(ColourRGB(0.5,0.5,0.5));
	//mat2->setAmbientC(ColourRGB(0.2,0.2,0.2));
	//mat2->setSpecular(ColourRGB(0.5,0.5,0.5));
	//mat2->setSpecularExp(2);
	//Scene scene1;
	//scene1.materials.push_back(mat1);
	//scene1.materials.push_back(mat2);

	//Texture* text = new Texture;
	//text->readTexture("bricks.tga");
	//scene1.textures.push_back(text);
	//mat1->setTexture(text);

	//Texture* text2 = new Texture;
	//text2->readTexture("plastic 1.tga");
	//scene1.textures.push_back(text2);
	//mat2->setTexture(text2);

	//Model *mesh = new ModelAdv;
	//Model *mesh2 = new ModelAdv;
	//ModelSys modelSys;
	////modelSys.createPlane(2,1,Vector3D(0,0,2),mesh);
	//
	//modelSys.createCube(2,Vector3D(0,0,0),mesh);
	////modelSys.rotate(mesh,Vector3D(45,0,0));
	////modelSys.rotate(mesh,Vector3D(0,45,0));
	////modelSys.translate(mesh,Vector3D(0,1,5));
	//mesh->material=mat1;
	////mesh.implicit=true;

	////modelSys.createSphere(1,Vector3D(1,0,0),mesh);
	//////modelSys.rotate(&mesh,Vector3D(45,0,0));
	//////modelSys.rotate(&mesh,Vector3D(0,45,0));
	//////modelSys.translate(&mesh,Vector3D(0,0,5));
	//////mesh.refractionIndex = 1.01;
	////mesh->material=mat1;
	////mesh->implicit=true;
	//
	//modelSys.createPlane(20,20,Vector3D(0,0,2),mesh2);
	//modelSys.rotate(mesh2,Vector3D(90,0,0));
	//modelSys.translate(mesh2,Vector3D(0,-2,10));	
	//mesh2->material=mat2;
	//mesh2->implicit=true;
	////modelSys.rotate(mesh,Vector3D(0,0,10));

	//*Light *light1= new LightSpot;
	//light1->setAngle(180);
	//light1->setColour(ColourRGB(1,1,1));
	//light1->setPosition(Vector3D(0,3,1));
	//light1->setInterest(Vector3D(0,0,0));
	//light1->setAtten(Vector3D(1,0,0));*/

	////Light* light1 = new LightArea;
	////light1->setColour(ColourRGB(1,1,1));
	////light1->setSegments(16);
	////light1->setWidthHeight(1,1);
	////light1->setPosition(Vector3D(0,1,1));
	////light1->setInterest(Vector3D(0,0,0));

	//Light *light1= new LightPoint;
	//light1->setColour(ColourRGB(1,1,1));
	//light1->setPosition(Vector3D(0,5,-3));
	//light1->setAtten(Vector3D(1,0,0));

	//*ObjReader reader;
	//reader.scPtr = &scene1;
	//reader.readFile("ship.obj");*/
	////scene1.models[0]->material = mat1;
	////modelSys.LoopSubD(scene1.models[0],1);
	////scene1.models[0]->boundingShape = new ImplicitSphere();
	////scene1.models[0]->parameters.radius= 1;
	////scene1.models[0]->parameters.position = Vector3D(0,0,0);
	//scene1.models.push_back(mesh);
	//scene1.models.push_back(mesh2);
	//scene1.lights.push_back(light1);
	//Camera_Active cam1;	
	//image->initialise(1024,512);
	//*
	//Vertex_R v1,v2,v3,v4;

	//v1.setWorld(Vector3D(-2,-1,2));
	//v2.setWorld(Vector3D(2,-1,2));
	//v3.setWorld(Vector3D(2,1,2));
	//v4.setWorld(Vector3D(-2,1,2));

	//mesh->vertices.push_back(v1);
	//mesh->vertices.push_back(v2);
	//mesh->vertices.push_back(v3);
	//mesh->vertices.push_back(v4);

	//mesh->index.push_back(0);
	//mesh->index.push_back(1);
	//mesh->index.push_back(2);
	//mesh->index.push_back(3);
	//mesh->index.push_back(-1);
	//mesh->material=mat1;

	//mesh->boundingShape=new ImplicitPlane;
	//mesh->boundingShape->setPoints(&mesh->vertices);*/

	//
	//cam1.setEye(Vector3D(0,0,-3));
	//cam1.setScreen(Vector3D(-2,-1,-2),Vector3D(2,-1,-2),Vector3D(2,1,-2),Vector3D(-2,1,-2));
	////cam1.translate(Vector3D(0,0,-1));
	////cam1.setTarget(Vector3D(0,0,0));


	//cam1.initialise(image);
	//cam1.RayBounces(0);
	//cam1.drawScene(&scene1);
	//output.readBuff(image->getColour());
	//output.outputImage("test");
	////delete image;
	


	return 0;
}