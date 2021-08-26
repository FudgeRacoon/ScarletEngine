#ifndef AssetManager_HPP
#define AssetManager_HPP

#include <map>
#include <unordered_map>
#include <string>

#include "scarlet/core/math/Vector2.hpp"
#include "scarlet/core/logger/Logger.hpp"

#include "scarlet/scene/components/SpriteRenderer.hpp"

#include "scarlet/graphics/GraphicsContext.hpp"
#include "scarlet/graphics/Texture.hpp"
#include "scarlet/graphics/Sprite.hpp"
#include "scarlet/graphics/Shader.hpp"

namespace scarlet
{   
    class SceneManager;

    class AssetManager
    {
    public:
        using SpritesTreeMap = std::map<std::string, Sprite*>;
        using ShadersTreeMap = std::map<std::string, Shader*>;
        using TexturesTreeMap = std::map<std::string, Texture*>;
        using TextureUsersHashMap = std::unordered_map<uint32, std::vector<Sprite*>>;

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