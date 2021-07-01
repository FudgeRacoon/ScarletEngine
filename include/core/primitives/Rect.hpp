#ifndef RECT_HPP
#define RECT_HPP

#include "core/math/Math.hpp"
#include "core/math/Vector2.hpp"
#include "core/renderer/VertexArray.hpp"
#include "core/renderer/VertexBuffer.hpp"
#include "core/renderer/IndexBuffer.hpp"
#include "core/renderer/VertexBufferLayout.hpp"

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
        Vector2 GetCenter();

    public:
        bool Contains(Vector2 point);

    public:
        void EnableBuffers();
        void DisbaleBuffers();
    };
}

#endif