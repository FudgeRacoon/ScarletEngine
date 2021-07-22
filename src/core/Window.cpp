#include "scarlet/core/Window.hpp"
using namespace scarlet;

#include "scarlet/utils/Logger.hpp"

std::string Window::GetTitle()
{
    return this->title;
}
int Window::GetWidth()
{
    return this->width;
}
int Window::GetHeight()
{
    return this->height;
}
SDL_Window* Window::GetSDLWindow()
{
    return this->window;
}
SDL_GLContext Window::GetSDLWindowContext()
{
    return this->context;
}

void Window::SetTitle(std::string value)
{
    this->title = value;
    SDL_SetWindowTitle(this->window, value.c_str());
}

Window* Window::Get()
{
    static Window* instance  = new Window();
    return instance;
}
int Window::Init(std::string title, int width, int height, bool fullscreen)
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        Logger::LogFatal("Cannot initialize SDL2 window");
        return EXIT_FAILURE;
    }

    //Set OpenGL version and compatibility options
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    //Set up window for fullscreen or windowed mode
    if(fullscreen)
    {
        SDL_DisplayMode displayMode;
        SDL_GetCurrentDisplayMode(0, &displayMode);
        this->width = displayMode.w;
        this->height = displayMode.h;
    }
    else
    {
        this->width = width;
        this->height = height;
    }
    
    this->window = SDL_CreateWindow
    (
        title.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        this->width, 
        this->height,
        fullscreen ? SDL_WINDOW_OPENGL | SDL_WINDOW_MAXIMIZED : SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
    );

    //Create OpenGL rendering context for current this window
    //and Set the swap interval
    this->context = SDL_GL_CreateContext(this->window);

    glewExperimental = true;
    if(glewInit() != 0)
    {
        Logger::LogFatal("Cannot initialize Glew");
        SDL_DestroyWindow(this->window);
        SDL_Quit();
        return EXIT_FAILURE;
    }
    
    this->running = true;
    
    return EXIT_SUCCESS;
}

void Window::EnableVSync(bool value)
{
    switch(value)
    {
        case true:  SDL_GL_SetSwapInterval(1); break;
        case false: SDL_GL_SetSwapInterval(0); break;
    }
}

bool Window::Running()
{
    return this->running;
}

void Window::Quit()
{
    this->running = false;
}
void Window::Release()
{
    SDL_GL_DeleteContext(this->context);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}