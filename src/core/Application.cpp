#include "scarlet/ScarletEngine.hpp"
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
    Time::OnInit();

    this->Setup();
    
    InputManager::Init();
    
    ImGuiManager::OnAttach();

    while(Window::Get()->Running())
    {
        Time::CalculateTimeElapsed();

        if(Time::GetDeltaTime() >= (1000.0 / Time::FRAME_RATE_TARGET))
        {
            double lag = Time::GetDeltaTime() - (1000.0 / Time::FRAME_RATE_TARGET);
            if(lag >= 4.0)
                Logger::LogWarning("%.2fms lag has occured.", lag);

            InputManager::Update();
            ImGuiManager::OnEvent(InputManager::GetSDLEvent());

            Renderer::ClearBuffers();

            this->Update();

            ImGuiManager::OnRender();

            Renderer::SwapBuffers();

            InputManager::End();

            Time::OnFrameEnd();
        }
    }

    Logger::CreateLogFile();

    ImGuiManager::OnDetach();
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