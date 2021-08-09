#include "scarlet/graphics/VertexBuffer.hpp"
using namespace scarlet;

VertexBuffer::VertexBuffer(const void* data, size_t size, int usage)
{
    GLCALL(glGenBuffers(1, &this->ID));
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, this->ID));
    GLCALL(glBufferData(GL_ARRAY_BUFFER, size, data, usage));
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));

    this->stride = 0;
}
VertexBuffer::~VertexBuffer()
{
    this->layouts.clear();
    GLCALL(glDeleteBuffers(1, &this->ID));
}

std::vector<VertexBufferLayout> VertexBuffer::GetLayouts()
{
    return this->layouts;
}
size_t VertexBuffer::GetStride()
{
    return this->stride;
}

void VertexBuffer::UpdateBufferData(size_t offset, size_t size, const void* data)
{
    Bind();

    GLCALL(glBufferSubData(GL_ARRAY_BUFFER, offset, size, data));
    
    UnBind();
}

void VertexBuffer::Bind()
{
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, this->ID));
}
void VertexBuffer::UnBind()
{
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}