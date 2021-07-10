#ifndef GAMEOBJECTMANAGER_HPP
#define GAMEOBJECTMANAGER_HPP

#include <map>
#include <vector>
#include <string>

#include <core/GameObject.hpp>

namespace scarlet
{
    class GameObjectManager
    {
    private:
        static std::map<std::string, GameObject*> gameObjects;

    public:
        static GameObject* AddGameObject(std::string name);
        static GameObject* GetGameObject(std::string name);
    
    public:
        template<typename T>
        static std::vector<GameObject*> GetGameObjectsOfType()
        {
            std::vector<GameObject*> gameObjectsOfType;

            for(auto it = gameObjects.begin(); it != gameObjects.end(); it++)
                if(it->second->GetComponent<T>() != nullptr)
                    gameObjectsOfType.push_back(it->second);

            return gameObjectsOfType;
        }

    public:
        static void SetupGameObjects();
        static void UpdateGameObjects();
    };
}

#endif