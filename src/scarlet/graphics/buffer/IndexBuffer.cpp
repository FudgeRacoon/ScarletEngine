#include "scarlet/graphics/buffer/IndexBuffer.hpp"
using namespace scarlet;

IndexBuffer::IndexBuffer(const uint32_t* data, size bytes, int usage)
{
    GLCALL(glGenBuffers(1, &this->indexBufferId));
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBufferId));
    GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, bytes, data, usage));
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

    this->indexCount = bytes / sizeof(uint32);
}
IndexBuffer::~IndexBuffer()
{
    GLCALL(glDeleteBuffers(1, &this->indexBufferId));
}

uint32 IndexBuffer::GetIndexCount()
{
    return this->indexCount;
}

void IndexBuffer::UpdateBufferData(size offsetBytes, size bytes, const uint32* data)
{
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBufferId));

    GLCALL(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offsetBytes, bytes, data));

    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

void IndexBuffer::Bind() const
{
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBufferId));
}
void IndexBuffer::UnBind() const
{
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}