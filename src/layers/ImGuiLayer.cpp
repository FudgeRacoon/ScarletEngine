#include "core/layers/ImGuiLayer.hpp"
using namespace scarlet;

ImGuiWindow::ImGuiWindow(std::string title)
{
    this->title = title;
}

std::map<std::string, ImGuiWindow*> ImGuiLayer::imguiWindows;

void ImGuiLayer::Init()
{
    //Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    //Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; 

    //Setup Dear ImGui style
    ImGui::StyleColorsDark();

    //Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForOpenGL(Window::Get()->GetSDLWindow(), Window::Get()->GetSDLWindowContext());
    ImGui_ImplOpenGL3_Init("#version 330 core");
}
void ImGuiLayer::Release()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}

ImGuiWindow* ImGuiLayer::AddWindow(ImGuiWindow* window)
{
    imguiWindows.insert(std::make_pair(window->title, window));
    return window;
}
void ImGuiLayer::RemoveWindow(std::string title)
{
    std::map<std::string, ImGuiWindow*>::iterator it;

    it = imguiWindows.find(title);
    if(it == imguiWindows.end())
    {
        Logger::LogError("No imgui window exists with that name.");
        return;
    }

    imguiWindows.erase(it);
    delete it->second;
}

void ImGuiLayer::Render()
{
    //Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    for(std::pair<std::string, ImGuiWindow*> imguiWindow : imguiWindows)
        imguiWindow.second->Update();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}