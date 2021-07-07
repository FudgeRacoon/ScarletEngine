#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <vector>
#include <string>
#include <type_traits>

#include "core/Component.hpp"
#include "core/components/Transform.hpp"
#include "core/Logger.hpp"

namespace scarlet
{
    class GameObjectManager;

    class GameObject
    {
    private:
        std::string name;
        bool active;

    private:
        std::vector<Component*> components;

    private:
        GameObject(std::string name)
        {
            this->name = name;
            this->active = true;
            this->AddComponent<Transform>();
        }
        ~GameObject() = default;

    public:
        template <typename T>
        void AddComponent()
        {
            for(Component* component : this->components)
                if(dynamic_cast<T*>(component) != nullptr)
                {
                    Logger::LogWarning("Component already exists.");
                    return;
                }
            
            T* component = new T();
            component->gameObject = this;
            this->components.push_back(component);
        }
        template <typename T>
        T* GetComponent()
        {
            for(Component* component : this->components)
            {
                T* queriedComponent = dynamic_cast<T*>(component);
                
                if(queriedComponent != nullptr)
                    return queriedComponent;
            }

            Logger::LogError("Component does not exist.");
            return nullptr;
        }    
        template <typename T>
        void RemoveComponent()
        {
            for(auto it = this->components.begin(); it != this->components.end(); it++)
                if(dynamic_cast<T*>(*it) != nullptr)
                {
                    this->components.erase(it);
                    delete it;
                    return;
                }
        }
    
    public:
        bool GetActive()
        {
            return this->active;
        }
        void SetActive(bool value)
        {
            this->active = value;
        }

    public:
        void Setup()
        {
            if(this->active)
            {
                for(Component* component : this->components)
                component->Setup();
            }
        }
        void Update()
        {
            if(this->active)
            {
                for(Component* component : this->components)
                component->Update();
            }
        }
    
        friend GameObjectManager;
    };
}

#endif