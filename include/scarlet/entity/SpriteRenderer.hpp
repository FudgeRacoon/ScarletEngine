#ifndef SPRITERENDERER_HPP
#define SPRITERENDERER_HPP

#include "scarlet/common/Types.hpp"

#include "scarlet/entity/Component.hpp"

#include "scarlet/graphics/Sprite.hpp"

#include "scarlet/math/Color.hpp"

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
        void UIUpdate() override;
    };
}

#endif