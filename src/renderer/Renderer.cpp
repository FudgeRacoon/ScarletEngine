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
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}
void Renderer::SwapBuffers()
{
    SDL_GL_SwapWindow(Window::Get()->GetSDLWindow());
}

void Renderer::Render(Camera& camera, const VertexArray*& va, const IndexBuffer* ib, const Shader*& shader)
{
    va->Bind();
    ib->Bind();
    shader->Bind();

    if(InputManager::GetKey(KeyCode::RIGHT))
        camera.position.x += 5.0f;
    else if(InputManager::GetKey(KeyCode::LEFT))
        camera.position.x -= 5.0f;
    else if(InputManager::GetKey(KeyCode::UP))
        camera.position.y += 5.0f;
    else if(InputManager::GetKey(KeyCode::DOWN))
        camera.position.y -= 5.0f;

    //World space to view space using view matrix
    shader->SetMat4("view", Matrix4::GetValuePointer(camera.GetViewMatrix()));

    //View space to clip space using projection matrix
    shader->SetMat4("proj", Matrix4::GetValuePointer(camera.GetProjectionMatrix()));

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}