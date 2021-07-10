#include "core/renderer/IndexBuffer.hpp"
using namespace scarlet;

IndexBuffer::IndexBuffer(const uint32_t* data, size_t size)
{
    glGenBuffers(1, &this->ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    this->count = size / sizeof(uint32);
}
IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &this->ID);
}

uint32 IndexBuffer::GetCount()
{
    return this->count;
}

void IndexBuffer::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ID);
}
void IndexBuffer::UnBind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}