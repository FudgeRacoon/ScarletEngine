#ifndef SPRITE_HPP
#define SPRITE_HPP

#include "core/renderer/Texture.hpp"
#include "core/primitives/Rect.hpp"

namespace scarlet
{
    class Sprite
    {
    private:
        Texture* texture = nullptr;
        Rect* rect = nullptr;
        
    public:
        Sprite();
        Sprite(Texture* texture);
        Sprite(Texture* texture, Rect* rect);
        ~Sprite();

    public:
        void SetTexture(Texture* texture);
        Texture* GetTexture();

        Rect* GetRect();
    };
}

#endif