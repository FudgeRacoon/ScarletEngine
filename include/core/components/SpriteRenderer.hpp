#ifndef SPRITERENDERER_HPP
#define SPRITERENDERER_HPP

//Core Headers
#include "core/Sprite.hpp"
#include "core/Component.hpp"

//Math Headers
#include "core/math/Color.hpp"

namespace scarlet
{
    class Sprite;

    class SpriteRenderer : public Component
    {
    public:
        Sprite* sprite;
        Color   color;
        bool    flipX, flipY;
        uint16  sortingOrder;

    public:
        void Setup() override;
        void Update() override;
    };
}

#endif