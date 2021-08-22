#include "scarlet/graphics/Renderer.hpp"
using namespace scarlet;

RendererData Renderer::rendererData;

void Renderer::StartBatch()
{
    rendererData.lineCount = 0;
    rendererData.quadCount = 0;

    rendererData.currentTextureIndex = 1;
    for(int i = rendererData.currentTextureIndex; i < GraphicsContext::GetMaxTextureSlots(); i++)
        rendererData.textureSlots[i] = nullptr;
    
    rendererData.lineVertexPtr = rendererData.lineVertexBase;
    rendererData.quadVertexPtr = rendererData.quadVertexBase;
}
void Renderer::NextBatch()
{
    Flush();
    StartBatch();
}
void Renderer::Flush()
{   
    rendererData.currentShader->Bind();

    for(int i = 0; i < rendererData.currentTextureIndex; i++)
        rendererData.textureSlots[i]->Bind(i);
    
    rendererData.lineVertexBuffer->UpdateBufferData(
        0,
        rendererData.lineCount * rendererData.LINE_VERTICES_SIZE,
        rendererData.lineVertexBase
    );

    rendererData.quadVertexBuffer->UpdateBufferData(
        0,
        rendererData.quadCount * rendererData.QUAD_VERTICES_SIZE,
        rendererData.quadVertexBase
    );

    rendererData.currentShader->SetMat4(
        "uView", rendererData.rendererCamera->GetViewMatrix()
    );
    rendererData.currentShader->SetMat4(
        "uProj", rendererData.rendererCamera->GetProjectionMatrix()
    );

    DrawArrays(
        Graphics_DrawMode::SCARLET_LINES,
        rendererData.lineVertexArray,
        rendererData.lineCount * 2
    );

    DrawElements(
        Graphics_DrawMode::SCARLET_TRIANGLES, 
        rendererData.quadVertexArray, 
        rendererData.quadIndexBuffer,
        rendererData.quadCount * 6
    );

    for(int i = 0; i < rendererData.currentTextureIndex; i++)
        rendererData.textureSlots[i]->UnBind();
        
    rendererData.currentShader->UnBind();
}

void Renderer::InitBuffers()
{
    rendererData.lineVertexBuffer = new VertexBuffer(
        nullptr,
        rendererData.MAX_LINE_VERTICES_SIZE,
        GL_DYNAMIC_DRAW
    );
    rendererData.lineVertexBuffer->AddLayout<float>(3, false);
    rendererData.lineVertexBuffer->AddLayout<float>(4, false);
    rendererData.lineVertexBuffer->AddLayout<float>(2, false);
    rendererData.lineVertexBuffer->AddLayout<float>(1, false);
    rendererData.lineVertexBuffer->AddLayout<float>(1, false);

    rendererData.lineVertexArray = new VertexArray();
    rendererData.lineVertexArray->AddBuffer(rendererData.lineVertexBuffer);

    rendererData.quadVertexBuffer = new VertexBuffer(
        nullptr, 
        rendererData.MAX_QUAD_VERTICES_SIZE, 
        GL_DYNAMIC_DRAW
    );
    rendererData.quadVertexBuffer->AddLayout<float>(3, false);
    rendererData.quadVertexBuffer->AddLayout<float>(4, false);
    rendererData.quadVertexBuffer->AddLayout<float>(2, false);
    rendererData.quadVertexBuffer->AddLayout<float>(1, false);
    rendererData.quadVertexBuffer->AddLayout<float>(1, false);

    int offset = 0;
    uint32 indices[rendererData.MAX_QUADS * 6];
    for(int i = 0; i < rendererData.MAX_QUADS * 6; i += 6)
    {
        indices[i + 0] = 0 + offset;  
        indices[i + 1] = 1 + offset;
        indices[i + 2] = 2 + offset;
        indices[i + 3] = 2 + offset;
        indices[i + 4] = 3 + offset;
        indices[i + 5] = 0 + offset;

        offset += 4;
    }

    rendererData.quadIndexBuffer = new IndexBuffer(
        indices, 
        rendererData.MAX_QUAD_INDICIES_SIZE, 
        GL_STATIC_DRAW
    );

    rendererData.quadVertexArray = new VertexArray();
    rendererData.quadVertexArray->AddBuffer(rendererData.quadVertexBuffer);
}
void Renderer::InitTextureSlots()
{
    rendererData.whiteTexture = AssetPool::GetTexture("white_texture");
    rendererData.textureSlots = new Texture*[GraphicsContext::GetMaxTextureSlots()];
    rendererData.textureSlots[0] = rendererData.whiteTexture;
}
void Renderer::InitShaders()
{   
    rendererData.currentShader = AssetPool::GetShader("default_shader");
}

