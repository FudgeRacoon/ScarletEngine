#ifndef INDEXBUFFER_HPP
#define INDEXBUFFER_HPP

#include <iostream>
#include "GL/glew.h"

namespace scarlet
{
    class IndexBuffer
    {
    private:
        uint32_t ID;

    public:
        IndexBuffer(const uint32_t* data, size_t size);
        ~IndexBuffer();

    public:
        void Bind() const;
        void UnBind() const;
    };
}

#endif