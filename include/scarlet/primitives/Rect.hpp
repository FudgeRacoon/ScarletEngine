#ifndef RECT_HPP
#define RECT_HPP

#include <vector>

#include "scarlet/math/Math.hpp"
#include "scarlet/math/Vector2.hpp"

#include "scarlet/graphics/VertexArray.hpp"
#include "scarlet/graphics/VertexBuffer.hpp"
#include "scarlet/graphics/IndexBuffer.hpp"
#include "scarlet/graphics/VertexBufferLayout.hpp"

namespace scarlet
{
    class Rect
    {
    private:
        VertexArray* vao = nullptr;
        VertexBuffer* vbo = nullptr;
        IndexBuffer* ibo = nullptr;

    private:
        real* dataBuffer = nullptr;
        uint32* indicesBuffer = nullptr;

    private:
        real x, y;
        real width, height;
        real xMax, yMax;

    public:
        Rect(real x, real y, real width, real height);
        ~Rect();

    public:
        void SetX(real x);
        void SetY(real y);
        void SetWidth(real width);
        void SetHeight(real height);
        void SetUV(Vector2 v1, Vector2 v2, Vector2 v3, Vector2 v4);

        real GetX();
        real GetY();
        real GetWidth();
        real GetHeight();
        std::vector<Vector2> GetUV();
        Vector2 GetCenter();

    public:
        bool Contains(Vector2 point);

    public:
        void Bind();
        void UnBind();
    };
}

#endif