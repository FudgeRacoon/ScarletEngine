#ifndef ASSETPOOL_HPP
#define ASSETPOOL_HPP

#include <map>
#include <string>

#include "core/Sprite.hpp"
#include "core/renderer/Texture.hpp"
#include "core/primitives/Rect.hpp"
#include "core/Logger.hpp"

namespace scarlet
{
    class AssetPool
    {
    private:
        static std::map<std::string, Sprite*> sprites;

    public:
        static Sprite* AddSprite(std::string name, Texture* texture);
        static Sprite* AddSprite(std::string name, Texture* texture, Rect* rect);

    public:
        static Sprite* GetSprite(std::string name);
    };
}

#endif