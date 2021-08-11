#ifndef CAMERACONTROLLER_HPP
#define CAMERACONTROLLER_HPP

#include "scarlet/system/InputManager.hpp"

#include "scarlet/graphics/camera/Camera.hpp"

#include "scarlet/math/Vector2.hpp"

namespace scarlet
{
    namespace editor
    {
        class CameraController
        {    
        public:
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
            void OnMouseDown();
            void OnMouseScroll();
        };
    }
}

#endif