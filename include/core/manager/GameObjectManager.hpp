#ifndef GAMEOBJECTMANAGER_HPP
#define GAMEOBJECTMANAGER_HPP

#include <map>
#include <queue>
#include <vector>
#include <string>

#include "core/GameObject.hpp"
#include "core/Camera.hpp"
#include "core/Logger.hpp"

#include "core/renderer/Renderer.hpp"
#include "core/renderer/Shader.hpp"

namespace scarlet
{   
    class GameObjectManager
    {
    using GameObjectTreeMap = std::map<std::string, GameObject*>;
    using GameObjectSetupQueue = std::queue<GameObject*>;
    using GameObjectDestroyQueue = std::queue<GameObject*>;

    private:
        uint32 gameObjectCount;

    private:
        GameObjectTreeMap gameObjects;

    private:
        GameObjectSetupQueue setupQueue;
        GameObjectDestroyQueue destroyQueue;
    
    public:
        GameObjectManager();
        ~GameObjectManager();

    public:
        GameObject* AddGameObject();
        GameObject* GetGameObject(std::string name);
        void DestroyGameObject(std::string name);

    public:  
        template<typename T>
        std::vector<GameObject*> GetGameObjectsOfType()
        {
            std::vector<GameObject*> gameObjectsOfType;

            for(auto it = this->gameObjects.begin(); it != this->gameObjects.end(); it++)
                if(it->second->GetComponent<T>() != nullptr)
                    gameObjectsOfType.push_back(it->second);

            return gameObjectsOfType;
        }

    public:
        void PollSetupQueue();
        void PollDestroyQueue();
        
    public:
        void UpdateGameObjects();
        void RenderGameObjects(Camera*& camera, Shader*& shader);
    };
}

#endif