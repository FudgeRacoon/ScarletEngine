#ifndef VECTOR4_HPP
#define VECTOR4_HPP

#include "scarlet/math/Vector3.hpp"

class Vector4
{
public:
    float x, y, z, w;

public:
    Vector4() : x(0.0f), y(0.0f), z(0.0f), w(1.0f) {}
    Vector4(float x, float y, float z) : x(x), y(y), z(z), w(1.0f){}
    Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w){}
    Vector4(Vector3 v) : x(v.x), y(v.y), z(v.z), w(1.0f){}

public:
    operator Vector3()
    {
        return Vector3(this->x, this->y, this->z);
    }
};

#endif