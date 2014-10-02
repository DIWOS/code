#ifndef MODEL_H
#define MODEL_H
#define GL_GLEXT_PROTOTYPES
#define FBXSDK_NEW_API
#define MAX_VERTICES 2000
#include "3dModelBasicStructs.h"
#include <fbxsdk.h>
#include <iostream>
#include <glew.h>
//_________GLUT_________//
#ifdef __APPLE__
#include <glut.h>
#else
#include <glut.h>
#endif
#include <gl\glaux.h>

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
	GLsizei numIndices;

	int numVertices;

};
#endif