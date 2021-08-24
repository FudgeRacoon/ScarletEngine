#include "scarlet/graphics/VertexArray.hpp"
using namespace scarlet;

VertexArray::VertexArray()
{
    GLCALL(glGenVertexArrays(1, &this->vertexArrayId));
    GLCALL(glBindVertexArray(0));
}
VertexArray::~VertexArray()
{
    GLCALL(glDeleteVertexArrays(1, &this->vertexArrayId));
}

void VertexArray::AddBuffer(VertexBuffer* vertexBuffer) const
{
    uint32 offset = 0;
    std::vector<VertexBufferLayout> layouts = vertexBuffer->GetLayouts();
    
    vertexBuffer->Bind();

    GLCALL(glBindVertexArray(this->vertexArrayId));

    if(layouts.empty())
        Logger::LogError("Failed to add buffer. Must specify a layout.");
    else
        for(uint32 index = 0; index < layouts.size(); index++)
        {
            VertexBufferLayout layout = layouts[index];

            GLCALL(glEnableVertexAttribArray(index));
            GLCALL(glVertexAttribPointer(index, layout.format, layout.type, layout.normalized, vertexBuffer->GetStride(), (const void*)offset));
            
            offset += layout.format * VertexBufferLayout::GetSizeOfType(layout.type);
        }
    
    GLCALL(glBindVertexArray(0));
    
    vertexBuffer->UnBind();
}

void VertexArray::Bind() const
{
    GLCALL(glBindVertexArray(this->vertexArrayId));
}
void VertexArray::UnBind() const
{
    GLCALL(glBindVertexArray(0));
}