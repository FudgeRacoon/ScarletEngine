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

void Renderer::Render(Camera*& camera, Shader*& shader, GameObject* gameObject)
{
    Transform* transform = gameObject->GetComponent<Transform>();
    SpriteRenderer* spriteRenderer = gameObject->GetComponent<SpriteRenderer>();

    if(spriteRenderer == nullptr || spriteRenderer->sprite == nullptr || spriteRenderer->sprite->GetTexture() == nullptr)
        return;

    shader->Bind();
    spriteRenderer->sprite->GetRect()->Bind();
    spriteRenderer->sprite->GetTexture()->Bind();

    Matrix4 model = Matrix4::Identity();
    model = model * Matrix4::Scale(transform->scale);
    model = model * Matrix4::Transalte(transform->position);
    model = model * Matrix4::Rotate(transform->rotation.x, Vector3::RIGHT());
    model = model * Matrix4::Rotate(transform->rotation.y, Vector3::UP());
    model = model * Matrix4::Rotate(transform->rotation.z, Vector3::FRONT());
    
    shader->SetMat4("u_model", Matrix4::GetValuePointer(model));
    shader->SetMat4("u_view", Matrix4::GetValuePointer(camera->GetViewMatrix()));
    shader->SetMat4("u_proj", Matrix4::GetValuePointer(camera->GetProjectionMatrix()));
    shader->SetVec4f
    (
        "u_color", 
        spriteRenderer->color.r / 255.0f,
        spriteRenderer->color.g / 255.0f,
        spriteRenderer->color.b / 255.0f,
        spriteRenderer->color.a / 255.0f
    );

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    spriteRenderer->sprite->GetTexture()->UnBind();
    spriteRenderer->sprite->GetRect()->UnBind();
    shader->UnBind();
}
void Renderer::Render(Camera*& camera, Shader*& shader, Rect* rect)
{
    shader->Bind();
    rect->Bind();
    
    shader->SetMat4("u_view", Matrix4::GetValuePointer(camera->GetViewMatrix()));
    shader->SetMat4("u_proj", Matrix4::GetValuePointer(camera->GetProjectionMatrix()));
    shader->SetVec4f("u_color", 0.0f, 0.0f, 0.0f, 1.0f);

    glDrawElements(GL_LINE_LOOP, 6, GL_UNSIGNED_INT, 0);

    rect->UnBind();
    shader->UnBind();
}