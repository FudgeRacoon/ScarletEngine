#ifndef SPRITEUTILS_HPP
#define SPRITEUTILS_HPP

#include <vector>
#include <string>

#include "core/manager/AssetPool.hpp"
#include "core/Sprite.hpp"
#include "core/math/Vector2.hpp"

namespace scarlet
{
    class SpriteUtils
    {
    public:
        static std::vector<Sprite*>& SliceSprite(std::string name, Sprite* sprite, int spriteWidth, int spriteHeight, int numberOfSprites);
    };
};

#endif