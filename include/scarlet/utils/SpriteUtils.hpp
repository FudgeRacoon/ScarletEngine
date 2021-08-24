#ifndef SPRITEUTILS_HPP
#define SPRITEUTILS_HPP

#include <vector>
#include <string>

#include "scarlet/core/Types.hpp"
#include "scarlet/core/math/Vector2.hpp"

namespace scarlet
{
    class Sprite;
    class AssetManager;

    class SpriteUtils
    {
    public:
        static void FlipSpriteX(Sprite* sprite);
        static void FlipSpriteY(Sprite* sprite);

    public:
        static std::vector<Sprite*> SliceSprite(Sprite* sprite, int spriteWidth, int spriteHeight);
    };
};

#endif