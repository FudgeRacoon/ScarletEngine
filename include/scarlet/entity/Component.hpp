#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include "scarletEditor/panels/ComponentMenu.hpp"

namespace scarlet
{
    class GameObject;

    class Component
    {
    public:
        ComponentMenu* componentMenu;

    public:
        GameObject* gameObject = nullptr;

    public:
        Component() = default;
        virtual ~Component() = default;

    public:
        virtual void Setup() = 0;
        virtual void Update() = 0;
        virtual void UIUpdate() = 0;
    };
}

#endif