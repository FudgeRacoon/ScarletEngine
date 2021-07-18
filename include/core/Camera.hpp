#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "core/Window.hpp"

#include "core/manager/InputManager.hpp"

#include "core/math/Math.hpp"
#include "core/math/Vector3.hpp"
#include "core/math/Matrix4.hpp"

namespace scarlet
{   
    class Camera
    {
    public:
        Vector3 position;
        Vector3 rotation;

    private:
        float size;
        float rightPlane, leftPlane;
        float bottomPlane, topPlane;
        float nearPlane, farPlane;

    private:
        Vector3 direction;

    private:
        const Vector3 front = Vector3::FRONT();

    private:
        bool mouseClickedFlag = true;
        Vector2 mousePositionBuffer;

    public:
        Camera();
        Camera(Vector3 position);

    public:
        void ProcessMouseMovement();

    public:
        Vector3 ScreenToWorldPoint(Vector3 point);

    public:
        float GetSize();
        Vector3 GetDirection();
        Matrix4 GetViewMatrix();
        Matrix4 GetProjectionMatrix(); 

    public:
        void SetSize(float size);
    };
}

#endif