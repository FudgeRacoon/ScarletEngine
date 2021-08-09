#include "scarlet/imgui/InspectorWindow.hpp"
using namespace scarlet;

InspectorWindow::InspectorWindow() : ImGuiWindow("Inspector")
{
    this->componentMenus.push_back(new TransformMenu());
    this->componentMenus.push_back(new SpriteRendererMenu());
}
InspectorWindow::~InspectorWindow()
{
    for(ComponentMenu* componentMenu : componentMenus)
        delete componentMenu;
}

ComponentMenu* InspectorWindow::GetComponentMenu(std::string title)
{
    for(ComponentMenu* componentMenu : this->componentMenus)
        if(componentMenu->GetTitle() == title)
            return componentMenu;

    Logger::LogWarning("ComponentMenu does not exist.");
    return nullptr; 
}

void InspectorWindow::OnUpdate()
{
    ImGui::Begin(this->title.c_str()); 
            
    for(ComponentMenu* componentMenu : componentMenus)
    {
        if(componentMenu->GetActive())
            componentMenu->Update();
    }
    
    ImGui::End();
}