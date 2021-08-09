#ifndef INDEXBUFFER_HPP
#define INDEXBUFFER_HPP

#include <iostream>

#include "GL/glew.h"

#include "scarlet/debug/Assert.hpp"

#include "scarlet/math/Math.hpp"

namespace scarlet
{
    class IndexBuffer
    {
    private:
        uint32 ID;
        uint32 count;

    public:
        IndexBuffer(const uint32* data, size_t size, int usage);
        ~IndexBuffer();

    public:
        uint32 GetCount();

    public:
        void UpdateBufferData(size_t offset, size_t size, const uint32* data);

    public:
        void Bind() const;
        void UnBind() const;
    };
}

#endif