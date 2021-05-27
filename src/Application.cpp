#include "core/ScarletEngine.hpp"
using namespace scarlet;

float vertices[] = 
{   
    //Position      //Color
    -0.5f, -0.5f,   1.0f, 0.0f, 0.0f, 1.0f,   //0
     0.5f, -0.5f,   0.0f, 1.0f, 0.0f, 1.0f,   //1
     0.5f,  0.5f,   0.0f, 0.0f, 1.0f, 1.0f,   //2
    -0.5f,  0.5f,   1.0f, 1.0f, 1.0f, 1.0f,   //3
};

uint32_t indices[] = 
{
    0, 1, 2,
    2, 3, 0
};

VertexArray* vertexArray = nullptr;
IndexBuffer* indexBuffer = nullptr;
Shader* shader = nullptr;

void Application::Setup()
{
    Window::Get()->Init("Scarlet Engine", 800, 600, false);
    std::cout << Window::Get()->GetGLVersion() << '\n';
    
    vertexArray = new VertexArray();

    VertexBuffer vertexBuffer(vertices, sizeof(vertices));

    VertexBufferLayout layout;
    layout.Push<float>(2, false);
    layout.Push<float>(4, false);

    vertexArray->AddBuffer(vertexBuffer, layout);

    indexBuffer = new IndexBuffer(indices, sizeof(indices));

    shader = new Shader("assets\\shaders\\vertex.shader", "assets\\shaders\\fragment.shader");
}

void Application::Update()
{
    shader->Bind();
    vertexArray->Bind();
    indexBuffer->Bind();

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

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

            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            this->Update();

            SDL_GL_SwapWindow(Window::Get()->GetSDLWindow());

            InputManager::End();

            Time::Reset();
        }
    }

    Window::Get()->Release();
}