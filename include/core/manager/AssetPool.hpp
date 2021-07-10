#ifndef ASSETPOOL_HPP
#define ASSETPOOL_HPP


#include <map>
#include <unordered_map>
#include <string>

#include "core/Sprite.hpp"

#include "core/renderer/Texture.hpp"

#include "core/primitives/Rect.hpp"

#include "core/Logger.hpp"

namespace scarlet
{   

    class AssetPool
    {
    typedef std::map<std::string, Sprite*> SpritesArray;
    typedef std::map<std::string, Texture*> TexturesArray;
    typedef std::unordered_map<uint32, std::vector<Sprite*>> TextureUsersArray;

    private:
        static SpritesArray      sprites;
        static TexturesArray     textures;
        static TextureUsersArray textureUsers;

    public:
        static Sprite* AddSprite(std::string name, Texture* texture);
        static Texture* AddTexture(std::string name, const char* filepath);
        
    public:
        static void RemoveSprite(std::string name);
        static void RemoveTexture(std::string name);

    public:
        static Sprite* GetSprite(std::string name);
        static Texture* GetTexture(std::string name);
    };
}

#endif