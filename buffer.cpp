#include "buffer.h"

#include <fbxsdk.h>
#include <iostream>
#include <glut.h>

using namespace std;

//________GLEW_________//
#ifdef	_WIN32
#include	<wglew.h>
#else
#include	<glxew.h>
#endif


class VertexBufferClass
{
public:
	//constructor
	VertexBufferClass(char*);

	void initBuffer();

	//~vertex_buffer();


private:
};



