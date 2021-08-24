#include "scarlet/graphics/buffer/VertexBufferLayout.hpp"
using namespace scarlet;

size VertexBufferLayout::GetSizeOfType(uint32 type)
{
    switch (type)
    {
        case GL_FLOAT: return sizeof(float); break;
        case GL_UNSIGNED_INT: return sizeof(unsigned int); break;
        case GL_UNSIGNED_BYTE: return sizeof(unsigned char); break;
    }
}