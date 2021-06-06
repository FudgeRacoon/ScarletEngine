#include "core/Camera.hpp"
using namespace scarlet;

Camera::Camera()
{
    this->direction = Vector3::FRONT();

    this->left = -Window::Get()->GetWidth() / 2, this->right = Window::Get()->GetWidth() / 2;
    this->bottom = -Window::Get()->GetHeight() / 2, this->top = Window::Get()->GetHeight() / 2;
    this->near = 0.0f, this->far = -100.0f;
}
Camera::Camera(Vector3 position)
{
    this->position = position;

    this->direction = Vector3::FRONT();

    this->left = -Window::Get()->GetWidth() / 2, this->right = Window::Get()->GetWidth() / 2;
    this->bottom = -Window::Get()->GetHeight() / 2, this->top = Window::Get()->GetHeight() / 2;
    this->near = 0.0f, this->far = -100.0f;
}

Matrix4 Camera::GetViewMatrix()
{   
    Matrix4 yaw = Matrix4::Rotate(this->rotation.x, Vector3::RIGHT());
    Matrix4 pitch = Matrix4::Rotate(this->rotation.y, Vector3::UP());
    Matrix4 rotation = yaw * pitch;

    this->direction = (Vector3)(rotation * Vector4(this->front));

    return Matrix4::LookAt(this->position, this->position + this->direction, Vector3::UP());
}
Matrix4 Camera::GetProjectionMatrix()
{
    return Matrix4::Orthographic(this->left, this->right, this->bottom, this->top, this->near, this->far);
}