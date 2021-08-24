#include "scarlet/graphics/buffer/VertexBuffer.hpp"
using namespace scarlet;

VertexBuffer::VertexBuffer(const void* data, size bytes, int usage)
{
    this->stride = 0;

    GLCALL(glGenBuffers(1, &this->vertexBufferId));
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferId));
    GLCALL(glBufferData(GL_ARRAY_BUFFER, bytes, data, usage));
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
VertexBuffer::~VertexBuffer()
{
    this->layouts.clear();

    GLCALL(glDeleteBuffers(1, &this->vertexBufferId));
}

size VertexBuffer::GetStride()
{
    return this->stride;
}
std::vector<VertexBufferLayout> VertexBuffer::GetLayouts()
{
    return this->layouts;
}

void VertexBuffer::UpdateBufferData(size offsetBytes, size bytes, const void* data)
{
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferId));

    GLCALL(glBufferSubData(GL_ARRAY_BUFFER, offsetBytes, bytes, data));
    
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void VertexBuffer::Bind()
{
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferId));
}
void VertexBuffer::UnBind()
{
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}