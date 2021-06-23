#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <vector>
#include <string>
#include <type_traits>

#include "core/Logger.hpp"

class Component;

namespace scarlet
{
    class GameObject
    {
    private:
        std::string name;

    private:
        std::vector<Component*> components;

    private:
        GameObject() = delete;
        ~GameObject() = delete;
        GameObject(const GameObject& gameObject) = delete;

    public:
        template <typename T, typename... Args>
        void AddComponent(Args... args)
        {
            for(Component* component : this->components)
            {
                if(dynamic_cast<T*>(component) != nullptr)
                {
                    Logger::LogWarning("Component already exists.");
                    return;
                }
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
    };
}

#endif