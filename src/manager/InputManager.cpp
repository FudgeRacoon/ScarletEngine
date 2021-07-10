#include "core/manager/InputManager.hpp"
using namespace scarlet;

SDL_Event InputManager::event;

const uint8_t* InputManager::keyboardStates = nullptr;
uint8_t* InputManager::prevKeyboardStates = nullptr;
int InputManager::keyboardStatesLength;

uint32_t InputManager::mouseState;
uint32_t InputManager::prevMouseState;

int InputManager::mousePosX;
int InputManager::mousePosY;
int InputManager::prevMousePosX;
int InputManager::prevMousePosY;
int InputManager::mouseScrollDelta;

void InputManager::Init()
{
    keyboardStates = SDL_GetKeyboardState(&keyboardStatesLength);
    prevKeyboardStates = new uint8_t[keyboardStatesLength];
}
void InputManager::Update()
{
    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
        case SDL_QUIT: 
            {
                Window::Get()->Quit();
            } break;
        
        case SDL_MOUSEWHEEL: 
            {
                if(event.wheel.y > 0)
                    mouseScrollDelta = 1;
                else if(event.wheel.y < 0)
                    mouseScrollDelta = -1;
            } break;
        }    
    }

    mouseState = SDL_GetMouseState(&mousePosX, &mousePosY);
}
void InputManager::End()
{
    memcpy(prevKeyboardStates, keyboardStates, keyboardStatesLength);

    mouseScrollDelta = 0;
    prevMousePosX = mousePosX;
    prevMousePosY = mousePosY;
    prevMouseState = mouseState;

}

SDL_Event* InputManager::GetSDLEvent()
{
    return &event;
}

bool InputManager::GetKey(KeyCode code)
{
    return keyboardStates[code];
}
bool InputManager::GetKeyDown(KeyCode code)
{
    return !prevKeyboardStates[code] && keyboardStates[code];
}
bool InputManager::GetKeyUp(KeyCode code)
{
    return prevKeyboardStates[code] && !keyboardStates[code];
}
bool InputManager::GetMouseButton(int button)
{
    uint32_t mask = 0;

    switch(button)
    {
        case 0: mask = SDL_BUTTON_LMASK; break;
        case 1: mask = SDL_BUTTON_MMASK; break;
        case 2: mask = SDL_BUTTON_RMASK; break;
    }

    return mask & mouseState;
}
bool InputManager::GetMouseButtonDown(int button)
{
    uint32_t mask = 0;

    switch(button)
    {
        case 0: mask = SDL_BUTTON_LMASK; break;
        case 1: mask = SDL_BUTTON_MMASK; break;
        case 2: mask = SDL_BUTTON_RMASK; break;
    }

    return !(mask & prevMouseState) && (mask && mouseState);
}
bool InputManager::GetMouseButtonUp(int button)
{
    uint32_t mask = 0;

    switch(button)
    {
        case 0: mask = SDL_BUTTON_LMASK; break;
        case 1: mask = SDL_BUTTON_MMASK; break;
        case 2: mask = SDL_BUTTON_RMASK; break;
    }

    return (mask & prevMouseState) && !(mask && mouseState);
}
Vector2 InputManager::GetMousePosition()
{
    return Vector2(mousePosX, mousePosY);
}
int InputManager::GetMouseScrollDelta()
{
    return mouseScrollDelta;
}
bool InputManager::MouseMoved()
{
    if(prevMousePosX != mousePosX || prevMousePosY != mousePosY)
        return true;
    else    
        return false;
}