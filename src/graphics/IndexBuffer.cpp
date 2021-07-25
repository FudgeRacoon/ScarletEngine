#include "scarlet/graphics/IndexBuffer.hpp"
#include "scarlet/common/Assert.hpp"
using namespace scarlet;

IndexBuffer::IndexBuffer(const uint32_t* data, size_t size, int usage)
{
    GLCALL(glGenBuffers(1, &this->ID));
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ID));
    GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage));
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

    this->count = size / sizeof(uint32);
}
IndexBuffer::~IndexBuffer()
{
    GLCALL(glDeleteBuffers(1, &this->ID));
}

uint32 IndexBuffer::GetCount()
{
    return this->count;
}

void IndexBuffer::UpdateBufferData(size_t offset, size_t size, const uint32* data)
{
    this->Bind();

    GLCALL(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, data));

    this->UnBind();
}

void IndexBuffer::Bind() const
{
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ID));
}
void IndexBuffer::UnBind() const
{
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}