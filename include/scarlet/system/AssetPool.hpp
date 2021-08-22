#ifndef ASSETPOOL_HPP
#define ASSETPOOL_HPP

#include <map>
#include <unordered_map>
#include <string>

#include "scarlet/entity/SpriteRenderer.hpp"

#include "scarlet/graphics/GraphicsContext.hpp"
#include "scarlet/graphics/Texture.hpp"
#include "scarlet/graphics/Sprite.hpp"
#include "scarlet/graphics/Shader.hpp"

#include "scarlet/math/Vector2.hpp"

#include "scarlet/utils/logger/Logger.hpp"

namespace scarlet
{   
    class SceneManager;

    class AssetPool
    {
    public:
        typedef std::map<std::string, Sprite*> SpritesTreeMap;
        typedef std::map<std::string, Shader*> ShadersTreeMap;
        typedef std::map<std::string, Texture*> TexturesTreeMap;
        typedef std::unordered_map<uint32, std::vector<Sprite*>> TextureUsersHashMap;

    private:
        static SpritesTreeMap      sprites;
        static ShadersTreeMap      shaders;
        static TexturesTreeMap     textures;
        static TextureUsersHashMap textureUsers; 

    public:
        static void OnInit();
        static void OnShutDown();

    public:
        static Sprite* AddSprite(std::string name, Texture* texture);
        static Sprite* AddSprite(std::string name, Texture* texture, std::vector<Vector2> uv);

    public:
        static Shader* AddShader(std::string name, const char* filepath);

    public:
        static Texture* AddTexture(std::string name, const char* filepath);
        static Texture* AddTexture(std::string name, uint32 color, uint32 width, uint32 height);
        static Texture* AddTexture(std::string name, void* pixels, uint32 width, uint32 height);
        
    public:
        static void RemoveSprite(std::string name);
        static void RemoveShader(std::string name);
        static void RemoveTexture(std::string name);

    public:
        static Sprite* GetSprite(std::string name);
        static Shader* GetShader(std::string name); 
        static Texture* GetTexture(std::string name);
    
    public:
        static SpritesTreeMap GetSprites();
        static ShadersTreeMap GetShaders();
        static TexturesTreeMap GetTextures();
    };
}

#endif