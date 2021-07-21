#include "scarlet/graphics/VertexArray.hpp"
using namespace scarlet;

#include "scarlet/utils/Logger.hpp"

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &this->ID);
    glBindVertexArray(0);
}
VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &this->ID);
}

void VertexArray::AddBuffer(VertexBuffer& vertexBuffer, VertexBufferLayout& layout) const
{
    this->Bind();
    vertexBuffer.Bind();

    uint32 offset = 0;

    auto elements = layout.GetElements();

    if(elements.empty())
    {
        Logger::LogError("Failed to add buffer. Must specify a layout.");
    } 
    else
        for(uint32 index = 0; index < elements.size(); index++)
        {
            auto& element = elements[index];
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index, element.format, element.type, element.normalized, layout.GetStride(), (const void*)offset);
            offset += element.format * VertexBufferElements::GetSizeOfType(element.type);
        }
    
    vertexBuffer.UnBind();
    this->UnBind();
}

void VertexArray::Bind() const
{
    glBindVertexArray(this->ID);
}
void VertexArray::UnBind() const
{
    glBindVertexArray(0);
}