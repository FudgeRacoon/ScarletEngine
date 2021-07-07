#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <string>

#include "core/renderer/Texture.hpp"
#include "core/primitives/Rect.hpp"

namespace scarlet
{
    class AssetPool;

    class Sprite
    {
    private:
        std::string name;
        
    private:
        Texture* texture = nullptr;
        Rect* rect = nullptr;
    
    private:
        Sprite(std::string name);
        Sprite(std::string name, Texture* texture);
        Sprite(std::string name, Texture* texture, Rect* rect);
        ~Sprite();

    public:
        void SetTexture(Texture* texture);
        Texture* GetTexture();

    public:
        void SetName(std::string name);
        std::string GetName();

    public:
        Rect* GetRect();

        friend AssetPool;
    };
}

#endif