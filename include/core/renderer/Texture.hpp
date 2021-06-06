#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "core/math/Math.hpp"

namespace scarlet
{
    class Texture
    {
    private:
        uint32 ID;
        uint32* buffer;

    private:
        int width, height;

    public:
        Texture(const char* filepath);
        ~Texture();

    public:
        int GetWidth();
        int GetHeight();

    public:
        void Bind(uint32 slot = 0) const;
        void UnBind() const;
    };
}

#endif