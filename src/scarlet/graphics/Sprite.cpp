#include "scarlet/graphics/Sprite.hpp"
#include "scarlet/graphics/Texture.hpp"
using namespace scarlet;

Sprite::Sprite(std::string name, Texture* texture)
{
    this->name = name;
    this->texture = texture;
    this->rect = Rect(-32.0f, 32.0f, 64.0f, 64.0f);
    this->uv.push_back(Vector2(0.0f, 0.0f));
    this->uv.push_back(Vector2(1.0f, 0.0f));
    this->uv.push_back(Vector2(1.0f, 1.0f));
    this->uv.push_back(Vector2(0.0f, 1.0f));
}
Sprite::Sprite(std::string name, Texture* texture, std::vector<Vector2> uv)
{
    this->name = name;
    this->texture = texture;
    this->rect = Rect(-32.0f, 32.0f, 64.0f, 64.0f);
    this->uv = uv;
}
Sprite::~Sprite()
{
    this->uv.clear();
}

std::string Sprite::GetName()
{
    return this->name;
}
Texture* Sprite::GetTexture()
{
    return this->texture;
}
Rect Sprite::GetRect()
{
    return this->rect;
}
std::vector<Vector2> Sprite::GetUV()
{
    return this->uv;
}

void Sprite::SetName(std::string name)
{
    this->name = name;
}
void Sprite::SetTexture(Texture* texture)
{
    this->texture = texture;
}
void Sprite::SetRect(Rect rect)
{
    this->rect = rect;
}
void Sprite::SetUV(std::vector<Vector2> uv)
{
    this->uv = uv;
}