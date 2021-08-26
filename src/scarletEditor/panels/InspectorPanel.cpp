#include "scarletEditor/panels/InspectorPanel.hpp"
using namespace scarlet;

InspectorPanel::InspectorPanel() : ImGuiPanel("Inspector")
{
    this->components.push_back(new TransformUI());
    this->components.push_back(new SpriteRendererMenu());
}
InspectorPanel::~InspectorPanel()
{
    for(ComponentUI* component : components)
        delete component;
}

ComponentUI* InspectorPanel::GetComponentUI(std::string title)
{
    for(ComponentUI* component : this->components)
        if(component->title == title)
            return component;

    Logger::LogWarning("ComponentUI does not exist.");
    return nullptr; 
}

void InspectorPanel::OnUpdate()
{
    ImGui::Begin(this->title.c_str()); 
            
    for(ComponentUI* component : components)
    {
        if(component->active)
            component->OnUpdate();
    }
    
    ImGui::End();
}