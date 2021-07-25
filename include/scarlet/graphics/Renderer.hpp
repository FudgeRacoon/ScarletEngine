#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <vector>

#include "GL/glew.h"

#include "scarlet/core/Window.hpp"

#include "scarlet/entity/GameObject.hpp"
#include "scarlet/entity/Transform.hpp"
#include "scarlet/entity/SpriteRenderer.hpp"

#include "scarlet/graphics/VertexBuffer.hpp"
#include "scarlet/graphics/VertexArray.hpp"
#include "scarlet/graphics/IndexBuffer.hpp"
#include "scarlet/graphics/Shader.hpp"
#include "scarlet/graphics/Texture.hpp"
#include "scarlet/graphics/camera/Camera.hpp"

#include "scarlet/math/Color.hpp"
#include "scarlet/math/Vector3.hpp"
#include "scarlet/math/Vector4.hpp"
#include "scarlet/math/Matrix4.hpp"

#include "scarlet/primitives/Line.hpp"
#include "scarlet/primitives/Rect.hpp"

namespace scarlet
{
    enum RendererBufferType
    {
        RENDERER_BUFFER_DEPTH = 0x00000100,
        RENDERER_BUFFER_STENCIL = 0x00000400,
        RENDERER_BUFFER_COLOR = 0x00004000
    };

    enum RendererBlendFunc
    {
        RENDERER_SRC_ALPHA = 0x0302,
        RENDERER_ONE_MINUS_SRC_ALPHA = 0x0303,
    };

    struct RendererData
    {
        Shader* defualtShader;
        Camera* rendererCamera;

        Color   clearColor;
        Vector4 viewport;

        RendererData() :  defualtShader(nullptr), 
            rendererCamera(nullptr) {}
    };

    class Renderer
    {
    private:
        static RendererData rendererData;

    public:
        Renderer() = delete;

    public:
        static void Init();

    public:
        static Vector4 GetViewport();

    public:
        static void SetViewport(uint32 x, uint32 y, uint32 width, uint32 height);
        static void SetBlendingFunction(uint32 sFactor, uint32 dFactor);
        static void SetClearColor(Color color);
    
    public:
        static void EnableBlending(bool enable);

    public:
        static void ClearBuffers(uint32 buffers);
        static void SwapBuffers();

    public:
        static void BeginScene(Camera* camera);
        static void EndScene();

    public:
        static void DrawRect(Rect* rect, Color color, const Shader* shader = nullptr);
        static void DrawEntity(GameObject* gameObject);
    };
}

#endif