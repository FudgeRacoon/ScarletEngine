#include "core/renderer/Renderer.hpp"
using namespace scarlet;

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

void Renderer::Render(const VertexArray*& va, const IndexBuffer* ib, const Shader*& shader)
{
    va->Bind();
    ib->Bind();
    shader->Bind();

    //World space to view space using view matrix

    //View space to clip space using projection matrix
    Matrix4 projection = Matrix4::Orthographic(0.0f, Window::Get()->GetWidth(), 0.0f, Window::Get()->GetHeight(), 0.0f, -1000.0f);
    shader->SetMat4("proj", Matrix4::GetValuePointer(projection));

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}