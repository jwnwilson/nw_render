#pragma once
#include "Scene.h"

// File reader is used to be derived into other file reading classes, so different files can be read
// and renderer can be expanded easily.

class FileReader
{
public:
	FileReader(void);
	void setScene(Scene *s){scPtr =s;}
	virtual bool readFile(char*){return false;}
	~FileReader(void);

	Scene *scPtr;
	Model *modPtr;
	int currentVert;
	bool invert;
};
