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

    //Create window and set up scenes
    this->Setup();

    while(Window::Get()->Running())
    {
        //Calculate dt between current and previous frame
        Time::Update();

        //Check if dt is larger than or equal the target frame rate dt
        if(Time::GetDeltaTime() >= 1.0f / Time::FRAME_RATE_TARGET)
        {
            Time::CalculateLag();

            //Poll events
            InputManager::Update();

            //Clear opengl buffers
            Renderer::Get()->ClearBuffers();

            //Update the current scene
            this->Update();

            //Display the back buffer
            Renderer::Get()->SwapBuffers();

            //Store previous key and mouse states for next frame
            InputManager::End();

            //Save the duration of current of frame
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