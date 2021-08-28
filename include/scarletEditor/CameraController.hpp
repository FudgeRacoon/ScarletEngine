#ifndef CAMERACONTROLLER_HPP
#define CAMERACONTROLLER_HPP

#include "scarlet/core/math/Vector2.hpp"

#include "scarlet/input/InputManager.hpp"

#include "scarlet/graphics/camera/Camera.hpp"

namespace scarlet
{
    namespace editor
    {
        class CameraController
        {    
        private:
            Camera* controlledCamera;
    
        private:
            bool mousePressed;
            Vector2 prevMousePosition;
    
        private:
            float zoomIntensity;
            float mouseSensitvity;
    
        public:
            CameraController(Camera* camera);
    
        public:
            void SetZoomIntensity(float zoomIntensity);
            void SetMouseSensitvity(float mouseSensitvity);
    
        public:
            void OnResize();
            void OnMouseDown();
            void OnMouseScroll();
        };
    }
}

#endif