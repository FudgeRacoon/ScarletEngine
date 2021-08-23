#ifndef VERTEXARRAY_HPP
#define VERTEXARRAY_HPP

#include <iostream>

#include "GL/glew.h"

#include "scarlet/core/Types.hpp"
#include "scarlet/core/debug/Assert.hpp"
#include "scarlet/core/logger/Logger.hpp"

#include "scarlet/graphics/VertexBuffer.hpp"

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