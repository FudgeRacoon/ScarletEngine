#include "core/Sprite.hpp"
using namespace scarlet;

Sprite::Sprite()
{
    this->rect = new Rect(-16.0f, 16.0f, 32.0f, 32.0f);
}
Sprite::Sprite(Texture* texture, Rect* rect)
{
    this->texture = texture;
    this->rect = rect;
}
Sprite::~Sprite()
{
    delete this->texture;
    delete this->rect;
}

void Sprite::SetTexture(Texture* texture)
{
    this->texture = texture;
}
Texture* Sprite::GetTexture()
{
    return this->texture;
}

Rect* Sprite::GetRect()
{
    return this->rect;
}
