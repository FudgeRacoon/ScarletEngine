#ifndef TEXTUREUTILS_HPP
#define TEXTUREUTILS_HPP

#include <vector>
#include <string>
#include <cstring>

#include "scarlet/core/Types.hpp"
#include "scarlet/core/math/Vector2.hpp"

#include "scarlet/utils/MemoryUtils.hpp"

namespace scarlet
{
    class Texture;
    class Sprite;
    class AssetManager;

    class TextureUtils
    {
    public:
        static void FlipTextureX(Texture* texutre);
        static void FlipTextureY(Texture* texture);
    
    public:
        static std::vector<Sprite*> SliceSprite(Sprite* sprite, int spriteWidth, int spriteHeight);
    };
};

#endif