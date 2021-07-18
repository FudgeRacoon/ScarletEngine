#ifndef VECTOR2_HPP
#define VECTOR2_HPP

#include <iostream>
#include <string>
#include <math.h>

class Vector2
{
public:
    float x, y;

public:
    Vector2() : x(0.0f), y(0.0f) {}
    Vector2(float x, float y) : x(x), y(y) {}

public:
    static Vector2 UP()
    {
        return Vector2(0.0f, 1.0f);
    }
    static Vector2 DOWN()
    {
        return Vector2(0.0f, -1.0f);
    }
    static Vector2 RIGHT()
    {
        return Vector2(1.0f, 0.0f);
    }   
    static Vector2 LEFT()
    {
        return Vector2(-1.0f, 0.0f);
    }

public:
    Vector2 operator +(Vector2 v)
    {
        return Vector2(this->x + v.x, this->y + v.y);
    }
    Vector2 operator -(Vector2 v)
    {
        return Vector2(this->x - v.x, this->y - v.y);
    }
    Vector2 operator -()
    {
        return Vector2(-this->x, -this->y);
    }
    Vector2 operator *(float value)
    {
        return Vector2(this->x * value, this->y * value);
    }
    bool operator ==(Vector2 v)
    {
        return this->x == v.x && this->y == v.y;
    }
    bool operator !=(Vector2 v)
    {
        return this->x != v.x && this->y != v.y;
    }
    
public:
    static float Magnitude(Vector2 v)
    {
        return sqrt((v.x * v.x) + (v.y * v.y));
    }
    static Vector2 Normalize(Vector2 v)
    {
        return Vector2(v.x / Magnitude(v), v.y / Magnitude(v));
    }
    static float Dot(Vector2 v1, Vector2 v2)
    {
        return (v1.x * v2.x) + (v1.y * v2.y);
    }
    static float Distance(Vector2 v1, Vector2 v2)
    {
        float diffX = v1.x - v2.x;
        float diffY = v1.y - v2.y;

        return Magnitude(Vector2(diffX, diffY));
    }
    static float Angle(Vector2 v1, Vector2 v2)
    {
        return acos((Dot(v1, v2) / (Magnitude(v1) * Magnitude(v2))));
    }
    static Vector2 Lerp(Vector2 start, Vector2 end, float t)
    {
        return start + ((end - start) * t);
    }

public:
    std::string ToString()
    {
        return "x: " + std::to_string(this->x) + " " + "y: " + std::to_string(this->y);
    }
};

#endif