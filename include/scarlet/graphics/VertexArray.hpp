#ifndef VERTEXARRAY_HPP
#define VERTEXARRAY_HPP

#include <iostream>

#include "GL/glew.h"

#include "scarlet/common/Types.hpp"

#include "scarlet/debug/Assert.hpp"

#include "scarlet/graphics/VertexBuffer.hpp"

#include "scarlet/utils/logger/Logger.hpp"

namespace scarlet
{
    class VertexArray
    {
    private:
        uint32 ID;

    public:
        VertexArray();
        ~VertexArray();

    public:
        void AddBuffer(VertexBuffer* vertexBuffer) const;

    public:
        void Bind() const;
        void UnBind() const;
    };
}

#endif