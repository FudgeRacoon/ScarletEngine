#ifndef UTILITES_HPP
#define UTILITES_HPP

#include <vector>
#include <string>

#include "core/math/Vector2.hpp"

namespace scarlet
{
    class Texture;
    class Sprite;
    class AssetPool;

    class Utilites
    {
    public:
        static void FlipTextureX(Texture* texutre);
        static void FlipTextureY(Texture* texture);
    
    public:
        static std::vector<Sprite*> SliceSprite(Sprite* sprite, int spriteWidth, int spriteHeight);
    };
};

#endif