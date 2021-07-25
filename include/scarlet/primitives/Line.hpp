#ifndef LINE_HPP
#define LINE_HPP

#include "scarlet/math/Vector3.hpp"

namespace scarlet
{
    class Line
    {
    public:
        Vector3 start;
        Vector3 end;

    public:
        Line();
        Line(Vector3 start, Vector3 end);
        Line(float x0, float y0, float x1, float x2);
    };
}

#endif