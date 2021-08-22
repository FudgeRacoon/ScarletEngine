#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <iostream>
#include <string>

#include "GL/glew.h"
#include "SDL2/SDL.h"

#include "scarlet/common/Types.hpp"

#include "scarlet/utils/logger/Logger.hpp"

namespace scarlet
{
    class Window
    {
    private:
        static std::string title;
        static uint32 width;
        static uint32 height;

    private:
        static bool running;

    private:
        static SDL_Window*   window;
        static SDL_GLContext context;
    
    private:
        Window() = delete;
        ~Window() = delete;

    public:
        static std::string GetTitle();
        static uint32 GetWidth();
        static uint32 GetHeight();
        static SDL_Window* GetSDLWindow();
        static SDL_GLContext GetSDLWindowContext();
    
    public:
        static void SetTitle(std::string value);
        static void SetWidth(uint32 value);
        static void SetHeight(uint32 value);
        static void SetVSync(bool value);

    public:
        static void OnInit(std::string title);
        static void OnShutDown();
    
    public:
        static bool IsRunning();

    public:
        static void Quit();
    };
}

#endif