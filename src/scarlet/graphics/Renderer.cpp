#include "scarlet/graphics/Renderer.hpp"
using namespace scarlet;

RendererData Renderer::rendererData;

void Renderer::StartBatch()
{
    rendererData.lineCount = 0;
    rendererData.quadCount = 0;

    rendererData.currentTextureIndex = 1;
    
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
    rendererData.defaultShader->Bind();

    for(int i = 0; i < rendererData.currentTextureIndex; i++)
    {
        rendererData.textureSlots[i]->Bind(i);
        rendererData.defaultShader->SetInt("textures[" + std::to_string(i) + "]", i);
    }

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

    rendererData.defaultShader->SetMat4(
        "uView", rendererData.rendererCamera->GetViewMatrix()
    );
    rendererData.defaultShader->SetMat4(
        "uProj", rendererData.rendererCamera->GetProjectionMatrix()
    );

    GraphicsContext::DrawArrays(
        DrawMode::SCARLET_LINES,
        rendererData.lineVertexArray,
        rendererData.lineCount * 2
    );

    GraphicsContext::DrawElements(
        DrawMode::SCARLET_TRIANGLES, 
        rendererData.quadVertexArray, 
        rendererData.quadIndexBuffer,
        rendererData.quadCount * 6
    );

    for(int i = 0; i < rendererData.currentTextureIndex; i++)
        rendererData.textureSlots[i]->UnBind();
        
    rendererData.defaultShader->UnBind();
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
    rendererData.whiteTexture = AssetPool::AddTexture("white_texture", 0xffffffff, 32, 32);
    rendererData.textureSlots = new Texture*[GraphicsContext::GetMaxTextureSlots()];
    rendererData.textureSlots[0] = rendererData.whiteTexture;
}
void Renderer::InitShaders()
{
    rendererData.defaultShader = new Shader(
        "assets\\shaders\\defaultVertex.shader",
        "assets\\shaders\\defaultFragment.shader"
    );
}

void Renderer::Init()
{
    InitBuffers();
    InitTextureSlots();
    InitShaders();

    rendererData.lineVertexBase = new RendererVertexData[rendererData.MAX_LINES * 2];
    rendererData.lineVertexPtr = rendererData.lineVertexBase;

    rendererData.quadVertexBase = new RendererVertexData[rendererData.MAX_QUADS * 4];
    rendererData.quadVertexPtr = rendererData.quadVertexBase;

    rendererData.defaultUV.push_back(Vector2(0.0f, 0.0f));
    rendererData.defaultUV.push_back(Vector2(1.0f, 0.0f));
    rendererData.defaultUV.push_back(Vector2(1.0f, 1.0f));
    rendererData.defaultUV.push_back(Vector2(0.0f, 1.0f));
}
void Renderer::ShutDown()
{
    delete rendererData.quadVertexBuffer;
    delete rendererData.quadIndexBuffer;
    delete rendererData.quadVertexArray;

    delete[] rendererData.textureSlots;

    delete[] rendererData.quadVertexBase;

    delete rendererData.defaultShader;
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

void Renderer::DrawLine(Line line, Color color)
{
    Vector3 position;

    for(int i = 0; i < 2; i++)
    {
        rendererData.lineVertexPtr->position = i == 0 ? line.start : line.end;
        rendererData.lineVertexPtr->color = (Vector4)color;
        rendererData.lineVertexPtr->textureCoords = Vector2();
        rendererData.lineVertexPtr->textureIndex = 0;
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
        rendererData.quadVertexPtr->textureCoords = rendererData.defaultUV.at(i);
        rendererData.quadVertexPtr->textureIndex = 0;
        rendererData.quadVertexPtr++;
    }

    rendererData.quadCount++;
}
void Renderer::DrawQuad(Vector3 position, Vector3 size, Color color)
{
    DrawQuad(Rect(position, size), color);
}
void Renderer::DrawQuad(float x, float y, float width, float height, Color color)
{
    DrawQuad(Rect(x, y, width, height), color);
}

void Renderer::DrawEntity(GameObject* gameObject)
{
    if(rendererData.quadCount >= rendererData.MAX_QUADS)
        NextBatch();

    if(rendererData.currentTextureIndex >= GraphicsContext::GetMaxTextureSlots())
        NextBatch();

    Transform* transform = gameObject->GetComponent<Transform>();
    SpriteRenderer* spriteRenderer = gameObject->GetComponent<SpriteRenderer>();
    Sprite* sprite = spriteRenderer->sprite;
    Texture* texture = sprite->GetTexture();

    if(!spriteRenderer || !sprite || !texture)
        return;

    Matrix4 model = Matrix4::Identity();
    model = model * Matrix4::Scale(transform->scale);
    model = model * Matrix4::Transalte(transform->position);
    model = model * Matrix4::Rotate(transform->rotation.x, Vector3::RIGHT());
    model = model * Matrix4::Rotate(transform->rotation.y, Vector3::UP());
    model = model * Matrix4::Rotate(transform->rotation.z, Vector3::FRONT());
    
    bool textureExists = false;
    uint32 textureIndex = rendererData.currentTextureIndex;

    for(int i = 0; i < rendererData.currentTextureIndex; i++)
        if(rendererData.textureSlots[i]->GetID() == texture->GetID())
        {
            textureExists = true;
            textureIndex = i;
            break;
        }
    
    if(!textureExists)
    {
        rendererData.textureSlots[textureIndex] = texture;
        rendererData.currentTextureIndex++;
    }

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
        rendererData.quadVertexPtr->color = (Vector4)spriteRenderer->color;
        rendererData.quadVertexPtr->textureCoords = sprite->GetUV().at(i);
        rendererData.quadVertexPtr->textureIndex = textureIndex;
        rendererData.quadVertexPtr++;
    }

    rendererData.quadCount++;
}