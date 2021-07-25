#include "scarlet/graphics/DebugRenderer.hpp"
#include "scarlet/common/Assert.hpp"
using namespace scarlet;

DebugRendererData DebugRenderer::debugRendererData;

VerticesData DebugRenderer::lineData;
VerticesData DebugRenderer::rectData;

float* DebugRenderer::vertexBuffer = new float[MAX_RECT_VERTICES];
uint32* DebugRenderer::indexBuffer = new uint32[MAX_RECTS * 6];

std::vector<SPair<Line, Color>> DebugRenderer::lines;
std::vector<SPair<Rect, Color>> DebugRenderer::rects;

void DebugRenderer::Init()
{
    lines.reserve(MAX_LINES);
    rects.reserve(MAX_RECTS);

    lineData.vbo = new VertexBuffer(nullptr, MAX_LINE_VERTICES * sizeof(float), GL_DYNAMIC_DRAW);
    lineData.vbo->AddLayout<float>(3, false);
    lineData.vbo->AddLayout<float>(4, false);
    lineData.vao = new VertexArray();
    lineData.vao->AddBuffer(lineData.vbo);
        
    rectData.vbo = new VertexBuffer(nullptr, MAX_RECT_VERTICES * sizeof(float), GL_DYNAMIC_DRAW);
    rectData.vbo->AddLayout<float>(3, false);
    rectData.vbo->AddLayout<float>(4, false);
    rectData.ibo = new IndexBuffer(nullptr, MAX_RECTS * 6 * sizeof(float), GL_DYNAMIC_DRAW);
    rectData.vao = new VertexArray();
    rectData.vao->AddBuffer(rectData.vbo);
    
    debugRendererData.defaultShader = new Shader(
        "assets\\shaders\\flatColorVertex.shader", 
        "assets\\shaders\\flatColorFragment.shader"
    );
}

void DebugRenderer::BeginScene(Camera* camera)
{
    debugRendererData.rendererCamera = camera;
}
void DebugRenderer::EndScene()
{
    debugRendererData.rendererCamera = nullptr;
}

void DebugRenderer::DrawLine(Line line, Color color)
{
    if(lines.size() >= MAX_LINES)
    {
        Logger::LogWarning("Reached max lines that can be rendered.");
        return;
    }

    lines.push_back(SPair<Line, Color>(line, color));
}
void DebugRenderer::DrawLine(Vector3 start, Vector3 end, Color color)
{
    if(lines.size() >= MAX_LINES)
    {
        Logger::LogWarning("Reached max lines that can be rendered.");
        return;
    }
    
    lines.push_back(SPair<Line, Color>(Line(start, end), color));
}
void DebugRenderer::DrawLine(float x0, float y0, float x1, float y1, Color color)
{
    if(lines.size() >= MAX_LINES)
    {
        Logger::LogWarning("Reached max lines that can be rendered.");
        return;
    }

    lines.push_back(SPair<Line, Color>(Line(x0, y0, x1, y1), color));
}

void DebugRenderer::DrawRect(Rect rect, Color color)
{
    if(lines.size() >= MAX_LINES)
    {
        Logger::LogWarning("Reached max rects that can be rendered.");
        return;
    }

    rects.push_back(SPair<Rect, Color>(rect, color));
}
void DebugRenderer::DrawRect(Vector3 position, Vector3 size, Color color)
{
    if(lines.size() >= MAX_LINES)
    {
        Logger::LogWarning("Reached max rects that can be rendered.");
        return;
    }

    rects.push_back(SPair<Rect, Color>(Rect(position, size), color));
}
void DebugRenderer::DrawRect(float x, float y, float width, float height, Color color)
{
    if(lines.size() >= MAX_LINES)
    {
        Logger::LogWarning("Reached max rects that can be rendered.");
        return;
    }

    rects.push_back(SPair<Rect, Color>(Rect(x, y, width, height), color));
}

