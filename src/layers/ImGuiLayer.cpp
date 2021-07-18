#include "core/layers/ImGuiLayer.hpp"
using namespace scarlet;

ImGuiWindow::ImGuiWindow(std::string title)
{
    this->title = title;
}

std::map<std::string, ImGuiWindow*> ImGuiLayer::imguiWindows;

void ImGuiLayer::OnAttach()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; 

    ImGui::StyleColorsDark();

    ImGui_ImplSDL2_InitForOpenGL(Window::Get()->GetSDLWindow(), Window::Get()->GetSDLWindowContext());
    ImGui_ImplOpenGL3_Init("#version 330 core");
}
void ImGuiLayer::OnEvent(SDL_Event* event)
{
    ImGui_ImplSDL2_ProcessEvent(event);
}
void ImGuiLayer::OnDetach()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}

ImGuiWindow* ImGuiLayer::AddWindow(ImGuiWindow* window)
{
    imguiWindows.insert(std::make_pair(window->GetTitle(), window));
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

void ImGuiLayer::OnRender()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    for(std::pair<std::string, ImGuiWindow*> imguiWindow : imguiWindows)
        imguiWindow.second->OnUpdate();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}