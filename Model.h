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
#include <glaux.h>


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
		//VERTEX 0
		pvertex[0].x = 0.0;
		pvertex[0].y = 0.0;
		pvertex[0].z = 0.0;

		//VERTEX 1
		pvertex[1].x = 1.0;
		pvertex[1].y = 0.0;
		pvertex[1].z = 0.0;

		//VERTEX 2
		pvertex[2].x = 0.0;
		pvertex[2].y = 1.0;
		pvertex[2].z = 0.0;

		glGenBuffers(1, &VertexVBOID);
		glBindBuffer(GL_ARRAY_BUFFER, VertexVBOID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex)* 3, &vertices[0].x, GL_STATIC_DRAW);

		unsigned short pindices[3];
		pindices[0] = 0;
		pindices[1] = 1;
		pindices[2] = 2;

		glGenBuffers(1, &IndexVBOID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexVBOID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short)* 3, pindices, GL_STATIC_DRAW);

		//Define this somewhere in your header file
		#define BUFFER_OFFSET(i) ((char *)NULL + (i))

			glBindBuffer(GL_ARRAY_BUFFER, VertexVBOID);
		glEnableVertexAttribArray(0);    
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), BUFFER_OFFSET(0));
		glEnableVertexAttribArray(1);   
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), BUFFER_OFFSET(3));
		glEnableVertexAttribArray(2);   
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), BUFFER_OFFSET(6));

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexVBOID);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, BUFFER_OFFSET(0));


	}

private:
	GLuint IndexVBOID;
	GLuint VertexVBOID;                              // ID of VBO

	vertex pvertex[3];

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