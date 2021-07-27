#include "scarlet/system//GameObjectManager.hpp"
using namespace scarlet;

GameObjectManager::GameObjectManager() : gameObjectCount(0) {}
GameObjectManager::~GameObjectManager()
{
    for(std::pair<std::string, GameObject*> gameObject : this->gameObjects)
        delete gameObject.second;
    this->gameObjects.clear();

    while(!this->setupQueue.empty())
    {
        delete this->setupQueue.front();
        this->setupQueue.pop();
    }

    while(!this->destroyQueue.empty())
    {
        delete this->destroyQueue.front();
        this->destroyQueue.pop();
    }
}

GameObject* GameObjectManager::AddGameObject()
{
    std::string name = "gameObject_" + std::to_string(gameObjectCount++);

    GameObject* gameObject = new GameObject(name);
    this->gameObjects.insert(std::make_pair(name, gameObject));
    this->setupQueue.push(gameObject);
    return gameObject;
}
GameObject* GameObjectManager::GetGameObject(std::string name)
{
    auto it = gameObjects.find(name);
    if(it != gameObjects.end())
        return it->second;

    Logger::LogWarning("GameObject does not exist.");
    return nullptr;
}
void GameObjectManager::DestroyGameObject(std::string name)
{
    auto it = this->gameObjects.find(name);
    if(it != this->gameObjects.end())
    {
        this->destroyQueue.push(it->second);
        this->gameObjects.erase(it);
        return;
    }

    Logger::LogWarning("GameObject does not exist.");
    return;
}

uint32 GameObjectManager::GetGameObjectCount()
{
    return this->gameObjectCount;
}

void GameObjectManager::PollSetupQueue()
{
    while(!this->setupQueue.empty())
    {
        this->setupQueue.front()->Setup();
        this->setupQueue.pop();   
    }
}
void GameObjectManager::PollDestroyQueue()
{
    while(!this->destroyQueue.empty())
    {
        delete this->destroyQueue.front();
        this->destroyQueue.pop();
    }
}

void GameObjectManager::UpdateGameObjects()
{
    for(std::pair<std::string, GameObject*> gameObject : this->gameObjects)
        gameObject.second->Update();
}
void GameObjectManager::RenderGameObjects(Camera* camera)
{
    Renderer::BeginScene(camera);

    for(std::pair<std::string, GameObject*> gameObject : this->gameObjects)
        Renderer::DrawEntity(gameObject.second);
    
    Renderer::EndScene();
}