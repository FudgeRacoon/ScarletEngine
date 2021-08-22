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
    Time::Start();

    Logger::OnInit();
    Logger::Configure(LoggerConfig::SCARLET_ENABLE_LOGGER);
    
    Window::OnInit("Scarlet Engine");
    Window::SetVSync(true);
    
    GraphicsContext::OnInit();
    GraphicsContext::SetViewPort(0, 0, Window::GetWidth(), Window::GetHeight());
    GraphicsContext::SetBlendingFunction(Graphics_BlendFunction::SCARLET_SRC_ALPHA, Graphics_BlendFunction::SCARLET_ONE_MINUS_SRC_ALPHA);
    GraphicsContext::SetClearColor(Color(22, 22, 22));
    GraphicsContext::EnableBlending(true);

    AssetPool::OnInit();
    Renderer::OnInit();
    InputManager::OnInit();
    ImGuiManager::OnInit();

    this->OnInit();
    
    while(Window::IsRunning())
    {
        Time::Elapsed();

        if(Time::GetDeltaTime() >= (1000.0 / Time::FRAME_RATE_TARGET))
        {
            double lag = Time::GetDeltaTime() - (1000.0 / Time::FRAME_RATE_TARGET);
            if(lag >= 4.0)
                Logger::LogWarning("%.2fms lag has occured.", lag);

            InputManager::OnEvent();

            this->OnUpdate();

            GraphicsContext::SwapBuffers();

            InputManager::OnFrameEnd();

            Time::Reset();
        }
    }

    Logger::CreateLogFile();

    ImGuiManager::OnShutDown();
    Renderer::OnShutDown();
    AssetPool::OnShutDown();
    Window::OnShutDown();
    Logger::OnShutDown();
}

void Application::OnInit()
{   
    StateManager::AddState("Editor", new Editor());
    StateManager::AddState("Game", new Game());
    StateManager::ChangeState("Editor");
}

void Application::OnUpdate()
{
    StateManager::UpdateState();
}