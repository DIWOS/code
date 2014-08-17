#ifndef MODEL_H
#define MODEL_H
#define GL_GLEXT_PROTOTYPES
#define FBXSDK_NEW_API
#define MAX_VERTICES 2000
#include "3dModelBasicStructs.h"
#include <fbxsdk.h>
#include <iostream>
//_________GLUT_________//
#ifdef __APPLE__
#include <glut.h>
#else
#include <glut.h>
#endif
#include "glext.h"

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

	void Buffer()
	{
		GLuint id = 0;  
		GLenum target = GL_ARRAY_BUFFER_ARB;
		GLenum usage = GL_STATIC_DRAW_ARB;

		glGenBuffersARB(1, &id); 
		glBindBufferARB(target, id);
		glBufferDataARB(target, numIndices, indices, usage);

		glBufferDataARB(GL_ARRAY_BUFFER_ARB, sizeof(vertices)+sizeof(normals), 0, GL_DYNAMIC_DRAW_ARB);

		int bufferSize = 0;
		glGetBufferParameterivARB(target, GL_BUFFER_SIZE_ARB, &bufferSize);
		if (numIndices != bufferSize)
		{
			glDeleteBuffersARB(1, &id);
			id = 0;
			cout << "\n [createVBO()] Data size is mismatch with input array \n BS = " << bufferSize << "\n NI = " << numIndices;
		}
	}

private:
	GLuint vboId;                              // ID of VBO


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