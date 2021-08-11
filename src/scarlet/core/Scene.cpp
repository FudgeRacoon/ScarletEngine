#include "scarlet/core/Scene.hpp"
using namespace scarlet;

Scene::Scene(std::string name, uint32 buildIndex) : name(name), buildIndex(buildIndex)
{
    this->gameObjectManager = new GameObjectManager();
    this->sceneCamera = new Camera();
}
Scene::~Scene()
{
    delete this->gameObjectManager;
}

std::string Scene::GetName()
{
    return this->name;
}
uint32 Scene::GetBuildIndex()
{
    return this->buildIndex;
}
uint32 Scene::GetGameObjectCount()
{
    return this->gameObjectManager->GetGameObjectCount();
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

void Scene::OnEnter()
{
    this->gameObjectManager->PollSetupQueue();
}
void Scene::OnUpdate()
{
    this->gameObjectManager->UpdateGameObjects();
    this->gameObjectManager->PollDestroyQueue();
}

void Scene::OnRenderEditor(Camera* editorCamera, editor::Selector* selector)
{
    this->gameObjectManager->RenderEditor(editorCamera, selector);
}
void Scene::OnRenderRuntime()
{
    this->gameObjectManager->RenderRuntime(this->sceneCamera);
}

GameObject* Scene::AddGameObject()
{
    return this->gameObjectManager->AddGameObject();
}
GameObject* Scene::GetGameObject(std::string name)
{
    return this->gameObjectManager->GetGameObject(name);
}
void Scene::DestroyGameObject(std::string name)
{
    this->gameObjectManager->DestroyGameObject(name);
}

