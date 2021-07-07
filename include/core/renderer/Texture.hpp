#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "core/utils/Utilites.hpp"
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
        int bytesPerPixel;

    public:
        Texture(const char* filepath);
        ~Texture();

    public:
        int GetWidth();
        int GetHeight();
        int GetBytesPerPixel();
        uint8* GetPixels();

    public:
        void Bind(uint32 slot = 0) const;
        void UnBind() const;
    };
}

#endif