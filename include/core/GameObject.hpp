#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <vector>
#include <string>
#include <type_traits>

#include "core/Component.hpp"
#include "core/Logger.hpp"

namespace scarlet
{
    class GameObjectManager;

    class GameObject
    {
    private:
        std::string name;

    private:
        std::vector<Component*> components;

    private:
        GameObject(std::string name) : name(name) {}
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
                    return;
                }
        }
    
    public:
        void Setup()
        {
            for(Component* component : this->components)
                component->Setup();
        }
        void Update()
        {
            for(Component* component : this->components)
                component->Update();
        }
    
        friend GameObjectManager;
    };
}

#endif