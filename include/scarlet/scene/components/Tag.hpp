#ifndef TAG_HPP
#define TAG_HPP

#include <string>

#include "scarlet/scene/components/Component.hpp"

namespace scarlet
{
    class Tag : public Component
    {
    public:
        std::string tag;

    public:
        Tag() = default;

    public:
        void Setup() override;
        void Update() override;
    };
}

#endif