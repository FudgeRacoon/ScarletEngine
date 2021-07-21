#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <vector>
#include <string>

#include "scarlet/graphics/Texture.hpp"

#include "scarlet/primitives/Rect.hpp"

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
        ~Sprite();

    public:
        std::string GetName();
        Texture* GetTexture();
        Rect* GetRect();
        
    public:
        void SetName(std::string name);
        void SetTexture(Texture* texture);
        
    friend AssetPool;
    };
}

#endif