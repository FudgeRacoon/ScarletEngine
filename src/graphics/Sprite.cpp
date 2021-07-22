#include "scarlet/graphics/Sprite.hpp"
#include "scarlet/graphics/Texture.hpp"
using namespace scarlet;

Sprite::Sprite(std::string name)
{
    this->name = name;
    this->rect = new Rect(-32.0f, 32.0f, 64.0f, 64.0f);
}
Sprite::Sprite(std::string name, Texture* texture)
{
    this->name = name;
    this->texture = texture;
    this->rect = new Rect(-32.0f, 32.0f, 64.0f, 64.0f);
}
Sprite::~Sprite()
{
    delete this->rect;
}

std::string Sprite::GetName()
{
    return this->name;
}
Texture* Sprite::GetTexture()
{
    return this->texture;
}
Rect* Sprite::GetRect()
{
    return this->rect;
}

void Sprite::SetName(std::string name)
{
    this->name = name;
}
void Sprite::SetTexture(Texture* texture)
{
    this->texture = texture;
}
