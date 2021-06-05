#include "core/ScarletEngine.hpp"
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

float counter = 0.0f;
float vertices[] = 
{   
    //Position            //Color
    -100.0f, -100.0f, 0.0f,   1.0f, 0.0f, 0.0f, 1.0f,   //0
     100.0f, -100.0f, 0.0f,   0.0f, 1.0f, 0.0f, 1.0f,   //1
     100.0f,  100.0f, 0.0f,   0.0f, 0.0f, 1.0f, 1.0f,   //2
    -100.0f,  100.0f, 0.0f,   1.0f, 1.0f, 1.0f, 1.0f,   //3
};

uint32_t indices[] = 
{
    0, 1, 2,
    2, 3, 0
};

const VertexArray* vertexArray = nullptr;
const IndexBuffer* indexBuffer = nullptr;
const Shader* shader = nullptr;

void Application::Setup()
{
    Window::Get()->Init("Scarlet Engine", 800, 600, false);
    std::cout << Window::Get()->GetGLVersion() << '\n';
    
    vertexArray = new VertexArray();

    VertexBuffer vertexBuffer(vertices, sizeof(vertices));

    VertexBufferLayout layout;
    layout.Push<float>(3, false);
    layout.Push<float>(4, false);

    vertexArray->AddBuffer(vertexBuffer, layout);

    indexBuffer = new IndexBuffer(indices, sizeof(indices));

    shader = new Shader("assets\\shaders\\vertex.shader", "assets\\shaders\\fragment.shader");
}

void Application::Update()
{
    Renderer::Get()->Render(vertexArray, indexBuffer, shader);
}