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
#include "scarlet/math/Vector4.hpp"

#include "scarlet/primitives/Line.hpp"
#include "scarlet/primitives/Rect.hpp"

namespace scarlet
{   
    struct Vertex
    {
        Vector3 position; 
        Vector4 color;    
    };

    struct DebugRendererData
    {
        const uint32        MAX_LINES = 10000;
        const uint32        MAX_QUADS = 10000;
        const uint32        LINE_VERTICES = 7 * 2;
        const uint32        QUAD_VERTICES = 7 * 4;
        const uint32        MAX_LINE_VERTICES = MAX_LINES * LINE_VERTICES;
        const uint32        MAX_QUAD_VERTICES = MAX_QUADS * QUAD_VERTICES;

        uint32              lineCount;
        uint32              quadCount;

        IndexBuffer*        lineIndexBuffer = nullptr;
        VertexBuffer*       lineVertexBuffer = nullptr;
        VertexArray*        lineVertexArray = nullptr;

        Vertex*             lineVertexPtr = nullptr;
        Vertex*             lineVertexBase = nullptr;

        IndexBuffer*        quadIndexBuffer = nullptr;
        VertexBuffer*       quadVertexBuffer = nullptr;
        VertexArray*        quadVertexArray = nullptr;

        Vertex*             quadVertexPtr = nullptr;
        Vertex*             quadVertexBase = nullptr;

        Shader*             defaultShader = nullptr;
        Camera*             debugRendererCamera = nullptr;
    };

    class DebugRenderer
    {
    private:
        static DebugRendererData debugRendererData;

    public:
        static void Init();
        static void ShutDown();

    private:
        static void StartBatch();
        static void NextBatch();
        static void Flush();

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
    };
}

#endif