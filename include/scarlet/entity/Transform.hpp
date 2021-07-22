#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include "scarlet/entity/Component.hpp"

#include "scarlet/math/Vector3.hpp"

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
        void GUI() override;
    };
}

#endif