#ifndef ASSETPOOL_HPP
#define ASSETPOOL_HPP

#include <map>
#include <unordered_map>
#include <string>

#include "scarlet/graphics/Texture.hpp"
#include "scarlet/graphics/Sprite.hpp"

#include "scarlet/primitives/Rect.hpp"

#include "scarlet/utils/Logger.hpp"

namespace scarlet
{   

    class AssetPool
    {
    public:
        typedef std::map<std::string, Sprite*> SpritesTreeMap;
        typedef std::map<std::string, Texture*> TexturesTreeMap;
        typedef std::unordered_map<uint32, std::vector<Sprite*>> TextureUsersHashMap;

    private:
        static SpritesTreeMap      sprites;
        static TexturesTreeMap     textures;
        static TextureUsersHashMap textureUsers; 

    public:
        static Sprite* AddSprite(std::string name, Texture* texture);
        static Texture* AddTexture(std::string name, const char* filepath);
        
    public:
        static void RemoveSprite(std::string name);
        static void RemoveTexture(std::string name);

    public:
        static Sprite* GetSprite(std::string name);
        static Texture* GetTexture(std::string name);
    
    public:
        static SpritesTreeMap GetSprites();
        static TexturesTreeMap GetTextures();
    };
}

#endif