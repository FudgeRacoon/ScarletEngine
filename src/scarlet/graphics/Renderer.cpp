#include "scarlet/graphics/Renderer.hpp"
using namespace scarlet;

RendererData Renderer::rendererData;

void Renderer::Init()
{
    rendererData.defualtShader = new Shader("assets\\shaders\\defaultFragment.shader");
}

void Renderer::BeginScene(Camera* camera)
{
    rendererData.rendererCamera = camera;
}
void Renderer::EndScene()
{
    rendererData.rendererCamera = nullptr;
}

void Renderer::DrawEntity(GameObject* gameObject)
{
    // Transform* transform = gameObject->GetComponent<Transform>();
    // SpriteRenderer* spriteRenderer = gameObject->GetComponent<SpriteRenderer>();

    // spriteRenderer->material->Bind();
    // spriteRenderer->sprite->GetRect()->Bind();
    // spriteRenderer->sprite->GetTexture()->Bind();

    // Matrix4 model = Matrix4::Identity();
    // model = model * Matrix4::Scale(transform->scale);
    // model = model * Matrix4::Rotate(transform->rotation.x, Vector3::RIGHT());
    // model = model * Matrix4::Rotate(transform->rotation.y, Vector3::UP());
    // model = model * Matrix4::Rotate(transform->rotation.z, Vector3::FRONT());
    // model = model * Matrix4::Transalte(transform->position);
    
    // rendererData.defualtShader->SetMat4("u_model", model);
    // rendererData.defualtShader->SetMat4("u_view", rendererData.rendererCamera->GetViewMatrix());
    // rendererData.defualtShader->SetMat4("u_proj", rendererData.rendererCamera->GetProjectionMatrix());
    // rendererData.defualtShader->SetVec4f("u_color", (Vector4)spriteRenderer->color);

    // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // spriteRenderer->sprite->GetTexture()->UnBind();
    // spriteRenderer->sprite->GetRect()->UnBind();
    // spriteRenderer->material->UnBind();
}