void Renderer::DrawArrays(Graphics_DrawMode mode, VertexArray* vao, uint32 count)
{
    vao->Bind();
    GLCALL(glDrawArrays(mode, 0, count));
    vao->UnBind();
}
void Renderer::DrawElements(Graphics_DrawMode mode, VertexArray* vao, IndexBuffer* ibo, uint32 count)
{
    vao->Bind();
    ibo->Bind();
    GLCALL(glDrawElements(mode, count, GL_UNSIGNED_INT, 0));
    ibo->UnBind();
    vao->UnBind();
}

void Renderer::OnInit()
{
    Logger::LogInfo("Intitializing Renderer Subsystem...");

    InitBuffers();
    InitTextureSlots();
    InitShaders();

    rendererData.lineVertexBase = new RendererVertexData[rendererData.MAX_LINES * 2];
    rendererData.lineVertexPtr = rendererData.lineVertexBase;

    rendererData.quadVertexBase = new RendererVertexData[rendererData.MAX_QUADS * 4];
    rendererData.quadVertexPtr = rendererData.quadVertexBase;
}
void Renderer::OnShutDown()
{
    delete rendererData.lineVertexBuffer;
    delete rendererData.lineVertexArray;

    delete rendererData.quadVertexBuffer;
    delete rendererData.quadIndexBuffer;
    delete rendererData.quadVertexArray;

    delete[] rendererData.lineVertexBase;
    delete[] rendererData.quadVertexBase;

    delete[] rendererData.textureSlots;
}

void Renderer::BeginScene(Camera* camera)
{
    StartBatch();

    rendererData.rendererCamera = camera;
}
void Renderer::EndScene()
{
    Flush();

    rendererData.rendererCamera = nullptr;
}

Shader* Renderer::GetBoundShader()
{
    return rendererData.currentShader;
}
void Renderer::BindShader(Shader* shader)
{
    rendererData.currentShader = shader;
}

void Renderer::DrawLine(Line line, Color color)
{
    if(rendererData.lineCount >= rendererData.MAX_LINES)
        NextBatch();

    Vector3 position;

    for(int i = 0; i < 2; i++)
    {
        rendererData.lineVertexPtr->position = i == 0 ? line.start : line.end;
        rendererData.lineVertexPtr->color = (Vector4)color;
        rendererData.lineVertexPtr->textureCoords = Vector2();
        rendererData.lineVertexPtr->textureIndex = 0;
        rendererData.lineVertexPtr->instanceID = -1;
        rendererData.lineVertexPtr++;
    }

    rendererData.lineCount++;
}
void Renderer::DrawLine(Vector3 start, Vector3 end, Color color)
{
    DrawLine(Line(start, end), color);
}
void Renderer::DrawLine(float x0, float y0, float x1, float y1, Color color)
{
    DrawLine(Line(x0, y0, x1, y1), color);
}

void Renderer::DrawQuad(Rect rect, Color color)
{
    float x = rect.GetX(); 
    float y = rect.GetY();
    float xMax = x + rect.GetWidth();
    float yMax = y - rect.GetHeight();

    DrawLine(x, y, xMax, y, color);
    DrawLine(x, yMax, xMax, yMax, color);
    DrawLine(x, y, x, yMax, color);
    DrawLine(xMax, y, xMax, yMax, color);
}
void Renderer::DrawQuad(Vector3 position, Vector3 size, Color color)
{
    DrawQuad(Rect(position, size), color);
}
void Renderer::DrawQuad(float x, float y, float width, float height, Color color)
{
    DrawQuad(Rect(x, y, width, height), color);
}

void Renderer::DrawFilledQuad(Rect rect, Color color)
{
    if(rendererData.quadCount >= rendererData.MAX_QUADS)
        NextBatch();

    Vector3 position;

    for(int i = 0; i < 4; i++)
    {
        switch(i)
        {
            case 0: position = Vector3(
                rect.GetX(), 
                rect.GetY() - rect.GetHeight(), 
                0.0f
            ); break;

            case 1: position = Vector3(
                rect.GetX() + rect.GetWidth(), 
                rect.GetY() - rect.GetHeight(), 
                0.0f
            ); break;

            case 2: position = Vector3(
                rect.GetX() + rect.GetWidth(), 
                rect.GetY(), 
                0.0f
            ); break;

            case 3: position = Vector3(
                rect.GetX(), 
                rect.GetY(), 
                0.0f
            ); break;
        }
    
        rendererData.quadVertexPtr->position = position;
        rendererData.quadVertexPtr->color = (Vector4)color;
        rendererData.quadVertexPtr->textureCoords = Vector2();
        rendererData.quadVertexPtr->textureIndex = 0;
        rendererData.quadVertexPtr->instanceID = -1;
        rendererData.quadVertexPtr++;
    }

    rendererData.quadCount++;
}
void Renderer::DrawFilledQuad(Vector3 position, Vector3 size, Color color)
{
    DrawFilledQuad(Rect(position, size), color);
}
void Renderer::DrawFilledQuad(float x, float y, float width, float height, Color color)
{
    DrawFilledQuad(Rect(x, y, width, height), color);
}

