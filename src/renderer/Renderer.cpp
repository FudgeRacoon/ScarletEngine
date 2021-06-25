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
    
    shader->SetMat4("proj", Matrix4::GetValuePointer(camera->GetProjectionMatrix()));
    shader->SetMat4("view", Matrix4::GetValuePointer(camera->GetViewMatrix()));
    shader->SetVec4f("u_color", 1.0f, 0.0f, 0.0f, 0.0f);

    glDrawElements(GL_LINE_LOOP, 6, GL_UNSIGNED_INT, 0);

    rect->DisbaleBuffers();

    shader->UnBind();
}
void Renderer::Render(Camera& camera, const Texture*& texture, const VertexArray*& va, const IndexBuffer* ib, const Shader*& shader)
{
    va->Bind();
    ib->Bind();
    texture->Bind();
    shader->Bind();

    if(InputManager::GetKey(KeyCode::D))
        camera.position.x += 5.0f;
    else if(InputManager::GetKey(KeyCode::A))
        camera.position.x -= 5.0f;
    else if(InputManager::GetKey(KeyCode::W))
        camera.position.y += 5.0f;
    else if(InputManager::GetKey(KeyCode::S))
        camera.position.y -= 5.0f;

    //World space to view space using view matrix
    shader->SetMat4("view", Matrix4::GetValuePointer(camera.GetViewMatrix()));

    //View space to clip space using projection matrix
    shader->SetMat4("proj", Matrix4::GetValuePointer(camera.GetProjectionMatrix()));

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    va->UnBind();
    ib->UnBind();
    texture->UnBind();
    shader->UnBind();
}