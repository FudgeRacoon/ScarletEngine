#ifndef VERTEXBUFFER_HPP
#define VERTEXBUFFER_HPP

#include <iostream>
#include "GL/glew.h"

namespace scarlet
{
    class VertexBuffer
    {
    private:
        uint32_t ID;

    public:
        VertexBuffer(const void* data, size_t size, int usage);
        ~VertexBuffer();

    public:
        void UpdateBufferData(size_t offset, size_t size, const void* data);

    public:
        void Bind();
        void UnBind();
    };
}

#endif