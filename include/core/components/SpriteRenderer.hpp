#ifndef SPRITERENDERER_HPP
#define SPRITERENDERER_HPP

#include "core/Component.hpp"
#include "core/Sprite.hpp"
#include "core/math/Color.hpp"
#include "core/Logger.hpp" 

namespace scarlet
{
    class SpriteRenderer : public Component
    {
    public:
        Sprite* sprite;
        Color color;
        bool flipX, flipY;
        int sortingOrder;

    public:
        void Setup() override
        {
            this->sprite = nullptr;
            this->flipX = false;
            this->flipY = false;
            this->sortingOrder = 0;
        }

        void Update() override
        {
            
        }
    };
}

#endif