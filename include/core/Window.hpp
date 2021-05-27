#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <iostream>
#include <string>

#include "SDL2/SDL.h"
#include "GL/glew.h"

namespace scarlet
{
    class Window
    {
    private:
        std::string title;
        int width, height;
        bool running;

    private:
        SDL_Window* window;
        SDL_GLContext context;

    private:
        Window() = default;
        Window(const Window& window) = delete;

    public:
        static Window* Get();
        int Init(std::string title, int width, int height, bool fullscreen);

    public:
        std::string GetTitle();
        void SetTitle(std::string value);

    public:
        int GetWidth();
        int GetHeight();

    public:
        SDL_Window* GetSDLWindow();
        SDL_GLContext GetSDLWindowContext();
        std::string GetGLVersion();

    public:
        bool Running();

    public:
        void Quit();
        void Release();
    };
}

#endif