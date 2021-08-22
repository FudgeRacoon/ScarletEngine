#include "scarletEditor/CameraController.hpp"
using namespace scarlet::editor;

CameraController::CameraController(Camera* camera)
{
    this->controlledCamera = camera;

    this->mousePressed = false;

    this->zoomIntensity = 0.05f;
    this->mouseSensitvity = 1.0f;
}

void CameraController::SetZoomIntensity(float zoomIntensity)
{
    this->zoomIntensity = zoomIntensity;
}
void CameraController::SetMouseSensitvity(float mouseSensitvity)
{
    this->mouseSensitvity = mouseSensitvity;
}

void CameraController::OnResize()
{
    this->controlledCamera->leftPlane   = -GraphicsContext::GetViewPort().z / 2; 
    this->controlledCamera->rightPlane  =  GraphicsContext::GetViewPort().z / 2;
    
    this->controlledCamera->bottomPlane = -GraphicsContext::GetViewPort().w / 2; 
    this->controlledCamera->topPlane    =  GraphicsContext::GetViewPort().w / 2;
}
void CameraController::OnMouseDown()
{
    if(InputManager::GetMouseButton(1))
    {
        if(!this->mousePressed)
        {
            this->prevMousePosition = InputManager::GetMousePosition();
            this->mousePressed = true;
        }

        float offsetX = this->prevMousePosition.x - InputManager::GetMousePosition().x;
        float offsetY = this->prevMousePosition.y - InputManager::GetMousePosition().y;

        this->prevMousePosition = InputManager::GetMousePosition();

        this->controlledCamera->position = this->controlledCamera->position + Vector3(
            offsetX * this->mouseSensitvity, -offsetY * this->mouseSensitvity, 0.0f
        );
    }

    if(InputManager::GetMouseButtonUp(1))
        this->mousePressed = false;
}
void CameraController::OnMouseScroll()
{
    if(InputManager::GetMouseScrollDelta() > 0)
    {
        float cameraSize = this->controlledCamera->GetSize();
        this->controlledCamera->SetSize(cameraSize -= this->zoomIntensity);
    }
    else if(InputManager::GetMouseScrollDelta() < 0)
    {
        float cameraSize = this->controlledCamera->GetSize();
        this->controlledCamera->SetSize(cameraSize += this->zoomIntensity);
    }
}