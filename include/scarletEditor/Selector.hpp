#ifndef Selector_HPP
#define Selector_HPP

#include "scarlet/common/Types.hpp"

#include "scarlet/entity/GameObject.hpp"

#include "scarlet/system/InputManager.hpp"

#include "scarlet/utils/logger/Logger.hpp"

#include "scarlet/graphics/GraphicsContext.hpp"
#include "scarlet/graphics/FrameBuffer.hpp"

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