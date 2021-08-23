#ifndef INPUTMANAGER_HPP
#define INPUTMANAGER_HPP

#include <string.h>

#include "SDL2/SDL.h"

#include "scarlet/core/Window.hpp"
#include "scarlet/core/Types.hpp"

#include "scarlet/input/KeyCode.hpp"

#include "scarlet/core/math/Vector2.hpp"

namespace scarlet
{
    class InputManager
    {
    private:
        InputManager() = delete;
        ~InputManager() = delete;

    private:
        static SDL_Event event;

    private:
        static const byte* keyboardStates;
        static byte* prevKeyboardStates;
        static int keyboardStatesLength;

    private:
        static uint32 mouseState;
        static uint32 prevMouseState;

    private:
        static int mousePosX, mousePosY;
        static int prevMousePosX, prevMousePosY;
        static int mouseScrollDelta;

    public:
        static SDL_Event* GetSDLEvent();

    public:
        static void OnInit();
        static void OnEvent();
        static void OnFrameEnd();

    public:
        static bool GetKey(KeyCode code);
        static bool GetKeyDown(KeyCode code);
        static bool GetKeyUp(KeyCode code);
        static bool GetMouseButton(int button);
        static bool GetMouseButtonDown(int button);
        static bool GetMouseButtonUp(int button);
        static Vector2 GetMousePosition();
        static int GetMouseScrollDelta();
        static bool MouseMoved();
    };
}

#endif