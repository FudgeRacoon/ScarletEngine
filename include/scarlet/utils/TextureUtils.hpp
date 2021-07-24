#ifndef TEXTUREUTILS_HPP
#define TEXTUREUTILS_HPP

#include <vector>
#include <string>
#include <cstring>

#include "scarlet/common/Types.hpp"

#include "scarlet/math/Vector2.hpp"

namespace scarlet
{
    class Texture;
    class Sprite;
    class AssetPool;

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