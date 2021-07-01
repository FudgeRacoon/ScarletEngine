#include "core/renderer/Renderer.hpp"
using namespace scarlet;

#include "core/Camera.hpp"
#include "core/manager/InputManager.hpp"

Renderer* Renderer::Get()
{
    static Renderer* instance = new Renderer();
    return instance;
}

void Renderer::ClearBuffers()
{
    glClearColor(0.35f, 0.35f, 0.35f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}
void Renderer::SwapBuffers()
{
    SDL_GL_SwapWindow(Window::Get()->GetSDLWindow());
}

void Renderer::Render(Camera* camera, Shader*& shader, GameObject* gameObject)
{

}
void Renderer::Render(Camera* camera, Shader*& shader, Rect* rect)
{
    shader->Bind();
    rect->EnableBuffers();
    
    camera->ProcessMouseMovement();

    shader->SetMat4("proj", Matrix4::GetValuePointer(camera->GetProjectionMatrix()));
    shader->SetMat4("view", Matrix4::GetValuePointer(camera->GetViewMatrix()));
    shader->SetVec4f("u_color", 0.0f, 0.0f, 0.0f, 1.0f);

    glDrawElements(GL_LINE_LOOP, 6, GL_UNSIGNED_INT, 0);

    rect->DisbaleBuffers();
    shader->UnBind();
}