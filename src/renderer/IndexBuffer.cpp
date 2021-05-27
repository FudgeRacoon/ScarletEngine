#include "core/renderer/IndexBuffer.hpp"
using namespace scarlet;

IndexBuffer::IndexBuffer(const uint32_t* data, size_t size)
{
    glGenBuffers(1, &this->ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &this->ID);
}

void IndexBuffer::Bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ID);
}
void IndexBuffer::UnBind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}