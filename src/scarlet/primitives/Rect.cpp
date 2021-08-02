#include "scarlet/primitives/Rect.hpp"
using namespace scarlet;

Rect::Rect()
{
    this->x = 0; this->y = 0;
    this->width = 0; this->height = 0;
    this->xMax = this->x + this->width; this->yMax = this->y - this->height;
}
Rect::Rect(Vector3 position, Vector3 size)
{
    this->x = position.x; this->y = position.y;
    this->width = size.x; this->height = size.y;
    this->xMax = this->x + this->width; this->yMax = this->y - this->height;
}
Rect::Rect(float x, float y, float width, float height)
{   
    this->x = x; this->y = y;
    this->width = width; this->height = height;
    this->xMax = this->x + this->width; this->yMax = this->y - this->height;
}

float Rect::GetX()
{
    return this->x;
}
float Rect::GetY()
{
    return this->y;
}
float Rect::GetWidth()
{
    return this->width;
}
float Rect::GetHeight()
{
    return this->height;
}
Vector2 Rect::GetCenter()
{
    return Vector2(this->x + (this->width / 2), this->y + (this->height / 2));
}

void Rect::SetX(float x)
{
    this->x = x;
    this->xMax = this->x + this->width;
}
void Rect::SetY(float y)
{
    this->y = y;
    this->yMax = this->y - this->height;
}
void Rect::SetWidth(float width)
{
    this->width = width;
    this->xMax = this->x + this->width;
}
void Rect::SetHeight(float height)
{
    this->height = height;
    this->yMax = this->y - this->height;
}

bool Rect::Contains(Vector2 point)
{
    if(point.x >= this->x && point.x <= this->xMax &&
       point.y <= this->y && point.y >= this->yMax)
        return true;
    else
        return false;
}