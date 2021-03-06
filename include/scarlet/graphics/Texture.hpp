#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <vector>

#include "GL/glew.h"

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "scarlet/core/Types.hpp"
#include "scarlet/core/logger/Logger.hpp"
#include "scarlet/core/debug/Assert.hpp"
#include "scarlet/core/math/Math.hpp"

#include "scarlet/utils/MemoryUtils.hpp"

namespace scarlet
{   
    class AssetManager;

    class Texture
    {
    private:
        uint32 textureId;

    private:
        int width, height;
        int bytesPerPixel;

    private:
        Texture(const char* filepath);
        Texture(uint32 color, uint32 width, uint32 height);
        Texture(void* pixels, uint32 width, uint32 height);
        ~Texture();

    public:
        uint32 GetId();
        int GetWidth();
        int GetHeight();
        int GetBytesPerPixel();
        
    public:
        void Bind(uint32 slot = 0) const;
        void UnBind() const;

    friend AssetManager;
    };
}

#endif