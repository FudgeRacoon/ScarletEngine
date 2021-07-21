#ifndef COMPONENT_HPP
#define COMPONENT_HPP

namespace scarlet
{
    class GameObject;

    class Component
    {
    public:
        GameObject* gameObject = nullptr;

    public:
        virtual void Setup() = 0;
        virtual void Update() = 0;
        virtual void GUI() = 0;
    };
}

#endif