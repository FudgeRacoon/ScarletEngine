#include "scarlet/scene/Registry.hpp"
using namespace scarlet;

Registry::Registry() : entityCount(0) {}
Registry::~Registry()
{
    for(auto entity : this->entities)
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

    this->entities.insert(std::make_pair(this->entityCount, entity));

    this->setupQueue.push(entity);
    return entity;
}

GameObject* Registry::GetEntityById(uint32 id)
{
    auto it = this->entities.find(id);
    if(it != this->entities.end())
        return it->second;

    Logger::LogWarning("Entity does not exist.");
    return nullptr;
}
GameObject* Registry::GetEntityByName(std::string name)
{
    return nullptr;
}

Registry::EntityTreeMap Registry::GetEntities()
{
    return this->entities;
}

void Registry::DestroyEntityById(uint32 id)
{
    auto it = this->entities.find(id);
    if(it != this->entities.end())
    {
        this->destroyQueue.push(it->second);
        this->entities.erase(it);
        return;
    }

    Logger::LogWarning("Entity does not exist.");
    return;
}
void Registry::DestroyEntityByName(std::string name)
{
    
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