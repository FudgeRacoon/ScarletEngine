#include "core/renderer/VertexArray.hpp"
#include <windows.h>
using namespace scarlet;

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &this->ID);
}
VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &this->ID);
}

void VertexArray::AddBuffer(VertexBuffer& vertexBuffer, VertexBufferLayout& layout)
{
    this->Bind();
    vertexBuffer.Bind();

    uint32_t offset = 0;

    auto elements = layout.GetElements();

    if(elements.empty())
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 4);
        std::cerr << "[WARNING]: Failed to add buffer. Must specify a layout." << '\n';
        SetConsoleTextAttribute(hConsole, 7);
    } 
    else
        for(uint32_t index = 0; index < elements.size(); index++)
        {
            auto& element = elements[index];
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index, element.format, element.type, element.normalized, layout.GetStride(), (const void*)offset);
            offset += element.format * VertexBufferElements::GetSizeOfType(element.type);
        }
    
    vertexBuffer.UnBind();
    this->UnBind();
}

void VertexArray::Bind()
{
    glBindVertexArray(this->ID);
}
void VertexArray::UnBind()
{
    glBindVertexArray(0);
}