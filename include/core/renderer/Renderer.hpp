#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "GL/glew.h"

#include "core/Window.hpp"
#include "core/Camera.hpp"
#include "core/GameObject.hpp"

#include "core/components/Transform.hpp"
#include "core/components/SpriteRenderer.hpp"

#include "core/renderer/VertexArray.hpp"
#include "core/renderer/IndexBuffer.hpp"
#include "core/renderer/Shader.hpp"
#include "core/renderer/Texture.hpp"

#include "core/math/Vector3.hpp"
#include "core/math/Matrix4.hpp"

#include "core/primitives/Rect.hpp"

namespace scarlet
{
    class Renderer
    {
    private:
        Renderer() = default;
        Renderer(const Renderer& renderer) = delete;

    public:
        static Renderer* Get();

    public:
        void ClearBuffers();
        void SwapBuffers();

    public:
        void Render(Camera*& camera, Shader*& shader, int x1, int y1, int x2, int y2, float width);
        void Render(Camera*& camera, Shader*& shader, Rect* rect); 
        void Render(Camera*& camera, Shader*& shader, GameObject* gameObject);
    };
}

#endif