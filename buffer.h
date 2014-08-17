#define GL_GLEXT_PROTOTYPES
#include <iostream>
#include "Model.h"
#include <glut.h>
#include "glext.h"

using namespace std;

class Buffers
{
public:
	//constructor
	Buffers(vertex*);
	float bufferInit(vertex*);
private:

	GLuint VertexVBOID;

};
