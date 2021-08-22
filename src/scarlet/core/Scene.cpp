#include "scarlet/core/Scene.hpp"
using namespace scarlet;

Scene::Scene(std::string name, uint32 buildIndex) : name(name), buildIndex(buildIndex)
{
    this->registry = new Registry();
    this->sceneCamera = new Camera();
}
Scene::~Scene()
{
    delete this->registry;
}

std::string Scene::GetName()
{
    return this->name;
}
uint32 Scene::GetBuildIndex()
{
    return this->buildIndex;
}
uint32 Scene::GetEntityCount()
{
    return this->registry->GetEntityCount();
}
Camera* Scene::GetCamera()
{
    return this->sceneCamera;
}

void Scene::SetName(std::string name)
{
    this->name = name;
}
void Scene::SetBuildIndex(uint32 buildIndex)
{
    this->buildIndex = buildIndex;
}
void Scene::SetCamera(Camera* camera)
{
    delete this->sceneCamera;
    this->sceneCamera = camera;
}

void Scene::OnEnterRuntime()
{
    this->registry->PollSetupQueue();
}
void Scene::OnUpdateRuntime()
{
    for(std::pair<std::string, GameObject*> entity : this->registry->GetEntities())
        entity.second->Update();

    this->registry->PollDestroyQueue();
}

void Scene::OnRenderRuntime()
{
    GraphicsContext::GetRenderTarget()->Bind();
    Renderer::BeginScene(this->sceneCamera);
    Renderer::BindShader(AssetPool::GetShader("default_shader"));

    GraphicsContext::ClearBuffers(Graphics_BufferType::SCARLET_BUFFER_COLOR);

    for(std::pair<std::string, GameObject*> entity : this->registry->GetEntities())
    {
        Transform* transform = entity.second->GetComponent<Transform>();
        SpriteRenderer* spriteRenderer = entity.second->GetComponent<SpriteRenderer>();

        if(!spriteRenderer || !spriteRenderer->sprite)
            return;

        Matrix4 model = Matrix4::Transform(
            transform->position, 
            transform->scale, 
            transform->rotation
        );

        Renderer::DrawSprite(
            spriteRenderer->sprite, 
            model, 
            entity.second->GetInstanceId(),
            spriteRenderer->color 
        );
    }
    
    Renderer::EndScene();
    GraphicsContext::GetRenderTarget()->UnBind();
}
void Scene::OnRenderEditor(Camera* editorCamera, editor::Selector* editorSelector)
{
    {
        editorSelector->Bind();
        Renderer::BeginScene(editorCamera);
        Renderer::BindShader(AssetPool::GetShader("selection_shader"));

        GraphicsContext::ClearBuffers(scarlet::SCARLET_BUFFER_COLOR);
        
        for(std::pair<std::string, GameObject*> entity : this->registry->GetEntities())
        {
            Transform* transform = entity.second->GetComponent<Transform>();
            SpriteRenderer* spriteRenderer = entity.second->GetComponent<SpriteRenderer>();

            if(!spriteRenderer || !spriteRenderer->sprite)
                return;

            Matrix4 model = Matrix4::Transform(
                transform->position, 
                transform->scale, 
                transform->rotation
            );

            Renderer::DrawSprite(
                spriteRenderer->sprite, 
                model, 
                entity.second->GetInstanceId(),
                spriteRenderer->color 
            );
        }

        Renderer::EndScene();
        editorSelector->UnBind();
    }
    
    {
        GraphicsContext::GetRenderTarget()->Bind();
        Renderer::BeginScene(editorCamera);
        Renderer::BindShader(AssetPool::GetShader("default_shader"));

        GraphicsContext::ClearBuffers(Graphics_BufferType::SCARLET_BUFFER_COLOR);

        for(std::pair<std::string, GameObject*> entity : this->registry->GetEntities())
        {
            Transform* transform = entity.second->GetComponent<Transform>();
            SpriteRenderer* spriteRenderer = entity.second->GetComponent<SpriteRenderer>();
    
            if(!spriteRenderer || !spriteRenderer->sprite)
                return;
    
            Matrix4 model = Matrix4::Transform(
                transform->position, 
                transform->scale, 
                transform->rotation
            );
    
            Renderer::DrawSprite(
                spriteRenderer->sprite, 
                model, 
                entity.second->GetInstanceId(),
                spriteRenderer->color 
            );
        }
        
        Renderer::EndScene();
        GraphicsContext::GetRenderTarget()->UnBind();
    }
}

GameObject* Scene::AddEntity()
{
    return this->registry->AddEntity();
}

GameObject* Scene::GetEntityById(uint32 id)
{
    return this->registry->GetEntityById(id);
}
GameObject* Scene::GetEntityByName(std::string name)
{
    return this->registry->GetEntityByName(name);
}

void Scene::DestroyEntityById(uint32 id)
{
    this->registry->DestroyEntityById(id);
}
void Scene::DestroyEntityByName(std::string name)
{
    this->registry->DestroyEntityByName(name);
}

