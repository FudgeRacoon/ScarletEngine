#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "core/Window.hpp"
#include "core/Time.hpp"
#include "core/manager/InputManager.hpp"

#define APP scarlet::Application::Get()

namespace scarlet
{
    class Application
    {
    private:
        Application() = default;
        Application(const Application& application) = delete;

    public:
        static Application* Get();

    public:
        void Run(int argc, char* argv[]);

    private:
        void Setup();
        void Update();
    };
}

#endif