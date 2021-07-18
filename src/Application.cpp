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
    Time::Init();

    this->Setup();
    
    InputManager::Init();
    
    ImGuiLayer::OnAttach();

    while(Window::Get()->Running())
    {
        Time::Update();

        if(Time::GetDeltaTime() >= (1000.0 / Time::FRAME_RATE_TARGET))
        {
            double lag = Time::GetDeltaTime() - (1000.0 / Time::FRAME_RATE_TARGET);
            if(lag >= 4.0)
                Logger::LogWarning("%.2fms lag has occured.", lag);

            InputManager::Update();
            ImGuiLayer::OnEvent(InputManager::GetSDLEvent());

            Renderer::Get()->ClearBuffers();

            this->Update();

            ImGuiLayer::OnRender();

            Renderer::Get()->SwapBuffers();

            InputManager::End();

            Time::Reset();
        }
    }

    Logger::CreateLogFile();

    ImGuiLayer::OnDetach();
    Window::Get()->Release();
}

void Application::Setup()
{
    Window::Get()->Init("Scarlet Engine", 800, 600, true);
    Window::Get()->EnableVSync(true);
    
    StateManager::AddState("Editor", new Editor());
    StateManager::AddState("Game", new Game());

    StateManager::ChangeState("Editor");
}

void Application::Update()
{
    StateManager::UpdateState();
}