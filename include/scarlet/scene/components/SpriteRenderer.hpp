#ifndef SPRITERENDERER_HPP
#define SPRITERENDERER_HPP

#include "scarlet/core/Types.hpp"
#include "scarlet/core/math/Color.hpp"

#include "scarlet/graphics/Sprite.hpp"

#include "scarlet/scene/components/Component.hpp"

namespace scarlet
{
    class SpriteRenderer : public Component
    {
    public:
        Sprite* sprite;
        Color   color;
        bool    flipX, flipY;
        uint16  sortingOrder;

    public:
        SpriteRenderer();

    public:
        void Setup() override;
        void Update() override;
    };
}

#endif