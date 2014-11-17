#pragma once
#include "filereader.h"
#include "Face.h"

// reads .obj model files and stores the model into the render scene.

class ObjReader :
	public FileReader
{
public:
	ObjReader(void);
	bool readFile(char* name);
	// debugging function no longer required.
	bool readFile2(char* name);
	string getWord(string line);
	~ObjReader(void);

private:
	vector<string> getWords(string line);
	vector<int> getInts(string &data);
	void invertPolygons();
	void clear();
	bool storeVertex(vector<string> &data);
	bool storeVertexUV(vector<string> &data);
	bool storeVertexNormal(vector<string> &data);
	bool storeFace(vector<string> &data);
	bool storeModel(vector<string> &data);

	vector<Vector3D> *vertPos;
	vector<Vector4D> *vertNorm;
	vector<Vector2D> *vertUV;
	vector<Face*> *faces;
	vector<int> *indices;
};
