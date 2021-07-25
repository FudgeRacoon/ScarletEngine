#include "scarlet/graphics/Renderer.hpp"
using namespace scarlet;

RendererData Renderer::rendererData;

void Renderer::Init()
{
    glewExperimental = true;
    if(glewInit() != 0)
    {
        Logger::LogFatal("Cannot Initialize Glew.");
        Window::Get()->Quit();
    }

    rendererData.defualtShader = new Shader("assets\\shaders\\defaultFragment.shader");
}

Vector4 Renderer::GetViewport()
{
    return rendererData.viewport;
}

void Renderer::SetViewport(uint32 x, uint32 y, uint32 width, uint32 height)
{
    rendererData.viewport = Vector4(x, y, width, height);
    glViewport(x, y, width, height);
}
void Renderer::SetBlendingFunction(uint32 sFactor, uint32 dFactor)
{
    glBlendFunc(sFactor, dFactor);
}
void Renderer::SetClearColor(Color color)
{
    rendererData.clearColor = color;
}

void Renderer::EnableBlending(bool enable)
{
    switch(enable)
    {
        case true: glEnable(GL_BLEND); break;
        case false: glDisable(GL_BLEND); break;
    }
}

void Renderer::ClearBuffers(uint32 buffers)
{
    glClearColor(
        rendererData.clearColor.r / 255.0f, 
        rendererData.clearColor.g / 255.0f, 
        rendererData.clearColor.b / 255.0f, 
        1.0f
    );
    glClear(buffers);
}
void Renderer::SwapBuffers()
{
    SDL_GL_SwapWindow(Window::Get()->GetSDLWindow());
}

void Renderer::BeginScene(Camera* camera)
{
    rendererData.rendererCamera = camera;
}
void Renderer::EndScene()
{
    rendererData.rendererCamera = nullptr;
}

void Renderer::DrawRect(Rect* rect, Color color, const Shader* shader)
{   
    const Shader* tempShader;
    if(shader == nullptr)
        tempShader = rendererData.defualtShader;
    else
        tempShader = shader;

    rect->Bind();
    tempShader->Bind();

    tempShader->SetMat4("u_model", Matrix4::Identity());
    tempShader->SetMat4("u_view", rendererData.rendererCamera->GetViewMatrix());
    tempShader->SetMat4("u_proj", rendererData.rendererCamera->GetProjectionMatrix());
    tempShader->SetVec4f("u_color", (Vector4)color);

    glDrawElements(GL_LINE_LOOP, 6, GL_UNSIGNED_INT, 0);

    tempShader->UnBind();
    rect->UnBind();
}
void Renderer::DrawEntity(GameObject* gameObject)
{
    Transform* transform = gameObject->GetComponent<Transform>();
    SpriteRenderer* spriteRenderer = gameObject->GetComponent<SpriteRenderer>();

    spriteRenderer->material->Bind();
    spriteRenderer->sprite->GetRect()->Bind();
    spriteRenderer->sprite->GetTexture()->Bind();

    Matrix4 model = Matrix4::Identity();
    model = model * Matrix4::Scale(transform->scale);
    model = model * Matrix4::Rotate(transform->rotation.x, Vector3::RIGHT());
    model = model * Matrix4::Rotate(transform->rotation.y, Vector3::UP());
    model = model * Matrix4::Rotate(transform->rotation.z, Vector3::FRONT());
    model = model * Matrix4::Transalte(transform->position);
    
    rendererData.defualtShader->SetMat4("u_model", model);
    rendererData.defualtShader->SetMat4("u_view", rendererData.rendererCamera->GetViewMatrix());
    rendererData.defualtShader->SetMat4("u_proj", rendererData.rendererCamera->GetProjectionMatrix());
    rendererData.defualtShader->SetVec4f("u_color", (Vector4)spriteRenderer->color);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    spriteRenderer->sprite->GetTexture()->UnBind();
    spriteRenderer->sprite->GetRect()->UnBind();
    spriteRenderer->material->UnBind();
}