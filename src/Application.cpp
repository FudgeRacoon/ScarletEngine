#include "core/ScarletEngine.hpp"
#include "scenes/Editor.hpp"
using namespace scarlet;

Application* Application::Get()
{
    static Application* instance = new Application();
    return instance;
}

void Application::Run(int argc, char* argv[])
{
    InputManager::Init();

    this->Setup();

    Time::Reset();

    while(Window::Get()->Running())
    {
        Time::Update();

        if(Time::GetDeltaTime() >= 1.0f / Time::FRAME_RATE_TARGET)
        {
            Time::CalculateLag();

            InputManager::Update();

            Renderer::Get()->ClearBuffers();

            this->Update();

            Renderer::Get()->SwapBuffers();

            InputManager::End();

            Time::Reset();
        }
    }

    Window::Get()->Release();
}

void Application::Setup()
{
    Window::Get()->Init("Scarlet Engine", 800, 600, false);
    std::cout << Window::Get()->GetGLVersion() << '\n';
    
    SceneManager::AddScene("Editor", new Editor());
    SceneManager::ChangeScene("Editor");
}

void Application::Update()
{
    SceneManager::UpdateScene();
}