#ifndef APPLICATION_HPP
#define APPLICATION_HPP

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
        void OnInit();
        void OnUpdate();
    };
}

#endif