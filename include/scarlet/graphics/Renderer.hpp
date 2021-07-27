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
    struct RendererData
    {
        Shader* defualtShader;
        Camera* rendererCamera;
        
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
        static void ShutDown();

    public:
        static void StartBatch();
        static void NextBatch();
        static void Flush();

    public:
        static void BeginScene(Camera* camera);
        static void EndScene();

    public:
        static void DrawEntity(GameObject* gameObject);
    };
}

#endif