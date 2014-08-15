#pragma once

#define GLEW_STATIC
#include <glew.h>

class Geometry;

template<GLenum target>
class GLBuffer {
    friend class Geometry;
public:
    void Buffer(void* data, const int& size, const unsigned int& usage){
        if(_handle == 0) glGenBuffers(1, &_handle);
        glBindBuffer(target, _handle);
        glBufferData(target, size, data, usage);
        glBindBuffer(target, 0);
    }

    void SetInfo(const unsigned int & drawingMode, const unsigned int & type, const unsigned int & elementsNum){
        _drawingMode = drawingMode;
        _type = type;
        _elementsNum = elementsNum;
    }

    void Release(){
        if(_handle != 0){
            glDeleteBuffers(1, &_handle);
            _handle = 0;
        }
    }

    void Bind(){
        if(_binded_handle != _handle) {
            glBindBuffer(target, _binded_handle);
            _binded_handle = _handle;
        }
    }

    GLBuffer() : _handle(0), _elementsNum(0) {}
    ~GLBuffer(){ Release(); }
private:
    unsigned int _handle;
    unsigned int _elementsNum;
    unsigned int _drawingMode;
    unsigned int _type;

    static unsigned int _binded_handle;
};

template<GLenum target>
unsigned int GLBuffer<target> ::_binded_handle = 0;

typedef GLBuffer<GL_ARRAY_BUFFER> VertexBuffer;
typedef GLBuffer<GL_ELEMENT_ARRAY_BUFFER> IndexBuffer;

class Geometry {
public:
    void BeginDraw();
    void Draw();
    void EndDraw();

    Geometry(VertexBuffer* vb, IndexBuffer* ib, const bool& freeMemory = true);
    ~Geometry();
private:
    VertexBuffer* _vb;
    IndexBuffer* _ib;
    bool _freeMem;
    unsigned int _vao;

    static unsigned int _binded_vao;
};
