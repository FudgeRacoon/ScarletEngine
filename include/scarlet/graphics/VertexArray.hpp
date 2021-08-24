#ifndef VERTEXARRAY_HPP
#define VERTEXARRAY_HPP

#include <iostream>

#include "GL/glew.h"

#include "scarlet/core/Types.hpp"
#include "scarlet/core/debug/Assert.hpp"
#include "scarlet/core/logger/Logger.hpp"

#include "scarlet/graphics/buffer/VertexBuffer.hpp"
#include "scarlet/graphics/buffer/VertexBufferLayout.hpp"

namespace scarlet
{
    class VertexArray
    {
    private:
        uint32 vertexArrayId;

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