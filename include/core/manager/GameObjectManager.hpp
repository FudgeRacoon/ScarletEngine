#ifndef GAMEOBJECTMANAGER_HPP
#define GAMEOBJECTMANAGER_HPP

#include <map>
#include <string>

#include <core/GameObject.hpp>

namespace scarlet
{
    class GameObjectManager
    {
    private:
        static std::map<std::string, GameObject*> gameObjects;

    public:
        static void AddGameObject(std::string name);
        static GameObject* GetGameObject(std::string name);
        
    public:
        static void SetupGameObjects();
        static void UpdateGameObjects();
    };
}

#endif