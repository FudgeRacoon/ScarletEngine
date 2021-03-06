#include "scarlet/system/AssetManager.hpp"
using namespace scarlet;

#include "scarlet/graphics/Renderer.hpp"
#include "scarlet/system/SceneManager.hpp"

AssetManager::SpritesTreeMap AssetManager::sprites;
AssetManager::ShadersTreeMap AssetManager::shaders;
AssetManager::TexturesTreeMap AssetManager::textures;

AssetManager::TextureUsersHashMap AssetManager::textureUsers;

void AssetManager::OnInit()
{
    Shader* shader = nullptr;

    shader = AddShader("default_shader", "assets\\shaders\\defaultFragment.shader");
    shader->Bind();
    for(int i = 0; i < GraphicsContext::GetMaxTextureSlots(); i++)
        shader->SetInt("textures[" + std::to_string(i) + "]", i);
    shader->UnBind();

    shader = AddShader("selection_shader", "assets\\shaders\\selectionFragment.shader");
    shader->Bind();
    for(int i = 0; i < GraphicsContext::GetMaxTextureSlots(); i++)
        shader->SetInt("textures[" + std::to_string(i) + "]", i);
    shader->UnBind();

    AddTexture("white_texture", 0xffffffff, 32, 32);
}
void AssetManager::OnShutDown()
{
    
}

Sprite* AssetManager::AddSprite(std::string name, Texture* texture)
{
    auto spritesIterator = sprites.find(name);
    if(spritesIterator != sprites.end())
    {
        Logger::LogWarning("Sprite name already exists.");
        return nullptr;
    }

    Sprite* sprite = new Sprite(name, texture);
    sprites.insert(
        std::make_pair(
            name, 
            sprite
        )
    );
    
    auto textureUsersIterator = textureUsers.find(texture->GetId());
    textureUsersIterator->second.push_back(sprite);

    return sprite;
}
Sprite* AssetManager::AddSprite(std::string name, Texture* texture, std::vector<Vector2> uv)
{   
    auto spritesIterator = sprites.find(name);
    if(spritesIterator != sprites.end())
    {
        Logger::LogWarning("Sprite name already exists.");
        return nullptr;
    }

    Sprite* sprite = new Sprite(name, texture, uv);
    sprites.insert(
        std::make_pair(
            name, 
            sprite
        )
    );
    
    auto textureUsersIterator = textureUsers.find(texture->GetId());
    textureUsersIterator->second.push_back(sprite);

    return sprite;
}

Shader* AssetManager::AddShader(std::string name, const char* filepath)
{
    auto it = shaders.find(name);
    if(it != shaders.end())
    {
        Logger::LogWarning("Shader name already exists.");
        return nullptr;
    }

    Shader* shader = new Shader("assets\\shaders\\defaultVertex.shader", filepath);
    shaders.insert(
        std::make_pair(
            name, 
            shader
        )
    );

    return shader;
}

Texture* AssetManager::AddTexture(std::string name, const char* filepath)
{
    auto it = textures.find(name);
    if(it != textures.end())
    {
        Logger::LogWarning("Texture name already exists.");
        return nullptr;
    }

    Texture* texture = new Texture(filepath);
    textures.insert(
        std::make_pair(
            name, 
            texture
        )
    );

    textureUsers.insert(
        std::make_pair(
            texture->GetId(),
            std::vector<Sprite*>()
        )
    );
    
    return texture;
}
Texture* AssetManager::AddTexture(std::string name, uint32 color, uint32 width, uint32 height)
{
    auto it = textures.find(name);
    if(it != textures.end())
    {
        Logger::LogWarning("Texture name already exists.");
        return nullptr;
    }

    Texture* texture = new Texture(color, width, height);
    textures.insert(
        std::make_pair(
            name,
            texture
        )
    );

    textureUsers.insert(
        std::make_pair(
            texture->GetId(),
            std::vector<Sprite*>()
        )
    );

    return texture;
}
Texture* AssetManager::AddTexture(std::string name, void* pixels, uint32 width, uint32 height)
{
    auto it = textures.find(name);
    if(it != textures.end())
    {
        Logger::LogWarning("Texture name already exists.");
        return nullptr;
    }

    Texture* texture = new Texture(pixels, width, height);
    textures.insert(
        std::make_pair(
            name, 
            texture
        )
    );

    textureUsers.insert(
        std::make_pair(
            texture->GetId(),
            std::vector<Sprite*>()
        )
    );

    return texture;
}

void AssetManager::RemoveSprite(std::string name)
{
    auto it = sprites.find(name);
    if(it != sprites.end())
    {
        std::vector<GameObject*> entities = SceneManager::Get()->GetActiveScene()->GetEntitiesOfType<SpriteRenderer>();
        
        for(GameObject* entity : entities)
        {
            SpriteRenderer* spriteRenderer = entity->GetComponent<SpriteRenderer>();
            if(spriteRenderer->sprite == it->second)
                spriteRenderer->sprite = nullptr;
        }

        delete it->second;
        sprites.erase(it);
    }
    else
        Logger::LogWarning("Sprite does not exist.");
}
void AssetManager::RemoveShader(std::string name)
{
    auto it = shaders.find(name);
    if(it != shaders.end())
    {
        if(Renderer::GetBoundShader() == it->second)
            Renderer::BindShader(GetShader("DefaultShader"));

        delete it->second;
        shaders.erase(it);
    }
    else
        Logger::LogWarning("Shader does not exist.");
}
void AssetManager::RemoveTexture(std::string name)
{
    auto textureIterator = textures.find(name);
    if(textureIterator != textures.end())
    {
        auto textureUsersIterator = textureUsers.find(textureIterator->second->GetId());
        for(Sprite* sprite : textureUsersIterator->second)
            sprite->SetTexture(nullptr);

        textureUsersIterator->second.clear();
        textureUsers.erase(textureUsersIterator);

        delete textureIterator->second;
        textures.erase(textureIterator);
    }
    else
        Logger::LogWarning("Texture does not exist.");
}

Sprite* AssetManager::GetSprite(std::string name)
{
    auto it = sprites.find(name);
    if(it != sprites.end())
        return it->second;

    Logger::LogWarning("Sprite does not exist.");
    return nullptr;
}
Shader* AssetManager::GetShader(std::string name)
{
    auto it = shaders.find(name);
    if(it != shaders.end())
        return it->second;

    Logger::LogWarning("Shader does not exist.");
    return nullptr;
}
Texture* AssetManager::GetTexture(std::string name)
{
    auto it = textures.find(name);
    if(it != textures.end())
        return it->second;

    Logger::LogWarning("Texture does not exist.");
    return nullptr;
}

AssetManager::SpritesTreeMap AssetManager::GetSprites()
{
    return sprites;
}
AssetManager::ShadersTreeMap AssetManager::GetShaders()
{
    return shaders;
}
AssetManager::TexturesTreeMap AssetManager::GetTextures()
{
    return textures;
}