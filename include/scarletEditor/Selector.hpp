#ifndef Selector_HPP
#define Selector_HPP

#include "scarlet/core/Types.hpp"
#include "scarlet/core/logger/Logger.hpp"

#include "scarlet/scene/GameObject.hpp"

#include "scarlet/graphics/GraphicsContext.hpp"
#include "scarlet/graphics/FrameBuffer.hpp"

#include "scarlet/input/InputManager.hpp"

namespace scarlet
{
    namespace editor
    {
        class Selector
        {
        private:
            FrameBuffer* SelectorFrameBuffer = nullptr;

        private:
            GameObject* activeGameObject = nullptr;

        public:
            Selector(uint32 width, uint32 height);
            ~Selector();

        public:
            void OnMouseDrag();
            void OnMousePress();

        public:
            void Bind();
            void UnBind();
        };
    }
}

#endif