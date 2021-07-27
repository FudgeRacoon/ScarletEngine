#include "scarlet/graphics/camera/Camera.hpp"
using namespace scarlet;

Camera::Camera()
{
    this->size        =  1.0f;
    
    this->direction   =  Vector3::FRONT();

    this->leftPlane   = -GraphicsContext::GetViewPort().z / 2; 
    this->rightPlane  =  GraphicsContext::GetViewPort().z / 2;
    
    this->bottomPlane = -GraphicsContext::GetViewPort().w / 2; 
    this->topPlane    =  GraphicsContext::GetViewPort().w / 2;
    
    this->nearPlane   =  0.0f; 
    this->farPlane    = -100.0f;
}
Camera::Camera(Vector3 position)
{
    this->position    =  position;

    this->size        =  1.0f;
    
    this->direction   =  Vector3::FRONT();

    this->leftPlane   = -Window::Get()->GetWidth() / 2; 
    this->rightPlane  =  Window::Get()->GetWidth() / 2;
    
    this->bottomPlane = -Window::Get()->GetHeight() / 2; 
    this->topPlane    =  Window::Get()->GetHeight() / 2;
    
    this->nearPlane   =  0.0f; 
    this->farPlane    = -100.0f;
}

Vector3 Camera::ScreenToWorldPoint(Vector3 point)
{
    int width = Window::Get()->GetWidth();
    int height = Window::Get()->GetHeight();
    
    float x = point.x / width;
    float y = (height - point.y) / height;

    Vector4 normalizedPoint;
    normalizedPoint.x = (x * 2) - 1;
    normalizedPoint.y = (y * 2) - 1;

    Matrix4 invProj = Matrix4::Inverse(this->GetProjectionMatrix());
    Matrix4 invView = Matrix4::Inverse(this->GetViewMatrix());
    Matrix4 invWorld = invView * invProj;

    return invWorld * normalizedPoint;
}

float Camera::GetSize()
{
    return this->size;
}
Vector3 Camera::GetDirection()
{
    return this->direction;
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
    return Matrix4::Orthographic
    (
        this->leftPlane * this->size, 
        this->rightPlane * this->size, 
        this->bottomPlane * this->size, 
        this->topPlane * this->size, 
        this->nearPlane, 
        this->farPlane
    );
}

void Camera::SetSize(float size)
{
    this->size = size;
}