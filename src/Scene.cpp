#include "core/Scene.hpp"
using namespace scarlet;

Scene::Scene(std::string name, uint32 buildIndex) : name(name), buildIndex(buildIndex)
{
    this->gameObjectManager = new GameObjectManager();
}
Scene::~Scene()
{
    delete this->gameObjectManager;
}

std::string Scene::GetName()
{
    return this->name;
}
void Scene::SetName(std::string name)
{
    this->name = name;
}

uint32 Scene::GetBuildIndex()
{
    return this->buildIndex;
}
void Scene::SetBuildIndex(uint32 buildIndex)
{
    this->buildIndex = buildIndex;
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

void Scene::OnEnter()
{
    this->gameObjectManager->PollSetupQueue();
}
void Scene::OnUpdate()
{
    this->gameObjectManager->UpdateGameObjects();
    this->gameObjectManager->PollDestroyQueue();
}
void Scene::OnRender(Camera*& camera, Shader*& shader)
{
    this->gameObjectManager->RenderGameObjects(camera, shader);
}
