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
        Component() = default;
        virtual ~Component() = default;

    public:
        virtual void Setup() = 0;
        virtual void Update() = 0;
    };
}

#endif