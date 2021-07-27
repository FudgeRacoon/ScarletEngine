#include "scarlet/system//InputManager.hpp"
using namespace scarlet;

SDL_Event InputManager::event;

const byte* InputManager::keyboardStates = nullptr;
byte* InputManager::prevKeyboardStates = nullptr;
int InputManager::keyboardStatesLength;

uint32 InputManager::mouseState;
uint32 InputManager::prevMouseState;

int InputManager::mousePosX;
int InputManager::mousePosY;
int InputManager::prevMousePosX;
int InputManager::prevMousePosY;
int InputManager::mouseScrollDelta;

void InputManager::OnInit()
{
    keyboardStates = SDL_GetKeyboardState(&keyboardStatesLength);
    prevKeyboardStates = new byte[keyboardStatesLength];
}
void InputManager::OnEvent()
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
void InputManager::OnFrameEnd()
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
    uint32 mask = 0;

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
    uint32 mask = 0;

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
    uint32 mask = 0;

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