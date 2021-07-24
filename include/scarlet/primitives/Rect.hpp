#ifndef RECT_HPP
#define RECT_HPP

#include <vector>

#include "scarlet/common/Types.hpp"

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
        float* dataBuffer = nullptr;
        uint32* indicesBuffer = nullptr;

    private:
        float x, y;
        float width, height;
        float xMax, yMax;

    public:
        Rect(float x, float y, float width, float height);
        ~Rect();

    public:
        void SetX(float x);
        void SetY(float y);
        void SetWidth(float width);
        void SetHeight(float height);
        void SetUV(Vector2 v1, Vector2 v2, Vector2 v3, Vector2 v4);

        float GetX();
        float GetY();
        float GetWidth();
        float GetHeight();
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