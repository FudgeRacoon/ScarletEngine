#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <vector>
#include <string>

#include "scarlet/core/math/Vector2.hpp"

#include "scarlet/graphics/Texture.hpp"

#include "scarlet/primitives/Rect.hpp"

namespace scarlet
{
    class AssetManager;

    class Sprite
    {
    private:
        std::string name;
        
    private:
        Rect rect;
        Texture* texture = nullptr;
        std::vector<Vector2> uv;
        
    private:
        Sprite(std::string name, Texture* texture);
        Sprite(std::string name, Texture* texture, std::vector<Vector2> uv);
        ~Sprite();

    public:
        std::string GetName();
        Texture* GetTexture();
        Rect GetRect();
        std::vector<Vector2> GetUV();
        
    public:
        void SetName(std::string name);
        void SetTexture(Texture* texture);
        void SetRect(Rect rect);
        void SetUV(std::vector<Vector2> uv);

    friend AssetManager;
    };
}

#endif