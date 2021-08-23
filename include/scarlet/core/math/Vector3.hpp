#ifndef VECTOR3_HPP
#define VECTOR3_HPP

#include <iostream>
#include <string>
#include <math.h>

#include "Vector2.hpp"

namespace scarlet
{
    class Vector3
    {
    public:
        float x, y, z;

    public:
        Vector3() 
            : x(0.0f), y(0.0f), z(0.0f) {}
        Vector3(float x, float y, float z) 
            : x(x), y(y), z(z) {}

    public:
        static Vector3 UP()
        {
            return Vector3(0.0f, 1.0f, 0.0f);
        }
        static Vector3 DOWN()
        {
            return Vector3(0.0f, -1.0f, 0.0f);
        }
        static Vector3 RIGHT()
        {
            return Vector3(1.0f, 0.0f, 0.0f);
        }   
        static Vector3 LEFT()
        {
            return Vector3(-1.0f, 0.0f, 0.0f);
        }
        static Vector3 FRONT()
        {
            return Vector3(0.0f, 0.0f, -1.0f);
        }

    public:
        Vector3 operator +(Vector3 v)
        {
            return Vector3(this->x + v.x, this->y + v.y, this->z + v.z);
        }
        Vector3 operator -(Vector3 v)
        {
            return Vector3(this->x - v.x, this->y - v.y, this->z - v.z);
        }
        Vector3 operator -()
        {
            return Vector3(-this->x, -this->y, -this->z);
        }
        Vector3 operator *(float value)
        {
            return Vector3(this->x * value, this->y * value, this->z * value);
        }
        bool operator ==(Vector3 v)
        {
            return this->x == v.x && this->y == v.y && this->z == v.z;
        }
        bool operator !=(Vector3 v)
        {
            return this->x != v.x && this->y != v.y && this->z != v.z;
        }
        operator Vector2()
        {
            return Vector2(this->x, this->y);
        }

    public:
        static float Magnitude(Vector3 v)
        {
            return sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
        }
        static Vector3 Normalize(Vector3 v)
        {
            return Vector3(v.x / Magnitude(v), v.y / Magnitude(v), v.z / Magnitude(v));
        }
        static float Dot(Vector3 v1, Vector3 v2)
        {
            return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
        }
        static Vector3 Cross(Vector3 v1, Vector3 v2)
        {
            return Vector3((v1.y * v2.z) - (v1.z * v2.y), (v1.z * v2.x) - (v1.x * v2.z), (v1.x * v2.y) - (v1.y * v2.x));
        }
        static float Distance(Vector3 v1, Vector3 v2)
        {
            float diffX = v1.x - v2.x;
            float diffY = v1.y - v2.y;
            float diffZ = v1.z - v2.z;

            return Magnitude(Vector3(diffX, diffY, diffZ));
        }
        static float Angle(Vector3 v1, Vector3 v2)
        {
            return acos((Dot(v1, v2) / (Magnitude(v1) * Magnitude(v2))));
        }
        static Vector3 Lerp(Vector3 start, Vector3 end, float t)
        {
            return start + ((end - start) * t);
        }

    public:
        std::string ToString()
        {
            return "x: " + std::to_string(this->x) + " " + "y: " + std::to_string(this->y) + " " + "z:" + std::to_string(this->z);
        }
    };
}

#endif