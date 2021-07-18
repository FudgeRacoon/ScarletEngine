#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <vector>
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
        ~Sprite();

    public:
        Texture* GetTexture();
        void SetTexture(Texture* texture);

    public:
        Rect* GetRect();

    public:
        std::string GetName();
        void SetName(std::string name);

    friend AssetPool;
    };
}

#endif