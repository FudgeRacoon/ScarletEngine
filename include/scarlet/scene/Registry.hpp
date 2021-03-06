#ifndef Registry_HPP
#define Registry_HPP

#include <map>
#include <queue>
#include <vector>
#include <string>

#include "scarlet/core/Types.hpp"
#include "scarlet/core/logger/Logger.hpp"

#include "scarlet/scene/GameObject.hpp"

namespace scarlet
{   
    class Registry
    {
    public:
        using EntityTreeMap = std::map<uint32, GameObject*>;
        using EntitySetupQueue = std::queue<GameObject*>;
        using EntityDestroyQueue = std::queue<GameObject*>;

    private:
        uint32 entityCount;

    private:
        EntityTreeMap entities;

    private:
        EntitySetupQueue setupQueue;
        EntityDestroyQueue destroyQueue;
    
    public:
        Registry();
        ~Registry();

    public:
        GameObject* AddEntity();

    public:
        uint32 GetEntityCount();
        EntityTreeMap GetEntities();
        GameObject* GetEntityById(uint32 id);
        GameObject* GetEntityByName(std::string name);
        
    public:
        template<typename T> 
        std::vector<GameObject*> GetEntitiesOfType()
        {
            std::vector<GameObject*> entitiesOfType;

            for(auto it = this->entities.begin(); it != this->entities.end(); it++)
                if(it->second->GetComponent<T>() != nullptr)
                    entitiesOfType.push_back(it->second);

            return entitiesOfType;
        }
        
    public:
        void DestroyEntityById(uint32 id);
        void DestroyEntityByName(std::string name);

    public:
        void PollSetupQueue();
        void PollDestroyQueue();
    };
}

#endif