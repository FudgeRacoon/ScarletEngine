#ifndef INDEXBUFFER_HPP
#define INDEXBUFFER_HPP

#include <iostream>

#include "GL/glew.h"

#include "scarlet/core/Types.hpp"
#include "scarlet/core/debug/Assert.hpp"
#include "scarlet/core/math/Math.hpp"

namespace scarlet
{
    class IndexBuffer
    {
    private:
        uint32 indexBufferId;
        uint32 indexCount;

    public:
        IndexBuffer(const uint32* data, size bytes, int usage);
        ~IndexBuffer();

    public:
        uint32 GetIndexCount();

    public:
        void UpdateBufferData(size offsetBytes, size bytes, const uint32* data);

    public:
        void Bind() const;
        void UnBind() const;
    };
}

#endif