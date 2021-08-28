#include "scarlet/scene/GameObject.hpp"
using namespace scarlet;

GameObject::GameObject(std::string& name, uint32 instanceId)
{
    this->instanceId = instanceId;
    this->active = true;
    
    this->AddComponent<Tag>();
    this->GetComponent<Tag>()->name = name;

    this->AddComponent<Transform>();
}
GameObject::~GameObject()
{
    for(Component* component : this->components)
        delete component;

    this->components.clear();
}

uint32 GameObject::GetInstanceId()
{
    return this->instanceId;
}
bool GameObject::GetActive()
{
    return this->active;
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