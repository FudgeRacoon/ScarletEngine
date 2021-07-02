#include "core/manager/AssetPool.hpp"
using namespace scarlet;

std::map<std::string, Sprite*> AssetPool::sprites;

Sprite* AssetPool::AddSprite(std::string name, Texture* texture)
{
    Sprite* sprite = new Sprite(texture);
    sprites.insert(std::make_pair(name, sprite));
    return sprite;
}
Sprite* AssetPool::AddSprite(std::string name, Texture* texture, Rect* rect)
{
    Sprite* sprite = new Sprite(texture, rect);
    sprites.insert(std::make_pair(name, sprite));
    return sprite;
}

Sprite* AssetPool::GetSprite(std::string name)
{
    auto it = sprites.find(name);
    if(it != sprites.end())
        return it->second;

    Logger::LogWarning("Sprite does not exist.");
    return nullptr;
}