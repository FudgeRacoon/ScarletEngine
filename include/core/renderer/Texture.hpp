#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "core/math/Math.hpp"

namespace scarlet
{
    class Texture
    {
    private:
        uint32 ID;
        uint8* buffer;

    private:
        int width, height;

    private:
        void FlipTexture(uint8* pixels, int width, int height, int bytesPerPixel);

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