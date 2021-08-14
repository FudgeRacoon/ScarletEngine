#include "scarlet/entity/GameObject.hpp"
using namespace scarlet;

GameObject::GameObject(std::string name, uint32 instanceId)
{
    this->name = name;
    this->instanceId = instanceId;
    this->active = true;
    
    this->AddComponent<Transform>();
}
GameObject::~GameObject()
{
    for(Component* component : this->components)
        delete component;

    this->components.clear();
}

std::string GameObject::GetName()
{
    return this->name;
}
bool GameObject::GetActive()
{
    return this->active;
}
uint32 GameObject::GetInstanceId()
{
    return this->instanceId;
}

void GameObject::SetName(std::string name)
{
    this->name = name;
}
void GameObject::SetActive(bool value)
{
    this->active = value;
}

void GameObject::Setup()
{
    for(Component* component : this->components)
        component->Setup();
}
void GameObject::Update()
{
    for(Component* component : this->components)
        component->Update();
}