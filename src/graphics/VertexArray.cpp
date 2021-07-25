#include "scarlet/graphics/VertexArray.hpp"
#include "scarlet/common/Assert.hpp"
using namespace scarlet;

VertexArray::VertexArray()
{
    GLCALL(glGenVertexArrays(1, &this->ID));
    GLCALL(glBindVertexArray(0));
}
VertexArray::~VertexArray()
{
    GLCALL(glDeleteVertexArrays(1, &this->ID));
}

void VertexArray::AddBuffer(VertexBuffer* vertexBuffer) const
{
    this->Bind();
    vertexBuffer->Bind();

    uint32 offset = 0;

    auto layouts = vertexBuffer->GetLayouts();

    if(layouts.empty())
    {
        Logger::LogError("Failed to add buffer. Must specify a layout.");
    } 
    else
        for(uint32 index = 0; index < layouts.size(); index++)
        {
            auto& layout = layouts[index];
            GLCALL(glEnableVertexAttribArray(index));
            GLCALL(glVertexAttribPointer(index, layout.format, layout.type, layout.normalized, vertexBuffer->GetStride(), (const void*)offset));
            offset += layout.format * VertexBufferLayout::GetSizeOfType(layout.type);
        }
    
    vertexBuffer->UnBind();
    this->UnBind();
}

void VertexArray::Bind() const
{
    GLCALL(glBindVertexArray(this->ID));
}
void VertexArray::UnBind() const
{
    GLCALL(glBindVertexArray(0));
}