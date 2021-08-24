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

    Logger::OnInit();
    Logger::Configure(LoggerConfig::SCARLET_ENABLE_LOGGER);
    
    Window::OnInit("Scarlet Engine");
    Window::SetVSync(true);
    
    GraphicsContext::OnInit();
    GraphicsContext::SetViewPort(0, 0, Window::GetWidth(), Window::GetHeight());
    GraphicsContext::SetBlendingFunction(GraphicsBlendFunction::SCARLET_SRC_ALPHA, GraphicsBlendFunction::SCARLET_ONE_MINUS_SRC_ALPHA);
    GraphicsContext::SetClearColor(Color(22, 22, 22));
    GraphicsContext::EnableBlending(true);

    AssetManager::OnInit();
    Renderer::OnInit();
    InputManager::OnInit();
    ImGuiManager::OnInit();

    this->OnInit();
    
    while(Window::IsRunning())
    {
        Time::OnUpdate();

        if(Time::GetDeltaTime() >= (1.0 / 240.0))
        {
            double lag = Time::GetDeltaTime() - (1.0 / 240.0);
            if(lag >= 0.004)
                Logger::LogWarning("%.2fms lag has occured.", lag * 1000.0);

            InputManager::OnEvent();

            this->OnUpdate();

            GraphicsContext::SwapBuffers();

            InputManager::OnFrameEnd();
            
            Time::OnFrameEnd();
        }
    }

    Logger::CreateLogFile();

    ImGuiManager::OnShutDown();
    Renderer::OnShutDown();
    AssetManager::OnShutDown();
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