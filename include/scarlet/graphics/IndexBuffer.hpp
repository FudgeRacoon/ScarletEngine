#ifndef INDEXBUFFER_HPP
#define INDEXBUFFER_HPP

#include <iostream>

#include "GL/glew.h"

#include "scarlet/math/Math.hpp"

namespace scarlet
{
    class IndexBuffer
    {
    private:
        uint32 ID;
        uint32 count;

    public:
        IndexBuffer(const uint32* data, size_t size);
        ~IndexBuffer();

    public:
        uint32 GetCount();

    public:
        void Bind() const;
        void UnBind() const;
    };
}

#endif