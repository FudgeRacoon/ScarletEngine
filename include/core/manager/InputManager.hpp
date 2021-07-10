#ifndef INPUTMANAGER_HPP
#define INPUTMANAGER_HPP

#include <string.h>
#include "SDL2/SDL.h"
#include "core/Window.hpp"
#include "core/math/Vector2.hpp"

namespace scarlet
{
    enum KeyCode
    {
        A = 4,
        B = 5,
        C = 6,
        D = 7,
        E = 8,
        F = 9,
        G = 10,
        H = 11,
        I = 12,
        J = 13,
        K = 14,
        L = 15,
        M = 16,
        N = 17,
        O = 18,
        P = 19,
        Q = 20,
        R = 21,
        S = 22,
        T = 23,
        U = 24,
        V = 25,
        W = 26,
        X = 27,
        Y = 28,
        Z = 29,

        Keypad1 = 30,
        Keypad2 = 31,
        Keypad3 = 32,
        Keypad4 = 33,
        Keypad5 = 34,
        Keypad6 = 35,
        Keypad7 = 36,
        Keypad8 = 37,
        Keypad9 = 38,
        Keypad0 = 39,

        Return = 40,
        Escape = 41,
        BackSpace = 42,
        Tab = 43,
        Space = 44,

        Minus = 45,
        Equals = 46,
        LeftBracket = 47,
        RightBracket = 48,
        BackSlash = 49,

        F1 = 58,
        F2 = 59,
        F3 = 60,
        F4 = 61,
        F5 = 62,
        F6 = 63,
        F7 = 64,
        F8 = 65,
        F9 = 66,
        F10 = 67,
        F11 = 68,
        F12 = 69,

        LCTRL = 224,
        LSHIFT = 225,
        LALT = 226,
        RCTRL = 228,
        RSHIFT = 229,
        RALT = 230,

        HOME = 74,
        PAGEUP = 75,
        DELETEYY = 76,
        END = 77,
        PAGEDOWN = 78,
        RIGHT = 79,
        LEFT = 80,
        DOWN = 81,
        UP = 82,
    };

    class InputManager
    {
    private:
        InputManager() = delete;
        ~InputManager() = delete;

    private:
        static SDL_Event event;

    private:
        static const uint8_t* keyboardStates;
        static uint8_t* prevKeyboardStates;
        static int keyboardStatesLength;

    private:
        static uint32_t mouseState;
        static uint32_t prevMouseState;

    private:
        static int mousePosX, mousePosY;
        static int prevMousePosX, prevMousePosY;
        static int mouseScrollDelta;

    public:
        static void Init();
        static void Update();
        static void End();

    public:
        static SDL_Event* GetSDLEvent(); 

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