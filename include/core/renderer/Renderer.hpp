#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "GL/glew.h"

#include "core/Window.hpp"
#include "core/Camera.hpp"
#include "core/renderer/VertexArray.hpp"
#include "core/renderer/IndexBuffer.hpp"
#include "core/renderer/Shader.hpp"
#include "core/math/Vector3.hpp"
#include "core/math/Matrix4.hpp"

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
        void Render(Camera& camera, const VertexArray*& va, const IndexBuffer* ib, const Shader*& shader);
    };
}

#endif