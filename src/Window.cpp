#include "core/Window.hpp"
#include <windows.h>
using namespace scarlet;

Window* Window::Get()
{
    static Window* instance  = new Window();
    return instance;
}
int Window::Init(std::string title, int width, int height, bool fullscreen)
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 4);
        std::cerr << "[ERROR]: Failed to initialize SDL2" << '\n';
        SetConsoleTextAttribute(hConsole, 7);
        return EXIT_FAILURE;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    this->width = width;
    this->height = height;
    this->window = SDL_CreateWindow
    (
        title.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        this->width, 
        this->height,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
    );

    SDL_GL_SetSwapInterval(1);
    this->context = SDL_GL_CreateContext(this->window);

    glewExperimental = true;
    if(glewInit() != 0)
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 4);
        std::cerr << "[ERROR]: Failed to initialize SDL2" << '\n';
        SetConsoleTextAttribute(hConsole, 7);
        SDL_DestroyWindow(this->window);
        SDL_Quit();
        return EXIT_FAILURE;
    }

    glViewport(0, 0, this->width, this->height);

    this->running = true;
    
    return EXIT_SUCCESS;
}

std::string Window::GetTitle()
{
    return this->title;
}
void Window::SetTitle(std::string value)
{
    this->title = value;
    SDL_SetWindowTitle(this->window, value.c_str());
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
std::string Window::GetGLVersion()
{
    std::string title = "";
    const unsigned char* version = glGetString(GL_VERSION);

    for(int i = 0; version[i] != '\0'; i++)
        title.push_back(version[i]);

    return title;
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
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}