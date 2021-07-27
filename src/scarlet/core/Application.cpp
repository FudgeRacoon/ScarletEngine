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

            InputManager::OnEvent();
            ImGuiManager::OnEvent(InputManager::GetSDLEvent());

            GraphicsContext::ClearBuffers(BufferType::SCARLET_BUFFER_COLOR);

            this->OnUpdate();

            ImGuiManager::OnRender();

            GraphicsContext::SwapBuffers();

            InputManager::OnFrameEnd();

            Time::Reset();
        }
    }

    Logger::CreateLogFile();

    ImGuiManager::OnDetach();
    
    DebugRenderer::ShutDown();

    Window::Get()->Release();
}

void Application::OnInit()
{   
    Time::Start();

    Window::Get()->Init("Scarlet Engine", 800, 600, true);
    Window::Get()->EnableVSync(true);
    
    InputManager::OnInit();

    GraphicsContext::Init();
    GraphicsContext::SetViewPort(0, 0, Window::Get()->GetWidth(), Window::Get()->GetHeight());
    GraphicsContext::SetBlendingFunction(BlendFunc::SCARLET_SRC_ALPHA, BlendFunc::SCARLET_ONE_MINUS_SRC_ALPHA);
    GraphicsContext::SetClearColor(Color(22, 22, 22));
    GraphicsContext::EnableBlending(true);

    Renderer::Init();
    DebugRenderer::Init();

    ImGuiManager::OnAttach();

    Logger::Configure(LoggerConfig_Flags::ENABLE_LOGGER);

    StateManager::AddState("Editor", new Editor());
    StateManager::AddState("Game", new Game());
    StateManager::ChangeState("Editor");
}

void Application::OnUpdate()
{
    StateManager::UpdateState();
}