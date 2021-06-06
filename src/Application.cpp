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

real vertices[] = 
{   
    //Position            //Color
    -100.0f, -100.0f, 0.0f,   1.0f, 0.0f, 0.0f, 1.0f,   //0
     100.0f, -100.0f, 0.0f,   0.0f, 1.0f, 0.0f, 1.0f,   //1
     100.0f,  100.0f, 0.0f,   0.0f, 0.0f, 1.0f, 1.0f,   //2
    -100.0f,  100.0f, 0.0f,   1.0f, 1.0f, 1.0f, 1.0f,   //3
};

uint32 indices[] = 
{
    0, 1, 2,
    2, 3, 0
};

Camera* camera = nullptr;

const VertexArray* vertexArray = nullptr;
const IndexBuffer* indexBuffer = nullptr;
const Shader* shader = nullptr;

void Application::Setup()
{
    Window::Get()->Init("Scarlet Engine", 800, 600, false);
    std::cout << Window::Get()->GetGLVersion() << '\n';
    
    camera = new Camera();

    vertexArray = new VertexArray();

    VertexBuffer vertexBuffer(vertices, sizeof(vertices));

    VertexBufferLayout layout;
    layout.Push<real>(3, false);
    layout.Push<real>(4, false);

    vertexArray->AddBuffer(vertexBuffer, layout);

    indexBuffer = new IndexBuffer(indices, sizeof(indices));

    shader = new Shader("assets\\shaders\\vertex.shader", "assets\\shaders\\fragment.shader");
}

void Application::Update()
{
    Renderer::Get()->Render(*camera, vertexArray, indexBuffer, shader);
}