#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "scarlet/common/Types.hpp"

#include "scarlet/debug/Assert.hpp"

#include "scarlet/graphics/GraphicsContext.hpp"
#include "scarlet/graphics/VertexBuffer.hpp"
#include "scarlet/graphics/VertexArray.hpp"
#include "scarlet/graphics/IndexBuffer.hpp"
#include "scarlet/graphics/Shader.hpp"
#include "scarlet/graphics/Texture.hpp"
#include "scarlet/graphics/camera/Camera.hpp"

#include "scarlet/system/AssetPool.hpp"

#include "scarlet/math/Color.hpp"
#include "scarlet/math/Vector3.hpp"
#include "scarlet/math/Vector4.hpp"
#include "scarlet/math/Matrix4.hpp"

#include "scarlet/primitives/Line.hpp"
#include "scarlet/primitives/Rect.hpp"

namespace scarlet
{   
    struct RendererVertexData
    {
        Vector3 position;      
        Vector4 color;         
        Vector2 textureCoords; 
        float   textureIndex;  
        float   instanceID;    
    };

    struct RendererData
    {
        const uint32           MAX_LINES = 10000;
        const size_t           LINE_VERTICES_SIZE = 11 * 2 * sizeof(float);
        const size_t           MAX_LINE_VERTICES_SIZE = MAX_LINES * LINE_VERTICES_SIZE;

        const uint32           MAX_QUADS = 10000;
        const size_t           QUAD_VERTICES_SIZE = 11 * 4 * sizeof(float);
        const size_t           QUAD_INDICIES_SIZE = 6 * sizeof(uint32);
        const size_t           MAX_QUAD_VERTICES_SIZE = MAX_QUADS * QUAD_VERTICES_SIZE;
        const size_t           MAX_QUAD_INDICIES_SIZE = MAX_QUADS * QUAD_INDICIES_SIZE;
        
        VertexBuffer*          lineVertexBuffer = nullptr;
        VertexArray*           lineVertexArray = nullptr;

        VertexBuffer*          quadVertexBuffer = nullptr;
        IndexBuffer*           quadIndexBuffer = nullptr;
        VertexArray*           quadVertexArray = nullptr;
        
        Texture*               whiteTexture = nullptr;
        Texture**              textureSlots = nullptr;

        Shader*                currentShader = nullptr;
        Camera*                rendererCamera = nullptr;

        uint32                 lineCount = 0;
        uint32                 quadCount = 0;
        uint32                 currentTextureIndex = 1;            

        RendererVertexData*    lineVertexPtr = nullptr;
        RendererVertexData*    lineVertexBase = nullptr;

        RendererVertexData*    quadVertexPtr = nullptr;
        RendererVertexData*    quadVertexBase = nullptr;
    };

    class Renderer
    {
    private:
        static RendererData rendererData;

    public:
        Renderer() = delete;

    private:
        static void StartBatch();
        static void NextBatch();
        static void Flush();

    private:
        static void InitBuffers();
        static void InitTextureSlots();
        static void InitShaders();

    public:
        static void OnInit();
        static void OnShutDown();

    public:
        static void BeginScene(Camera* camera);
        static void EndScene();

    public:
        static Shader* GetBoundShader();
        static void BindShader(Shader* shader);

    public:
        static void DrawLine(Line line, Color color);
        static void DrawLine(Vector3 start, Vector3 end, Color color);
        static void DrawLine(float x0, float y0, float x1, float y1, Color color);

    public:
        static void DrawQuad(Rect rect, Color color);
        static void DrawQuad(Vector3 position, Vector3 size, Color color);
        static void DrawQuad(float x, float y, float width, float height, Color color);

    public:
        static void DrawFilledQuad(Rect rect, Color color);
        static void DrawFilledQuad(Vector3 position, Vector3 size, Color color);
        static void DrawFilledQuad(float x, float y, float width, float height, Color color);

    public:
        static void DrawRotatedQuad(Rect rect, float radians, Color color);
        static void DrawRotatedQuad(Vector3 position, Vector3 size, float radians, Color color);
        static void DrawRotatedQuad(float x, float y, float width, float height, float radians, Color color);

    public:
        static void DrawSprite(Sprite* sprite, Matrix4 model, uint32 id, Color color);
    };
}

#endif