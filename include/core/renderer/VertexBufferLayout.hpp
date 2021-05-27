#ifndef VERTEXBUFFERLAYOUT_HPP
#define VERTEXBUFFERLAYOUT_HPP

#include <iostream>
#include <type_traits>
#include <vector>

#include "GL/glew.h"

namespace scarlet
{
    struct VertexBufferElements
    {
        uint32_t type;
        uint32_t format;
        bool normalized;

        static size_t GetSizeOfType(uint32_t type)
        {
            switch (type)
            {
                case GL_FLOAT: return sizeof(float);
                case GL_UNSIGNED_INT: return sizeof(unsigned int);
                case GL_UNSIGNED_BYTE: return sizeof(unsigned char);
            }
        }
    };

    class VertexBufferLayout
    {
    private:
        std::vector<VertexBufferElements> elements;
        size_t stride;

    public:
        VertexBufferLayout()
        {
            this->stride = 0;
        }
        ~VertexBufferLayout() = default;

    public:
        template<typename T>
        void Push(uint32_t format, bool normalized)
        {
            if(std::is_same<T,float>::value)
            {
                VertexBufferElements element;
                element.type = GL_FLOAT;
                element.format = format;
                element.normalized = normalized;

                this->stride += element.format * sizeof(float);

                this->elements.push_back(element);
            }
            else if(std::is_same<T,unsigned int>::value)
            {
                VertexBufferElements element;
                element.type = GL_UNSIGNED_INT;
                element.format = format;
                element.normalized = normalized;

                this->stride += element.format * sizeof(unsigned int);

                this->elements.push_back(element);
            }
            else if(std::is_same<T,unsigned char>::value)
            {
                VertexBufferElements element;
                element.type = GL_UNSIGNED_BYTE;
                element.format = format;
                element.normalized = normalized;

                this->stride += element.format * sizeof(unsigned char);

                this->elements.push_back(element);
            }
            else
            {
                std::cerr << "[WARNING]: Failed to add buffer layout. Unsupported type." << '\n';
                return;
            }
        }

    public:
        std::vector<VertexBufferElements> GetElements()
        {
            return this->elements;
        }
        size_t GetStride()
        {
            return this->stride;
        }
    };
}

#endif