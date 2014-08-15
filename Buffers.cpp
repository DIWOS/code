#include "Buffers.hpp"

void Geometry::BeginDraw(){
    if(_binded_vao != _vao) {
        glBindVertexArray(_vao);
        _binded_vao = _vao;
    }
}

void Geometry::Draw(){
    if(_ib == nullptr) {
        glDrawArrays(_vb->_drawingMode, 0, _vb->_elementsNum);
    }
    else {
        _ib->Bind();
        glDrawElements(_ib->_drawingMode, _ib->_elementsNum, _ib->_type, 0);
    }
}

void Geometry::EndDraw(){
    glBindVertexArray(0);
    _binded_vao = 0;
}

Geometry::Geometry(VertexBuffer* vb, IndexBuffer* ib, const bool& freeMemory)
    : _vb(vb), _ib(ib), _freeMem(freeMemory) {

    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);
    glBindBuffer(GL_ARRAY_BUFFER, vb->_handle);

    glVertexAttribPointer(0, 3, _vb->_type, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

Geometry::~Geometry(){
    if(_freeMem){
        delete _vb;
        delete _ib;
    }
}

unsigned int Geometry::_binded_vao = 0;
