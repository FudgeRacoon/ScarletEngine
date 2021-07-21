#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <iostream>
#include <string>

#include "GL/glew.h"

#include "SDL2/SDL.h"

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
        std::string GetTitle();
        int GetWidth();
        int GetHeight();
        SDL_Window* GetSDLWindow();
        SDL_GLContext GetSDLWindowContext();
    
    public:
        void SetTitle(std::string value);

    public:
        static Window* Get();
        int Init(std::string title, int width, int height, bool fullscreen);
    
    public:
        void EnableVSync(bool value);

    public:
        bool Running();

    public:
        void Quit();
        void Release();
    };
}

#endif