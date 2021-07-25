#ifndef DEBUGRENDERER_HPP
#define DEBUGRENDERER_HPP

#include <vector>

#include "../../containers/SPair.hpp"

#include "scarlet/graphics/VertexBuffer.hpp"
#include "scarlet/graphics/VertexArray.hpp"
#include "scarlet/graphics/IndexBuffer.hpp"
#include "scarlet/graphics/Shader.hpp"
#include "scarlet/graphics/camera/Camera.hpp"

#include "scarlet/math/Color.hpp"
#include "scarlet/math/Vector3.hpp"

#include "scarlet/primitives/Line.hpp"
#include "scarlet/primitives/Rect.hpp"

namespace scarlet
{   
    struct DebugRendererData
    {
        Shader* defaultShader;
        Camera* rendererCamera;

        DebugRendererData() : defaultShader(nullptr), 
            rendererCamera(nullptr) {}
    };

    struct VerticesData
    {
        VertexBuffer*  vbo;
        IndexBuffer*   ibo;
        VertexArray*   vao;
        
        VerticesData() : vbo(nullptr), 
            ibo(nullptr), vao(nullptr){}
    };

    class DebugRenderer
    {
    private:
        static DebugRendererData debugRendererData;

    private:
        static VerticesData lineData;
        static VerticesData rectData;

    private:
        static const uint32 MAX_LINES = 1000;
        static const uint32 MAX_RECTS = 1000;
        static const uint32 LINE_VERTICES = 7 * 2;
        static const uint32 RECT_VERTICES = 7 * 4;
        static const uint32 MAX_LINE_VERTICES = MAX_LINES * LINE_VERTICES;
        static const uint32 MAX_RECT_VERTICES = MAX_RECTS * RECT_VERTICES;

    private:
        static float* vertexBuffer;
        static uint32* indexBuffer;

    private:
        static std::vector<SPair<Line, Color>> lines;
        static std::vector<SPair<Rect, Color>> rects;

    public:
        static void Init();

    public:
        static void BeginScene(Camera* camera);
        static void EndScene();

    public:
        static void DrawLine(Line line, Color color);
        static void DrawLine(Vector3 start, Vector3 end, Color color);
        static void DrawLine(float x0, float y0, float x1, float y1, Color color);
        
    public:
        static void DrawRect(Rect rect, Color color);
        static void DrawRect(Vector3 position, Vector3 size, Color color);
        static void DrawRect(float x, float y, float width, float height, Color color);

    private:
        static void INTERNAL_PrepareLineBatch();
        static void INTERNAL_PrepareRectBatch();

    public:
        static void RenderBatch();
        static void Flush();
    };
}

#endif