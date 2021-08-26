#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <vector>
#include <string>

#include "scarlet/core/logger/Logger.hpp"

#include "scarlet/scene/components/Component.hpp"
#include "scarlet/scene/components/Tag.hpp"
#include "scarlet/scene/components/Transform.hpp"

namespace scarlet
{
    class Scene;
    class Registry;

    class GameObject
    {
    private:
        uint32 instanceId;

    private:
        bool active;

    private:
        std::vector<Component*> components;

    private:
        GameObject(std::string& name, uint32 instanceID);
        ~GameObject();
    
    public:
        bool GetActive();
        uint32 GetInstanceId();

    public: 
        void SetActive(bool value);

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
                    delete it;
                    this->components.erase(it);
                    return;
                }
        }
    
    private:
        void Setup();
        void Update();

    friend Scene;
    friend Registry;
    };
}

#endif