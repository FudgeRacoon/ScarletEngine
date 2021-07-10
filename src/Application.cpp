#include "core/ScarletEngine.hpp"
#include "states/Editor.hpp"
#include "states/Game.hpp"
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

    ImGuiLayer::Init();

    while(Window::Get()->Running())
    {
        Time::Update();

        if(Time::GetDeltaTime() >= 1.0 / Time::FRAME_RATE_TARGET)
        {
            Time::CalculateLag();

            InputManager::Update();
            ImGuiLayer::OnEvent(InputManager::GetSDLEvent());

            Renderer::Get()->ClearBuffers();

            this->Update();

            ImGuiLayer::Render();

            Renderer::Get()->SwapBuffers();

            InputManager::End();

            Time::Reset();
        }
    }

    ImGuiLayer::Release();
    Window::Get()->Release();
}

void Application::Setup()
{
    Window::Get()->Init("Scarlet Engine", 800, 600, false);
    std::cout << Window::Get()->GetGLVersion() << '\n';
    
    StateManager::AddState("Editor", new Editor());
    StateManager::AddState("Game", new Game());

    StateManager::ChangeState("Editor");
}

void Application::Update()
{
    StateManager::UpdateState();
}