#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "GL/glew.h"

#include "scarlet/core/Window.hpp"

#include "scarlet/entity/GameObject.hpp"
#include "scarlet/entity/Transform.hpp"
#include "scarlet/entity/SpriteRenderer.hpp"

#include "scarlet/graphics/VertexArray.hpp"
#include "scarlet/graphics/IndexBuffer.hpp"
#include "scarlet/graphics/Shader.hpp"
#include "scarlet/graphics/Texture.hpp"
#include "scarlet/graphics/camera/Camera.hpp"

#include "scarlet/math/Vector3.hpp"
#include "scarlet/math/Matrix4.hpp"

#include "scarlet/primitives/Rect.hpp"

namespace scarlet
{
    class Renderer
    {
    public:
        Renderer() = delete;

    public:
        static void ClearBuffers();
        static void SwapBuffers();

    public:
        static void Render(Camera*& camera, Shader*& shader, int x1, int y1, int x2, int y2, float width);
        static void Render(Camera*& camera, Shader*& shader, Rect* rect); 
        static void Render(Camera*& camera, Shader*& shader, GameObject* gameObject);
    };
}

#endif