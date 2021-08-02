#ifndef RECT_HPP
#define RECT_HPP

#include <vector>

#include "scarlet/common/Types.hpp"

#include "scarlet/math/Math.hpp"
#include "scarlet/math/Vector2.hpp"
#include "scarlet/math/Vector3.hpp"

namespace scarlet
{
    class Rect
    {
    private:
        float x, y;
        float width, height;
        float xMax, yMax;

    public:
        Rect();
        Rect(Vector3 position, Vector3 size);
        Rect(float x, float y, float width, float height);

    public:
        float GetX();
        float GetY();
        float GetWidth();
        float GetHeight();
        Vector2 GetCenter();
    
    public:
        void SetX(float x);
        void SetY(float y);
        void SetWidth(float width);
        void SetHeight(float height);
    
    public:
        bool Contains(Vector2 point);
        bool OverLaps(Rect rect);
    };
}

#endif