void Renderer::DrawRotatedQuad(Rect rect, float radians, Color color)
{
    if(rendererData.quadCount >= rendererData.MAX_QUADS)
        NextBatch();

    Vector3 position;

    for(int i = 0; i < 4; i++)
    {
        switch(i)
        {
            case 0: position = Vector3(
                rect.GetX(), 
                rect.GetY() - rect.GetHeight(), 
                0.0f
            ); break;

            case 1: position = Vector3(
                rect.GetX() + rect.GetWidth(), 
                rect.GetY() - rect.GetHeight(), 
                0.0f
            ); break;

            case 2: position = Vector3(
                rect.GetX() + rect.GetWidth(), 
                rect.GetY(), 
                0.0f
            ); break;

            case 3: position = Vector3(
                rect.GetX(), 
                rect.GetY(), 
                0.0f
            ); break;
        }
    
        rendererData.quadVertexPtr->position = Matrix4::Rotate(radians, Vector3::FRONT()) * position;
        rendererData.quadVertexPtr->color = (Vector4)color;
        rendererData.quadVertexPtr->textureCoords = Vector2();
        rendererData.quadVertexPtr->textureIndex = 0;
        rendererData.quadVertexPtr->instanceID = -1;
        rendererData.quadVertexPtr++;
    }

    rendererData.quadCount++;
}
void Renderer::DrawRotatedQuad(Vector3 position, Vector3 size, float radians, Color color)
{
    DrawRotatedQuad(Rect(position, size), radians, color);
}
void Renderer::DrawRotatedQuad(float x, float y, float width, float height, float radians, Color color)
{
    DrawRotatedQuad(Rect(x, y, width, height), radians, color);
}

void Renderer::DrawSprite(Sprite* sprite, Matrix4 model, uint32 id, Color color)
{
    if(rendererData.quadCount >= rendererData.MAX_QUADS)
        NextBatch();

    if(rendererData.currentTextureIndex >= GraphicsContext::GetMaxTextureSlots())
        NextBatch();

    bool textureExists; 
    uint32 textureIndex;

    if(sprite->GetTexture() != nullptr)
    {
        textureExists = false;
        textureIndex = rendererData.currentTextureIndex;

        for(int i = 0; i < rendererData.currentTextureIndex; i++)
            if(rendererData.textureSlots[i]->GetID() == sprite->GetTexture()->GetID())
            {
                textureExists = true;
                textureIndex = i;
                break;
            }
    
        if(!textureExists)
        {
            rendererData.textureSlots[textureIndex] = sprite->GetTexture();
            rendererData.currentTextureIndex++;
        }
    }
    else
        textureIndex = 0;

    Vector4 position;

    for(int i = 0; i < 4; i++)
    {
        switch (i)
        {
            case 0: position = Vector4(
                sprite->GetRect().GetX(), 
                sprite->GetRect().GetY() - sprite->GetRect().GetHeight(), 
                0.0f
            ); break;

            case 1: position = Vector4(
                sprite->GetRect().GetX() + sprite->GetRect().GetWidth(), 
                sprite->GetRect().GetY() - sprite->GetRect().GetHeight(), 
                0.0f
            ); break;

            case 2: position = Vector4(
                sprite->GetRect().GetX() + sprite->GetRect().GetWidth(), 
                sprite->GetRect().GetY(), 
                0.0f
            ); break;

            case 3: position = Vector4(
                sprite->GetRect().GetX(), 
                sprite->GetRect().GetY(), 
                0.0f
            ); break;
        }
    
        rendererData.quadVertexPtr->position = model * position;
        rendererData.quadVertexPtr->color = (Vector4)color;
        rendererData.quadVertexPtr->textureCoords = sprite->GetUV().at(i);
        rendererData.quadVertexPtr->textureIndex = textureIndex;
        rendererData.quadVertexPtr->instanceID = (float)id;
        rendererData.quadVertexPtr++;
    }

    rendererData.quadCount++;
}