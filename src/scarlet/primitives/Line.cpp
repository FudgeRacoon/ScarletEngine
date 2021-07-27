#include "scarlet/primitives/Line.hpp"
using namespace scarlet;

Line::Line()
{
    this->start = Vector3();
    this->end = Vector3();
}
Line::Line(Vector3 start, Vector3 end)
{
    this->start = start;
    this->end = end;
}
Line::Line(float x0, float y0, float x1, float y1)
{
    this->start = Vector3(x0, y0, 0.0f);
    this->end = Vector3(x1, y1, 0.0f);
}