void DebugRenderer::INTERNAL_PrepareLineBatch()
{
    if(lines.size() <= 0 || lines.size() >= MAX_LINES)
        return;
    
    int vertexBufferIndexOffset = 0;

    for(SPair<Line, Color> line : lines)
    {
        for(int i = 0; i < 2; i++)
        {
            Vector3 position = i == 0 ? line.first.start : line.first.end;

            vertexBuffer[vertexBufferIndexOffset + 0] = position.x;
            vertexBuffer[vertexBufferIndexOffset + 1] = position.y;
            vertexBuffer[vertexBufferIndexOffset + 2] = 0.0f;

            vertexBuffer[vertexBufferIndexOffset + 3] = (float)(line.second.r / 255.0f);
            vertexBuffer[vertexBufferIndexOffset + 4] = (float)(line.second.g / 255.0f);
            vertexBuffer[vertexBufferIndexOffset + 5] = (float)(line.second.b / 255.0f);
            vertexBuffer[vertexBufferIndexOffset + 6] = (float)(line.second.a / 255.0f);

            vertexBufferIndexOffset += 7;
        }
    }

    lineData.vbo->UpdateBufferData(0, lines.size() * LINE_VERTICES * sizeof(float), vertexBuffer);
}
void DebugRenderer::INTERNAL_PrepareRectBatch()
{
    if(rects.size() <= 0 || lines.size() >= MAX_RECTS)
        return;

    int indexBufferValueOffset = 0;
    int vertexBufferIndexOffset = 0, indexBufferIndexOffset = 0;

    for(SPair<Rect, Color> rect : rects)
    {
        for(int i = 0; i < 4; i++)
        {
            Vector3 position;

            switch(i)
            {
                case 0: position = Vector3(rect.first.GetX(), rect.first.GetY(), 0.0f); break;
                case 1: position = Vector3(rect.first.GetX(), rect.first.GetY() - rect.first.GetHeight(), 0.0f); break;
                case 2: position = Vector3(rect.first.GetX() + rect.first.GetWidth(), rect.first.GetY() - rect.first.GetHeight(), 0.0f); break;
                case 3: position = Vector3(rect.first.GetX() + rect.first.GetWidth(), rect.first.GetY(), 0.0f); break;
            }

            vertexBuffer[vertexBufferIndexOffset + 0] = position.x;
            vertexBuffer[vertexBufferIndexOffset + 1] = position.y;
            vertexBuffer[vertexBufferIndexOffset + 2] = 0.0f;

            vertexBuffer[vertexBufferIndexOffset + 3] = (float)(rect.second.r / 255.0f);
            vertexBuffer[vertexBufferIndexOffset + 4] = (float)(rect.second.g / 255.0f);
            vertexBuffer[vertexBufferIndexOffset + 5] = (float)(rect.second.b / 255.0f);
            vertexBuffer[vertexBufferIndexOffset + 6] = (float)(rect.second.a / 255.0f);

            vertexBufferIndexOffset += 7;
        }

        indexBuffer[indexBufferIndexOffset + 0] = 0 + indexBufferValueOffset;
        indexBuffer[indexBufferIndexOffset + 1] = 1 + indexBufferValueOffset;
        indexBuffer[indexBufferIndexOffset + 2] = 2 + indexBufferValueOffset;
        indexBuffer[indexBufferIndexOffset + 3] = 2 + indexBufferValueOffset;
        indexBuffer[indexBufferIndexOffset + 4] = 3 + indexBufferValueOffset;
        indexBuffer[indexBufferIndexOffset + 5] = 0 + indexBufferValueOffset;

        indexBufferValueOffset += 4;
        indexBufferIndexOffset += 6;
    }

    rectData.vbo->UpdateBufferData(0, rects.size() * RECT_VERTICES * sizeof(float), vertexBuffer);
    rectData.ibo->UpdateBufferData(0, rects.size() * 6 * sizeof(float), indexBuffer);
}

void DebugRenderer::RenderBatch()
{
    INTERNAL_PrepareLineBatch();
    INTERNAL_PrepareRectBatch();
    
    debugRendererData.defaultShader->Bind();
    
    debugRendererData.defaultShader->SetMat4("uView", debugRendererData.rendererCamera->GetViewMatrix());
    debugRendererData.defaultShader->SetMat4("uProj", debugRendererData.rendererCamera->GetProjectionMatrix());

    lineData.vao->Bind();
    GLCALL(glDrawArrays(GL_LINES, 0, lines.size() * 2));
    lineData.vao->UnBind();

    rectData.vao->Bind();
    rectData.ibo->Bind();
    GLCALL(glDrawElements(GL_TRIANGLES, rects.size() * 6, GL_UNSIGNED_INT, 0));
    rectData.ibo->UnBind();
    rectData.vao->UnBind();
    
    debugRendererData.defaultShader->UnBind();
}
void DebugRenderer::Flush()
{
    lines.clear();
    rects.clear();
}