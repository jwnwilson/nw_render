#include "JWRT.h"
#include "ObjReader.h"
#include "OutputWin.h"
#include "MaterialPhong.h"
#include "ModelAdv.h"
#include "ModelSys.h"
#include "LightArea.h"
#include "LightSpot.h"
#include "ImplicitSphere.h"

JWRT::JWRT(void)
{
	camera=NULL;
	output=NULL;
	error = false;
	argCount = 0;
	argValues = NULL;
}

JWRT::JWRT(int argc, char **argV)
{
	camera=NULL;
	output=NULL;
	error = false;
	argCount = argc;
	argValues = argV;
}

JWRT::~JWRT(void)
{
	if(camera!=NULL)
	{
		delete camera;
	}
	if(output!=NULL)
	{
		delete output;
	}
}
void JWRT::initalise(int i)
{
	setScene(i);
}

void JWRT::configure(Configure& c)
{
	config =c;
	image.initialise(config.w,config.h);
	if(c.camera=='p')
	{
		camera=new Camera_Passive();
	}
	else
	{
		camera=new Camera_Active();
	}
	camera->setBounces(c.bounces);
	if(c.output == 't')
	{
		output = new OutputTGA();
	}
	else
	{
		output = new OutputWin(argCount, argValues);
	}
}
void JWRT::render()
{
	if(error == false)
	{
		if(timeLine.keyFrames.size()==0)
		{
			camera->initialise(&image);
			camera->setScene(&mainScene);
			//camera->setOutput(output);
			//camera->drawScene();
			output->setCamera(camera);
			output->readBuff(image.getColour());
			output->outputImage("render");
			cout<< "Image output as 'render.tga' in project directory\n";
			cout<< "Enter any Key to exit\n";
			char exit;
			cin>>exit;
		}
		else
		{
			for(int i=0;i<(timeLine.length*timeLine.fps);i++)
			{
				cout<< "rendering frame "<< i<< " out of " << timeLine.fps<< endl;
				timeLine.setScene(i,&mainScene);
				camera->initialise(&image);
				camera->setScene(&mainScene);
				camera->drawScene(0);
				output->readBuff(image.getColour());
				output->outputImage("render"+ i);
			}
		}
	}
}
void JWRT::setScene(int i)
{
	Light *light1;
	Material *mat1,*mat2;
	Texture* text, *text2;
	Model *mesh,*mesh1,*mesh2;
	ModelSys modelSys;
	ObjReader reader;
	Scene key1,key2;

	camera->setEye(Vector3D(0,0,-3));
	camera->setScreen(Vector3D(-2,-1,-2),Vector3D(2,-1,-2),Vector3D(2,1,-2),Vector3D(-2,1,-2));

	switch(i){
		case 1:
			mat1= new MaterialPhong,mat2= new MaterialPhong;
			mat1->setDiffuse(ColourRGB(0.5,0.5,0.5));
			mat1->setAmbientC(ColourRGB(0.2,0.2,0.2));
			mat1->setSpecular(ColourRGB(0.5,0.5,0.5));
			mat1->setSpecularExp(2);
			mat2->setDiffuse(ColourRGB(0.5,0.5,0.5));
			mat2->setAmbientC(ColourRGB(0.2,0.2,0.2));
			mat2->setSpecular(ColourRGB(0.5,0.5,0.5));
			mat2->setSpecularExp(2);
			mat2->reflectivity = ColourRGB(1,1,1);

			text = new Texture;
			text->readTexture("bricks.tga");
			
			mat1->setTexture(text);

			mesh = new ModelAdv;
			mesh1 = new ModelAdv;
			mesh2 = new ModelAdv;

			modelSys.createSphere(1,Vector3D(-1.5,0,0),mesh);
			mesh->material=mat2;
			mesh->implicit=true;

			modelSys.createSphere(1,Vector3D(1.5,0,0),mesh1);
			mesh1->material=mat2;
			mesh1->implicit=true;
			
			modelSys.createPlane(10,10,Vector3D(0,0,2),mesh2);
			modelSys.rotate(mesh2,Vector3D(90,0,0));
			modelSys.translate(mesh2,Vector3D(0,0,10));	
			mesh2->material=mat1;

			light1= new LightSpot;
			light1->setAngle(180);
			light1->setColour(ColourRGB(1,1,1));
			light1->setPosition(Vector3D(0,3,0));
			light1->setInterest(Vector3D(0,0,0));
			light1->setAtten(Vector3D(1,0,0));

			mainScene.models.push_back(mesh);
			mainScene.models.push_back(mesh1);
			mainScene.models.push_back(mesh2);
			mainScene.lights.push_back(light1);
			mainScene.materials.push_back(mat1);
			mainScene.materials.push_back(mat2);
			mainScene.textures.push_back(text);
			break;
		case 2:
			mat1= new MaterialPhong,mat2= new MaterialPhong;
			mat1->setDiffuse(ColourRGB(0.5,0.5,0.5));
			mat1->setAmbientC(ColourRGB(0.2,0.2,0.2));
			mat1->setSpecular(ColourRGB(0.5,0.5,0.5));
			mat1->setSpecularExp(2);
			mat2->setDiffuse(ColourRGB(0.5,0.5,0.5));
			mat2->setAmbientC(ColourRGB(0.2,0.2,0.2));
			mat2->setSpecular(ColourRGB(0.5,0.5,0.5));
			mat2->setSpecularExp(2);
			mat2->transparency = ColourRGB(0.9,0.9,0.9);

			text = new Texture;
			text->readTexture("bricks.tga");
			
			mat1->setTexture(text);


			mesh = new ModelAdv;
			mesh1 = new ModelAdv;
			mesh2 = new ModelAdv;

			modelSys.createSphere(1,Vector3D(-1.5,-0.5,0),mesh);
			mesh->material=mat2;
			mesh->refractionIndex = 1.05;
			mesh->implicit=true;

			modelSys.createSphere(1,Vector3D(1.5,-0.5,0),mesh1);
			mesh1->material=mat2;
			mesh1->refractionIndex = 1.05;
			mesh1->implicit=true;
			
			modelSys.createPlane(10,10,Vector3D(0,0,2),mesh2);
			modelSys.rotate(mesh2,Vector3D(90,0,0));
			modelSys.translate(mesh2,Vector3D(0,0,10));	
			mesh2->material=mat1;

			light1= new LightSpot;
			light1->setAngle(180);
			light1->setColour(ColourRGB(1,1,1));
			light1->setPosition(Vector3D(0,3,0));
			light1->setInterest(Vector3D(0,0,0));
			light1->setAtten(Vector3D(1,0,0));

			mainScene.models.push_back(mesh);
			mainScene.models.push_back(mesh1);
			mainScene.models.push_back(mesh2);
			mainScene.lights.push_back(light1);
			mainScene.materials.push_back(mat1);
			mainScene.materials.push_back(mat2);
			mainScene.textures.push_back(text);
			break;
		case 3:
			mat1= new MaterialPhong,mat2= new MaterialPhong;
			mat1->setDiffuse(ColourRGB(0.5,0.5,0.5));
			mat1->setAmbientC(ColourRGB(0.2,0.2,0.2));
			mat1->setSpecular(ColourRGB(0.5,0.5,0.5));
			mat1->setSpecularExp(2);
			mat2->setDiffuse(ColourRGB(0.5,0.5,0.5));
			mat2->setAmbientC(ColourRGB(0.2,0.2,0.2));
			mat2->setSpecular(ColourRGB(0.5,0.5,0.5));
			mat2->setSpecularExp(2);

			text = new Texture;
			text->readTexture("bricks.tga");
			text2 = new Texture;
			text2->readTexture("plastic 1.tga");
			
			mat1->setTexture(text2);		
			mat2->setTexture(text);


			mesh = new ModelAdv;
			mesh1 = new ModelAdv;
			mesh2 = new ModelAdv;

			modelSys.createSphere(1,Vector3D(-1.5,-0.5,1),mesh);
			mesh->material=mat2;
			mesh->implicit=true;

			modelSys.createCube(2,Vector3D(0,0,0),mesh1);
			modelSys.rotate(mesh1,Vector3D(45,0,0));
			modelSys.rotate(mesh1,Vector3D(0,45,0));
			modelSys.translate(mesh1,Vector3D(2,0,1));
			mesh1->material=mat2;
			
			modelSys.createPlane(10,10,Vector3D(0,0,2),mesh2);
			modelSys.rotate(mesh2,Vector3D(90,0,0));
			modelSys.translate(mesh2,Vector3D(0,0,10));	
			mesh2->material=mat1;

			light1 = new LightArea;
			light1->setColour(ColourRGB(1,1,1));
			light1->setSegments(16);
			light1->setWidthHeight(1,1);
			light1->setPosition(Vector3D(0,4,0));
			light1->setInterest(Vector3D(0,0,0));

			mainScene.models.push_back(mesh);
			mainScene.models.push_back(mesh1);
			mainScene.models.push_back(mesh2);
			mainScene.lights.push_back(light1);
			mainScene.materials.push_back(mat1);
			mainScene.materials.push_back(mat2);
			mainScene.textures.push_back(text);
			mainScene.textures.push_back(text2);
			break;
		case 4:
			mat1= new MaterialPhong,mat2= new MaterialPhong;
			mat1->setDiffuse(ColourRGB(0.5,0.5,0.5));
			mat1->setAmbientC(ColourRGB(0.2,0.2,0.2));
			mat1->setSpecular(ColourRGB(0.5,0.5,0.5));
			mat1->setSpecularExp(2);

			text = new Texture;
			text->readTexture("bricks.tga");
			text2 = new Texture;
			text2->readTexture("plastic 1.tga");
			
			mat1->setTexture(text2);		
			mat2->setTexture(text);

			mesh2 = new ModelAdv;

			modelSys.createPlane(10,10,Vector3D(0,0,2),mesh2);
			modelSys.rotate(mesh2,Vector3D(90,0,0));
			modelSys.translate(mesh2,Vector3D(0,0,10));	
			mesh2->material=mat1;

			light1= new LightSpot;
			light1->setAngle(180);
			light1->setColour(ColourRGB(1,1,1));
			light1->setPosition(Vector3D(0,3,-1));
			light1->setInterest(Vector3D(0,0,0));
			light1->setAtten(Vector3D(1,0,0));

			reader.scPtr = &mainScene;
			reader.readFile("cube.obj");
			mainScene.models[0]->material = mat2;
			mainScene.models[0]->boundingShape = new ImplicitSphere();
			mainScene.models[0]->parameters.radius = 2;
			mainScene.models[0]->parameters.position = Vector3D(0,0,0);
			mainScene.models[0]->boundingShape->setPoints(mainScene.models[0]);
			mainScene.models.push_back(mesh2);
			mainScene.lights.push_back(light1);
			mainScene.materials.push_back(mat1);
			mainScene.materials.push_back(mat2);
			mainScene.textures.push_back(text);
			mainScene.textures.push_back(text2);
			break;
		case 5:
			mat1= new MaterialPhong,mat2= new MaterialPhong;
			mat1->setDiffuse(ColourRGB(0.5,0.5,0.5));
			mat1->setAmbientC(ColourRGB(0.2,0.2,0.2));
			mat1->setSpecular(ColourRGB(0.5,0.5,0.5));
			mat1->setSpecularExp(2);

			text = new Texture;
			text->readTexture("bricks.tga");
			text2 = new Texture;
			text2->readTexture("plastic 1.tga");
			
			mat1->setTexture(text2);		
			mat2->setTexture(text);

			mesh2 = new ModelAdv;


			
			modelSys.createPlane(10,10,Vector3D(0,0,2),mesh2);
			modelSys.rotate(mesh2,Vector3D(90,0,0));
			modelSys.translate(mesh2,Vector3D(0,0,10));	
			mesh2->material=mat1;

			light1= new LightSpot;
			light1->setAngle(180);
			light1->setColour(ColourRGB(1,1,1));
			light1->setPosition(Vector3D(0,3,0));
			light1->setInterest(Vector3D(0,0,0));
			light1->setAtten(Vector3D(1,0,0));

			reader.scPtr = &mainScene;
			reader.readFile("cube.obj");
			modelSys.LoopSubD(mainScene.models[0],1);
			mainScene.models[0]->material = mat2;
			mainScene.models.push_back(mesh2);
			mainScene.lights.push_back(light1);
			mainScene.materials.push_back(mat1);
			mainScene.materials.push_back(mat2);
			mainScene.textures.push_back(text);
			mainScene.textures.push_back(text2);
			break;
		case 6:
			cout<< "not fully implemented\n";
			mat1= new MaterialPhong,mat2= new MaterialPhong;
			mat1->setDiffuse(ColourRGB(0.5,0.5,0.5));
			mat1->setAmbientC(ColourRGB(0.2,0.2,0.2));
			mat1->setSpecular(ColourRGB(0.5,0.5,0.5));
			mat1->setSpecularExp(2);
			mat2->setDiffuse(ColourRGB(0.5,0.5,0.5));
			mat2->setAmbientC(ColourRGB(0.2,0.2,0.2));
			mat2->setSpecular(ColourRGB(0.5,0.5,0.5));
			mat2->setSpecularExp(2);
			//mat2->transparency = ColourRGB(0.9,0.9,0.9);

			text = new Texture;
			text->readTexture("bricks.tga");
			
			mat1->setTexture(text);


			mesh = new ModelAdv;
			mesh1 = new ModelAdv;
			mesh2 = new ModelAdv;

			modelSys.createCube(2,Vector3D(0,0,0),mesh1);
			modelSys.rotate(mesh1,Vector3D(45,0,0));
			modelSys.rotate(mesh1,Vector3D(0,45,0));
			modelSys.translate(mesh1,Vector3D(2,-1,0));
			mesh1->material=mat2;

			key1.models.push_back(mesh);

			mesh->parameters.position = mesh->parameters.position + Vector3D(3,1,0);


			key2.models.push_back(mesh);

			timeLine.initalise(5,12);
			timeLine.addKeyFrame(0,&key1);
			timeLine.addKeyFrame(5,&key2);
			timeLine.setInbetweens();
			
			modelSys.createPlane(10,10,Vector3D(0,0,2),mesh2);
			modelSys.rotate(mesh2,Vector3D(90,0,0));
			modelSys.translate(mesh2,Vector3D(0,0,10));	
			mesh2->material=mat1;

			light1= new LightSpot;
			light1->setAngle(180);
			light1->setColour(ColourRGB(1,1,1));
			light1->setPosition(Vector3D(0,3,0));
			light1->setInterest(Vector3D(0,0,0));
			light1->setAtten(Vector3D(1,0,0));

			mainScene.models.push_back(mesh);
			mainScene.models.push_back(mesh1);
			mainScene.models.push_back(mesh2);
			mainScene.lights.push_back(light1);
			mainScene.materials.push_back(mat1);
			mainScene.materials.push_back(mat2);
			mainScene.textures.push_back(text);
			break;
		default:
			cout<< "Selection not handled, cancelling render.\n";
			error = true;
			break;

	}
}