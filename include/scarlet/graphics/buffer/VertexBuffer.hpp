#ifndef VERTEXBUFFER_HPP
#define VERTEXBUFFER_HPP

#include <iostream>
#include <vector>
#include <type_traits>

#include "GL/glew.h"

#include "scarlet/core/Types.hpp"
#include "scarlet/core/debug/Assert.hpp"

#include "VertexBufferLayout.hpp"

namespace scarlet
{   
    class VertexBuffer
    {
    private:
        uint32 vertexBufferId;

    private:
        size stride;
        std::vector<VertexBufferLayout> layouts;

    public:
        VertexBuffer(const void* data, size bytes, int usage);
        ~VertexBuffer();

    public:
        size GetStride();
        std::vector<VertexBufferLayout> GetLayouts();

    public:
        template<typename T>
        void AddLayout(int format, bool normalized)
        {
            if(std::is_same<T,float>::value)
            {
                VertexBufferLayout layout;
                layout.type = GL_FLOAT;
                layout.format = format;
                layout.normalized = normalized;

                this->stride += layout.format * sizeof(float);

                this->layouts.push_back(layout);
            }
            else if(std::is_same<T,unsigned int>::value)
            {
                VertexBufferLayout layout;
                layout.type = GL_UNSIGNED_INT;
                layout.format = format;
                layout.normalized = normalized;

                this->stride += layout.format * sizeof(unsigned int);

                this->layouts.push_back(layout);
            }
            else if(std::is_same<T,unsigned char>::value)
            {
                VertexBufferLayout layout;
                layout.type = GL_UNSIGNED_BYTE;
                layout.format = format;
                layout.normalized = normalized;

                this->stride += layout.format * sizeof(unsigned char);

                this->layouts.push_back(layout);
            }
            else
            {
                std::cerr << "[WARNING]: Failed to add buffer layout. Unsupported type." << '\n';
                return;
            }
        }

    public:
        void UpdateBufferData(size offsetBytes, size bytes, const void* data);

    public:
        void Bind();
        void UnBind();
    };
}

#endif