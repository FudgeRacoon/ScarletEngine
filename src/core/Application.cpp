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
    this->OnInit();
    
    while(Window::Get()->Running())
    {
        Time::Elapsed();

        if(Time::GetDeltaTime() >= (1000.0 / Time::FRAME_RATE_TARGET))
        {
            double lag = Time::GetDeltaTime() - (1000.0 / Time::FRAME_RATE_TARGET);
            if(lag >= 4.0)
                Logger::LogWarning("%.2fms lag has occured.", lag);

            InputManager::OnUpdate();

            ImGuiManager::OnEvent(InputManager::GetSDLEvent());

            Renderer::ClearBuffers(RendererBufferType::RENDERER_BUFFER_COLOR);

            this->OnUpdate();

            ImGuiManager::OnRender();

            Renderer::SwapBuffers();

            InputManager::OnFrameEnd();

            Time::Reset();
        }
    }

    Logger::CreateLogFile();

    ImGuiManager::OnDetach();
    Window::Get()->Release();
}

void Application::OnInit()
{   
    Time::Start();

    Window::Get()->Init("Scarlet Engine", 800, 600, true);
    Window::Get()->EnableVSync(false);
    
    InputManager::OnInit();

    Renderer::Init();
    Renderer::SetViewport(0, 0, Window::Get()->GetWidth(), Window::Get()->GetHeight());
    Renderer::SetBlendingFunction(RendererBlendFunc::RENDERER_SRC_ALPHA, RendererBlendFunc::RENDERER_ONE_MINUS_SRC_ALPHA);
    Renderer::SetClearColor(Color(100, 100, 100));
    Renderer::EnableBlending(true);

    ImGuiManager::OnAttach();

    Logger::Configure(LoggerConfig_Flags::DISABLE_LOGGER);

    StateManager::AddState("Editor", new Editor());
    StateManager::AddState("Game", new Game());
    StateManager::ChangeState("Editor");
}

void Application::OnUpdate()
{
    StateManager::UpdateState();
}