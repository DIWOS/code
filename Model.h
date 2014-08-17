#ifndef MODEL_H
#define MODEL_H
#define FBXSDK_NEW_API
#define MAX_VERTICES 40000
#include "3dModelBasicStructs.h"
#include <fbxsdk.h>
#include <iostream>
#include "buffer.h"

using namespace std;

class Model
{

public:

	Model(char*);
	~Model();

	void ShowDetails();

	char* GetModelName();
	void  SetModelName(char*);
	void  GetFbxInfo(FbxNode*);
	void  RenderModel();
	void createVertex();

private:

	char Name[25];

	vertex vertices[MAX_VERTICES];
	texturecoords txt[MAX_VERTICES];

	float *normals;
	int numNormals;

	GLsizei *indices;
	int numIndices;

	int numVertices;

};
#endif