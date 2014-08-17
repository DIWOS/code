#include "buffer.h"


//constructor
Buffers::Buffers(vertex *vertices)
{

		bufferInit(vertices);

}

float Buffers::bufferInit(vertex *vertices)
{
	glGenBuffers(1, &VertexVBOID);
	glBindBuffer(GL_ARRAY_BUFFER, VertexVBOID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex)* 3, &vertices[0].x, GL_STATIC_DRAW);
}

