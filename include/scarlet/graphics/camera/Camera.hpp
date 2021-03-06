#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "scarlet/core/Window.hpp"
#include "scarlet/core/math/Math.hpp"
#include "scarlet/core/math/Vector3.hpp"
#include "scarlet/core/math/Matrix4.hpp"

#include "scarlet/graphics/GraphicsContext.hpp"

#include "scarlet/input/InputManager.hpp"

namespace scarlet
{   
    class Camera
    {
    public:
        Vector3 position;
        Vector3 rotation;

    public:
        float rightPlane, leftPlane;
        float bottomPlane, topPlane;
        float nearPlane, farPlane;

    private:
        float size;
        Vector3 direction;
        const Vector3 front = Vector3::FRONT();

    private:
        bool mouseClickedFlag = true;
        Vector2 mousePositionBuffer;

    public:
        Camera();
        Camera(Vector3 position);

    public:
        Vector3 ScreenToWorldPoint(Vector3 point);

    public:
        float GetSize();

    public:
        Vector3 GetDirection();
        Matrix4 GetViewMatrix();
        Matrix4 GetProjectionMatrix(); 

    public:
        void SetSize(float size);
    };
}

#endif