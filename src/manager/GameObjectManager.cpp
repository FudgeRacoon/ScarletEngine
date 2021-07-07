#include "core/manager/GameObjectManager.hpp"
using namespace scarlet;

#include "core/Logger.hpp"

std::map<std::string, GameObject*> GameObjectManager::gameObjects;

GameObject* GameObjectManager::AddGameObject(std::string name)
{
    GameObject* gameObject = new GameObject(name);
    gameObjects.insert(std::make_pair(name, gameObject));
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

void GameObjectManager::SetupGameObjects()
{
    //Dangerous way to implement this. Will definetly cause issues when
    //a gameobject adds a another during setup time. Better use a queue
    //to poll gameobjects awaiting setting up.
    for(std::pair<std::string, GameObject*> gameObject : gameObjects)
        gameObject.second->Setup();
}
void GameObjectManager::UpdateGameObjects()
{
    for(std::pair<std::string, GameObject*> gameObject : gameObjects)
        gameObject.second->Update();
}