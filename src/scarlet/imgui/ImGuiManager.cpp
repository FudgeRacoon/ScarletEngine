#include "scarlet/imgui/ImGuiManager.hpp"
using namespace scarlet;

std::map<std::string, ImGuiPanel*> ImGuiManager::ImGuiPanels;

void ImGuiManager::OnInit()
{
    Logger::LogInfo("Intitializing ImGui Subsystem...");

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; 

    ImGui::StyleColorsDark();

    ImGui_ImplSDL2_InitForOpenGL(Window::GetSDLWindow(), Window::GetSDLWindowContext());
    ImGui_ImplOpenGL3_Init("#version 330 core");
}
void ImGuiManager::OnEvent(SDL_Event* event)
{
    ImGui_ImplSDL2_ProcessEvent(event);
}
void ImGuiManager::OnRender()
{   
    static bool dockspaceEnabled = true;
    static bool opt_fullscreen = true;
    static bool opt_padding = false;
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    if (opt_fullscreen)
    {
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    }
    else
    {
        dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
    }

    if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
        window_flags |= ImGuiWindowFlags_NoBackground;

    if (!opt_padding)
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    
    ImGui::Begin("Scarlet Engine", &dockspaceEnabled, window_flags);
    
    if (!opt_padding)
        ImGui::PopStyleVar();

    if (opt_fullscreen)
        ImGui::PopStyleVar(2);

    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        ImGuiID dockspace_id = ImGui::GetID("Dockspace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
    }

    if (ImGui::BeginMenuBar())
    {
        if(ImGui::BeginMenu("File"))
        {   
            if(ImGui::MenuItem("Open"));
            
            if(ImGui::MenuItem("Save"));

            if(ImGui::MenuItem("Exit"))
                Window::Quit();

            ImGui::EndMenu();
        }
        
        ImGui::EndMenuBar();
    }

    for(std::pair<std::string, ImGuiPanel*> ImGuiPanel : ImGuiPanels)
        ImGuiPanel.second->OnUpdate();

    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
void ImGuiManager::OnShutDown()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}

ImGuiPanel* ImGuiManager::AddPanel(ImGuiPanel* panel)
{
    ImGuiPanels.insert(std::make_pair(panel->GetTitle(), panel));
    return panel;
}
ImGuiPanel* ImGuiManager::GetPanel(std::string title)
{
    auto it = ImGuiPanels.find(title);
    if(it == ImGuiPanels.end())
    {
        Logger::LogError("No imgui window exists with that name.");
        return nullptr;
    }

    return it->second;
}
void ImGuiManager::RemovePanel(std::string title)
{
    auto it = ImGuiPanels.find(title);
    if(it == ImGuiPanels.end())
    {
        Logger::LogError("No imgui window exists with that name.");
        return;
    }

    delete it->second;
    ImGuiPanels.erase(it);
}
