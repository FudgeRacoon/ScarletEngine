#ifndef VERTEXBUFFERLAYOUT_HPP
#define VERTEXBUFFERLAYOUT_HPP

#include "GL/glew.h"

#include "scarlet/core/Types.hpp"

namespace scarlet
{
    struct VertexBufferLayout
    {
        uint32 type;
        uint32 format;
        
        bool normalized;

        static size GetSizeOfType(uint32 type);
    };
}

#endif