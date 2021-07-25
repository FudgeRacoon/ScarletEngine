#include "scarlet/system/AssetPool.hpp"
#include "scarlet/graphics/Sprite.hpp"
using namespace scarlet;

#include "scarlet/entity/SpriteRenderer.hpp"

#include "scarlet/system/SceneManager.hpp"

AssetPool::SpritesTreeMap AssetPool::sprites;
AssetPool::TexturesTreeMap AssetPool::textures;

AssetPool::TextureUsersHashMap AssetPool::textureUsers;

Sprite* AssetPool::AddSprite(std::string name, Texture* texture)
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
    
    auto textureUsersIterator = textureUsers.find(texture->GetID());
    textureUsersIterator->second.push_back(sprite);

    return sprite;
}
Texture* AssetPool::AddTexture(std::string name, const char* filepath)
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
            texture->GetID(),
            std::vector<Sprite*>()
        )
    );
    
    return texture;
}

void AssetPool::RemoveSprite(std::string name)
{
    auto it = sprites.find(name);
    if(it != sprites.end())
    {
        std::vector<GameObject*> gameObjects = SceneManager::Get()->GetActiveScene()->GetGameObjectsOfType<SpriteRenderer>();
        
        for(GameObject* gameObject : gameObjects)
        {
            SpriteRenderer* spriteRenderer = gameObject->GetComponent<SpriteRenderer>();
            if(spriteRenderer->sprite == it->second)
                spriteRenderer->sprite = nullptr;
        }

        delete it->second;
        sprites.erase(it);
    }
    else
        Logger::LogWarning("Sprite does not exist.");
}
void AssetPool::RemoveTexture(std::string name)
{
    auto textureIterator = textures.find(name);
    if(textureIterator != textures.end())
    {
        auto textureUsersIterator = textureUsers.find(textureIterator->second->GetID());
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

Sprite* AssetPool::GetSprite(std::string name)
{
    auto it = sprites.find(name);
    if(it != sprites.end())
        return it->second;

    Logger::LogWarning("Sprite does not exist.");
    return nullptr;
}
Texture* AssetPool::GetTexture(std::string name)
{
    auto it = textures.find(name);
    if(it != textures.end())
        return it->second;

    Logger::LogWarning("Texture does not exist.");
    return nullptr;
}

AssetPool::SpritesTreeMap AssetPool::GetSprites()
{
    return sprites;
}
AssetPool::TexturesTreeMap AssetPool::GetTextures()
{
    return textures;
}