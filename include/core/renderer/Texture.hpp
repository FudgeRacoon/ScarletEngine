#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <vector>

#include "GL/glew.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "core/Logger.hpp"

#include "core/utils/Utilites.hpp"

namespace scarlet
{   
    class AssetPool;

    class Texture
    {
    private:
        uint32 ID;
        uint8* buffer;

    private:
        int width, height;
        int bytesPerPixel;

    private:
        Texture(const char* filepath);
        ~Texture();

    public:
        uint32 GetID();
        uint8* GetPixels();

    public:
        int GetWidth();
        int GetHeight();
        int GetBytesPerPixel();
        
    public:
        void Bind(uint32 slot = 0) const;
        void UnBind() const;

    friend AssetPool;
    };
}

#endif