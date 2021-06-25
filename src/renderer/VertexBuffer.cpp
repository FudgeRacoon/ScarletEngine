#include "core/renderer/VertexBuffer.hpp"
using namespace scarlet;

VertexBuffer::VertexBuffer(const void* data, size_t size, int usage)
{
    glGenBuffers(1, &this->ID);
    glBindBuffer(GL_ARRAY_BUFFER, this->ID);
    glBufferData(GL_ARRAY_BUFFER, size, data, usage);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &this->ID);
}

void VertexBuffer::UpdateBufferData(size_t offset, size_t size, const void* data)
{
    glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
}

void VertexBuffer::Bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, this->ID);
}
void VertexBuffer::UnBind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}