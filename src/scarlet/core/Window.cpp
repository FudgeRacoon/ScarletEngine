#include "scarlet/core/Window.hpp"
using namespace scarlet;

#define WINDOW_FLAGS SDL_WINDOW_MAXIMIZED\
    | SDL_WINDOW_RESIZABLE\ 
    | SDL_WINDOW_OPENGL

std::string Window::title;
uint32 Window::width; 
uint32 Window::height;

bool Window::running = false;

SDL_Window* Window::window = nullptr;
SDL_GLContext Window::context;

std::string Window::GetTitle()
{
    return title;
}
uint32 Window::GetWidth()
{
    return width;
}
uint32 Window::GetHeight()
{
    return height;
}
SDL_Window* Window::GetSDLWindow()
{
    return window;
}
SDL_GLContext Window::GetSDLWindowContext()
{
    return context;
}

void Window::SetTitle(std::string value)
{
    title = value;
    SDL_SetWindowTitle(window, value.c_str());
}
void Window::SetWidth(uint32 value)
{
    width = value;
}
void Window::SetHeight(uint32 value)
{
    height = value;
}
void Window::SetVSync(bool value)
{
    switch(value)
    {
        case true:  SDL_GL_SetSwapInterval(1); break;
        case false: SDL_GL_SetSwapInterval(0); break;
    }
}

void Window::OnInit(std::string title)
{
    Logger::LogInfo("Intitializing Window Subsystem...");

    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        Logger::LogFatal("Cannot initialize SDL2 window");
        return;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_DisplayMode displayMode;
    SDL_GetCurrentDisplayMode(0, &displayMode);
    width = displayMode.w;
    height = displayMode.h;
   
    window = SDL_CreateWindow
    (
        title.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width, 
        height,
        WINDOW_FLAGS
    );

    context = SDL_GL_CreateContext(window);

    running = true;
}
void Window::OnShutDown()
{
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

bool Window::IsRunning()
{
    return running;
}

void Window::Quit()
{
    running = false;
}
