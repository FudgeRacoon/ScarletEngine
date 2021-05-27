#ifndef VERTEXARRAY_HPP
#define VERTEXARRAY_HPP

#include <iostream>

#include "core/renderer/VertexBuffer.hpp"
#include "core/renderer/VertexBufferLayout.hpp"

namespace scarlet
{
    class VertexArray
    {
    private:
        uint32_t ID;

    public:
        VertexArray();
        ~VertexArray();

    public:
        void AddBuffer(VertexBuffer& vertexBuffer, VertexBufferLayout& layout);

    public:
        void Bind();
        void UnBind();
    };
}

#endif