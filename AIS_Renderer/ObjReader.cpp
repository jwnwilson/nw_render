#include "ObjReader.h"
#include <fstream>
#include "MaterialPhong.h"
#include "ModelAdv.h"

ObjReader::ObjReader(void)
{
}

ObjReader::~ObjReader(void)
{
}

void ObjReader::clear()
{
	vertPos= NULL;
	vertUV= NULL;
	vertNorm= NULL;
}

vector<string> ObjReader::getWords(string line)
{
	vector<string> words;
	int wordcount=0,b=0;
	if(line.size() > 0)
	{
		int i = 0;
		while(i < line.size())
		{
			if(line[i] == ' ' )
			{
				words.push_back("");
				for(int a=b;a<i;a++)
				{
					words[wordcount].push_back(line[a]);
				}
				b = i+1;
				wordcount++;
			}
			if(i == (line.size()-1))
			{
				words.push_back("");
				for(int a=b;a<i+1;a++)
				{
					words[wordcount].push_back(line[a]);
				}
				b = i+1;
				wordcount++;
			}
			i++;
		}
	}
	return words;
}
bool ObjReader::storeVertex(vector<string> &data)
{
	Vector3D vec(atof(&data[1][0]),atof(&data[2][0]),atof(&data[3][0]));
	vertPos->push_back(vec);

	return true;
}
bool ObjReader::storeVertexUV(vector<string> &data)
{
	Vector2D vec(atof(&data[1][0]),atof(&data[2][0]));
	vertUV->push_back(vec);

	return true;
}

bool ObjReader::storeVertexNormal(vector<string> &data)
{
	Vector4D vec(atof(&data[1][0]),atof(&data[2][0]),atof(&data[3][0]),1);
	vertNorm->push_back(vec);

	return true;
}

vector<int> ObjReader::getInts(string &data)
{
	string number;
	vector<int> ints;
	for(int i =0;i<data.size();i++)
	{
		if(data[i] != '/')
		{
			number.push_back(data[i]);
		}
		else
		{
			ints.push_back(atoi(&number[0]));
			number.clear();
		}

	}
	ints.push_back(atoi(&number[0]));
	number.clear();
	return ints;
}
bool ObjReader::storeModel(vector<string> &data)
{
	/*for(int i =1;i<data.size();i++)
	{
		modPtr->getVertices()->push_back(Vertex_R());
		Vertex_R *vert = &(*modPtr->getVertices())[modPtr->vertices.size()-1];
		vector<int> indices = getInts(data[i]);

		vert->setWorld(vertpos[indices[0]-1]);
		vert->setUV(vertUVs[indices[1]-1]);
		vert->setNorm(vertNormals[indices[2]-1]);

		modPtr->index.push_back(modPtr->vertices.size()-1);
	}
	modPtr->index.push_back(-1);*/

	return true;
}
void ObjReader::invertPolygons()
{
	for(int i=0;i<faces->size();i++)
	{
		Face* face = (*faces)[i];
		for(int i=1; i< face->vertexPos.size()/2;i++)
		{
			swap( face->vertexPos[i], face->vertexPos[face->vertexPos.size()-i-1] );
			swap( face->vertexNorm[i], face->vertexNorm[face->vertexNorm.size()-i-1] );
			swap( face->vertexUV[i], face->vertexUV[face->vertexUV.size()-i-1] );
		}
	}
	/*int polystart=0, polyend;
	vector<int> newIndex

	for(int i=0;i<modPtr->index.size();i++)
	{
		if(modPtr->index[i] == -1)
		{
			polyend = i;
			newIndex.push_back(modPtr->index[polystart]);
			for(int a=1;a<(polyend-(polystart));a++)
			{
				newIndex.push_back(modPtr->index[polyend-a]);
			}
			newIndex.push_back(-1);
			polystart = polyend+1;
		}
	}
	modPtr->index.clear();
	modPtr->index = newIndex;*/
}

bool ObjReader::storeFace(vector<string> &data)
{
	Face *f = new Face;
	for(int i =1;i<data.size();i++)
	{
		vector<int> ind = getInts(data[i]);
		f->vertexPos.push_back(&(*vertPos)[ind[0]-1]);
		f->vertexNorm.push_back(&(*vertNorm)[ind[2]-1]);
		f->vertexUV.push_back(&(*vertUV)[ind[1]-1]);
		indices->push_back(ind[0]-1);
	}
	faces->push_back(f);
	indices->push_back(-1);
	return true;
}

bool ObjReader::readFile(char* name)
{
	fstream file;
	string line;
	vector<string> data;

	Model *mod = new ModelAdv();
	scPtr->models.push_back(mod);
	modPtr = mod;
	modPtr->implicit= false;

	vertPos = modPtr->getPositions();
	vertNorm = modPtr->getNormals();
	vertUV = modPtr->getUVs();
	faces = modPtr->getFaces();
	indices = modPtr->getIndex();

	Material *mat1= new MaterialPhong;
	mat1->setDiffuse(ColourRGB(0.5,0.5,0.5));
	mat1->setAmbientC(ColourRGB(0.2,0.2,0.2));
	mat1->setSpecular(ColourRGB(0.5,0.5,0.5));
	mat1->setSpecularExp(2);

	scPtr->materials.push_back(mat1);

	modPtr->material = mat1;

	file.open(name);

	while(! file.eof())
	{
		getline (file,line);
		data = getWords(line);
		if(data.size() >0)
		{
			if(data[0] == "v")
			{
				storeVertex(data);
			}
			if(data[0] == "vt")
			{
				storeVertexUV(data);
			}
			if(data[0] == "vn")
			{
				storeVertexNormal(data);
			}
			if(data[0] == "f")
			{
				storeFace(data);
			}
		}
	}
	if(invert == true)
	{
		invertPolygons();
	}
	clear();
	file.close();
	return true;
}

bool ObjReader::readFile2(char* name)
{
	fstream file;
	string line;
	vector<string> data;

	Model *mod = new ModelAdv();
	scPtr->models.push_back(mod);
	modPtr = mod;
	modPtr->implicit= false;

	Material *mat1= new MaterialPhong;
	mat1->setDiffuse(ColourRGB(0.5,0.5,0.5));
	mat1->setAmbientC(ColourRGB(0.2,0.2,0.2));
	mat1->setSpecular(ColourRGB(0.5,0.5,0.5));
	mat1->setSpecularExp(2);

	scPtr->materials.push_back(mat1);

	modPtr->material = mat1;

	file.open(name);

	while(! file.eof())
	{
		getline (file,line);
		data = getWords(line);
		if(data.size() >0)
		{
			if(data[0] == "v")
			{
				storeVertex(data);
			}
			if(data[0] == "vt")
			{
				storeVertexUV(data);
			}
			if(data[0] == "vn")
			{
				storeVertexNormal(data);
			}
			if(data[0] == "f")
			{
				storeModel(data);
			}
		}
	}
	//invertPolygons();
	clear();
	file.close();
	return true;
}