#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <vector>

#include "GL/glew.h"

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "scarlet/common/Types.hpp"

#include "scarlet/math/Math.hpp"

#include "scarlet/utils/Logger.hpp"
#include "scarlet/utils/TextureUtils.hpp"

namespace scarlet
{   
    class AssetPool;

    class Texture
    {
    private:
        uint32 ID;
        byte* pixels;

    private:
        int width, height;
        int bytesPerPixel;

    private:
        Texture(const char* filepath);
        Texture(uint32 color, uint32 width, uint32 height);
        Texture(uint32* pixels, uint32 width, uint32 height);
        ~Texture();

    public:
        uint32 GetID();
        byte* GetPixels();
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