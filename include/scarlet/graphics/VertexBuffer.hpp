#ifndef VERTEXBUFFER_HPP
#define VERTEXBUFFER_HPP

#include <iostream>
#include <vector>
#include <type_traits>

#include "GL/glew.h"

#include "scarlet/common/Types.hpp"

namespace scarlet
{   
    struct VertexBufferLayout
    {
        uint32 type;
        uint32 format;
        bool normalized;

        static size_t GetSizeOfType(uint32 type)
        {
            switch (type)
            {
                case GL_FLOAT: return sizeof(float); break;
                case GL_UNSIGNED_INT: return sizeof(unsigned int); break;
                case GL_UNSIGNED_BYTE: return sizeof(unsigned char); break;
            }
        }
    };

    class VertexBuffer
    {
    private:
        uint32 ID;

    private:
        std::vector<VertexBufferLayout> layouts;
        size_t stride;

    public:
        VertexBuffer(const void* data, size_t size, int usage);
        ~VertexBuffer();

    public:
        std::vector<VertexBufferLayout> GetLayouts();
        size_t GetStride();

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
        void UpdateBufferData(size_t offset, size_t size, const void* data);

    public:
        void Bind();
        void UnBind();
    };
}

#endif