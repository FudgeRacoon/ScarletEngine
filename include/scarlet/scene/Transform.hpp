#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include "scarlet/scene/Component.hpp"

#include "scarlet/core/math/Vector3.hpp"

namespace scarlet
{
    class Transform : public Component
    {
    public:
        Vector3 position;
        Vector3 rotation;
        Vector3 scale;
    
    public:
        Transform();

    public:
        void Setup() override;
        void Update() override;
        void GuiUpdate() override;
    };
}

#endif