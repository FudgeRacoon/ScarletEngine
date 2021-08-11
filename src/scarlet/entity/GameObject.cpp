#include "scarlet/entity/GameObject.hpp"
using namespace scarlet;

GameObject::GameObject(std::string name, uint32 instanceID)
{
    this->name = name;
    this->instanceID = instanceID;
    this->active = true;
    
    this->AddComponent<Transform>();
}
GameObject::~GameObject()
{
    for(Component* component : this->components)
        delete component;

    this->components.clear();
}

bool GameObject::GetActive()
{
    return this->active;
}
uint32 GameObject::GetInstanceID()
{
    return this->instanceID;
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