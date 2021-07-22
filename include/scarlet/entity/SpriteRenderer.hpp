#ifndef SPRITERENDERER_HPP
#define SPRITERENDERER_HPP

#include "scarlet/entity/Component.hpp"

#include "scarlet/graphics/Shader.hpp"
#include "scarlet/graphics/Sprite.hpp"

#include "scarlet/math/Color.hpp"

namespace scarlet
{
    class SpriteRenderer : public Component
    {
    public:
        Sprite* sprite;
        Shader* material;

    public:
        Color   color;
        bool    flipX, flipY;
        uint16  sortingOrder;

    public:
        SpriteRenderer();

    public:
        void Setup() override;
        void Update() override;
        void GUI() override;
    };
}

#endif