#include "scarlet/graphics/DebugRenderer.hpp"
#include "scarlet/common/Assert.hpp"
using namespace scarlet;

DebugRendererData DebugRenderer::debugRendererData;

void DebugRenderer::Init()
{
    #pragma region Line Buffer Init
    debugRendererData.lineVertexBuffer = new VertexBuffer(
        nullptr, 
        debugRendererData.MAX_LINE_VERTICES * sizeof(float),
        GL_DYNAMIC_DRAW  
    );
    debugRendererData.lineVertexBuffer->AddLayout<float>(3, false);
    debugRendererData.lineVertexBuffer->AddLayout<float>(4, false);
    debugRendererData.lineVertexArray = new VertexArray();
    debugRendererData.lineVertexArray->AddBuffer(debugRendererData.lineVertexBuffer);

    debugRendererData.lineVertexBase = new Vertex[debugRendererData.MAX_LINES * 2];
    debugRendererData.lineVertexPtr = debugRendererData.lineVertexBase;
    #pragma endregion

    #pragma region Quad Buffer Init
    debugRendererData.quadVertexBuffer = new VertexBuffer(
        nullptr, 
        debugRendererData.MAX_QUAD_VERTICES * sizeof(float),
        GL_DYNAMIC_DRAW  
    );
    debugRendererData.quadVertexBuffer->AddLayout<float>(3, false);
    debugRendererData.quadVertexBuffer->AddLayout<float>(4, false);
    debugRendererData.quadVertexArray = new VertexArray();
    debugRendererData.quadVertexArray->AddBuffer(debugRendererData.quadVertexBuffer);

    int offset = 0;
    uint32* quadIndices = new uint32[debugRendererData.MAX_QUADS * 6];
    for(int i = 0; i < debugRendererData.MAX_QUADS * 6; i += 6)
    {
        quadIndices[i + 0] = 0 + offset; 
        quadIndices[i + 1] = 1 + offset;
        quadIndices[i + 2] = 2 + offset;
        quadIndices[i + 3] = 2 + offset;
        quadIndices[i + 4] = 3 + offset;
        quadIndices[i + 5] = 0 + offset;

        offset += 4;
    }

    debugRendererData.quadIndexBuffer = new IndexBuffer(
        quadIndices, 
        debugRendererData.MAX_QUADS * 6 * sizeof(float),
        GL_STATIC_DRAW
    );

    delete[] quadIndices;

    debugRendererData.quadVertexBase = new Vertex[debugRendererData.MAX_QUADS * 4];
    debugRendererData.quadVertexPtr = debugRendererData.quadVertexBase;
    #pragma endregion

    debugRendererData.defaultShader = new Shader(
        "assets\\shaders\\flatColorVertex.shader",
        "assets\\shaders\\flatColorFragment.shader"
    );
}
void DebugRenderer::ShutDown()
{
    delete debugRendererData.lineIndexBuffer;
    delete debugRendererData.lineVertexBuffer;
    delete debugRendererData.lineVertexArray;

    delete[] debugRendererData.lineVertexBase;

    delete debugRendererData.quadIndexBuffer;
    delete debugRendererData.quadVertexBuffer;
    delete debugRendererData.quadVertexArray;

    delete[] debugRendererData.quadVertexBase;
    
    delete debugRendererData.defaultShader;
    delete debugRendererData.debugRendererCamera;
}

void DebugRenderer::StartBatch()
{
    debugRendererData.lineCount = 0;
    debugRendererData.quadCount = 0;
    debugRendererData.lineVertexPtr = debugRendererData.lineVertexBase;
    debugRendererData.quadVertexPtr = debugRendererData.quadVertexBase;
}
void DebugRenderer::NextBatch()
{
    Flush();
    StartBatch();
}
void DebugRenderer::Flush()
{
    debugRendererData.lineVertexBuffer->UpdateBufferData(
        0, 
        debugRendererData.lineCount * debugRendererData.LINE_VERTICES * sizeof(float),
        debugRendererData.lineVertexBase
    );

    debugRendererData.quadVertexBuffer->UpdateBufferData(
        0,
        debugRendererData.quadCount * debugRendererData.QUAD_VERTICES * sizeof(float),
        debugRendererData.quadVertexBase
    );

    debugRendererData.defaultShader->Bind();
    debugRendererData.defaultShader->SetMat4(
        "uView", debugRendererData.debugRendererCamera->GetViewMatrix()
    );
    debugRendererData.defaultShader->SetMat4(
        "uProj", debugRendererData.debugRendererCamera->GetProjectionMatrix()
    );

    debugRendererData.lineVertexArray->Bind();
    GLCALL(glDrawArrays(GL_LINES, 0, debugRendererData.lineCount * 2));
    debugRendererData.lineVertexArray->UnBind();

    debugRendererData.quadVertexArray->Bind();
    debugRendererData.quadIndexBuffer->Bind();
    GLCALL(glDrawElements(GL_TRIANGLES, debugRendererData.quadCount * 6, GL_UNSIGNED_INT, 0));
    debugRendererData.quadIndexBuffer->UnBind();
    debugRendererData.quadVertexArray->UnBind();

    debugRendererData.defaultShader->UnBind();
}

void DebugRenderer::BeginScene(Camera* camera)
{
    debugRendererData.debugRendererCamera = camera;

    StartBatch();
}
void DebugRenderer::EndScene()
{
    Flush();

    debugRendererData.debugRendererCamera = nullptr;
}

void DebugRenderer::DrawLine(Line line, Color color)
{
    if(debugRendererData.lineCount >= debugRendererData.MAX_LINES)
        NextBatch();
    
    for(int i = 0; i < 2; i++)
    {
        debugRendererData.lineVertexPtr->position = i == 0 ? line.start : line.end;
        debugRendererData.lineVertexPtr->color = color;
        debugRendererData.lineVertexPtr++;
    }

    debugRendererData.lineCount++;
}
void DebugRenderer::DrawLine(Vector3 start, Vector3 end, Color color)
{
    DrawLine(Line(start, end), color);
}
void DebugRenderer::DrawLine(float x0, float y0, float x1, float y1, Color color)
{
    DrawLine(Line(x0, y0, x1, y1), color);
}

void DebugRenderer::DrawRect(Rect rect, Color color)
{
    if(debugRendererData.quadCount >= debugRendererData.MAX_QUADS)
        NextBatch();

    Vector3 position;

    for(int i = 0; i < 4; i++)
    {
        switch (i)
        {
            case 0: position = Vector3(
                rect.GetX(), 
                rect.GetY(), 
                0.0f
            ); break;

            case 1: position = Vector3(
                rect.GetX(), 
                rect.GetY() - rect.GetHeight(), 
                0.0f
            ); break;

            case 2: position = Vector3(
                rect.GetX() + rect.GetWidth(), 
                rect.GetY() - rect.GetHeight(), 
                0.0f
            ); break;

            case 3: position = Vector3(
                rect.GetX() + rect.GetWidth(), 
                rect.GetY(), 
                0.0f
            ); break;
        }

        debugRendererData.quadVertexPtr->position = position;
        debugRendererData.quadVertexPtr->color = color;
        debugRendererData.quadVertexPtr++;
    }

    debugRendererData.quadCount++;
}
void DebugRenderer::DrawRect(Vector3 position, Vector3 size, Color color)
{
    DrawRect(Rect(position, size), color);
}
void DebugRenderer::DrawRect(float x, float y, float width, float height, Color color)
{
    DrawRect(Rect(x, y, width, height), color);
}
