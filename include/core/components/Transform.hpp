#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include "core/Component.hpp"
#include "core/math/Vector3.hpp"

namespace scarlet
{
    class Transform : public Component
    {
    public:
        Vector3 position;
        Vector3 rotation;
        Vector3 scale;

    public:
        void Setup() override
        {

        }

        void Update() override
        {

        }
    };
}

#endif