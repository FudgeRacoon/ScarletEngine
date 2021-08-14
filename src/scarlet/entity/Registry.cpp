#include "scarlet/entity/Registry.hpp"
using namespace scarlet;

Registry::Registry() : entityCount(0) {}
Registry::~Registry()
{
    for(std::pair<uint32, GameObject*> entity : this->entitiesId)
        delete entity.second;

    this->entitiesId.clear();

    for(std::pair<std::string, GameObject*> entity : this->entities)
        delete entity.second;
        
    this->entities.clear();

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

GameObject* Registry::AddEntity()
{
    std::string name = "entity_" + std::to_string(++entityCount);

    GameObject* entity = new GameObject(name, entityCount);

    this->entitiesId.insert(std::make_pair(this->entityCount, entity));
    this->entities.insert(std::make_pair(name, entity));

    this->setupQueue.push(entity);
    return entity;
}

GameObject* Registry::GetEntityById(uint32 id)
{
    auto it = this->entitiesId.find(id);
    if(it != this->entitiesId.end())
        return it->second;

    Logger::LogWarning("Entity does not exist.");
    return nullptr;
}
GameObject* Registry::GetEntityByName(std::string name)
{
    auto it = entities.find(name);
    if(it != entities.end())
        return it->second;

    Logger::LogWarning("Entity does not exist.");
    return nullptr;
}

Registry::EntityTreeMap Registry::GetEntities()
{
    return this->entities;
}

void Registry::DestroyEntityById(uint32 id)
{
    auto entityIdIt = this->entitiesId.find(id);
    if(entityIdIt != this->entitiesId.end())
    {
        this->destroyQueue.push(entityIdIt->second);

        auto entityStringIt = this->entities.find(entityIdIt->second->GetName());
        this->entities.erase(entityStringIt);

        this->entitiesId.erase(entityIdIt);
        return;
    }

    Logger::LogWarning("Entity does not exist.");
    return;
}
void Registry::DestroyEntityByName(std::string name)
{
    auto entityStringIt = this->entities.find(name);
    if(entityStringIt != this->entities.end())
    {
        this->destroyQueue.push(entityStringIt->second);

        auto entityIdIt = this->entitiesId.find(entityStringIt->second->GetInstanceId());
        this->entitiesId.erase(entityIdIt);

        this->entities.erase(entityStringIt);
        return;
    }

    Logger::LogWarning("Entity does not exist.");
    return;
}

uint32 Registry::GetEntityCount()
{
    return this->entityCount;
}

void Registry::PollSetupQueue()
{
    while(!this->setupQueue.empty())
    {
        this->setupQueue.front()->Setup();
        this->setupQueue.pop();   
    }
}
void Registry::PollDestroyQueue()
{
    while(!this->destroyQueue.empty())
    {
        delete this->destroyQueue.front();
        this->destroyQueue.pop();
    }
}