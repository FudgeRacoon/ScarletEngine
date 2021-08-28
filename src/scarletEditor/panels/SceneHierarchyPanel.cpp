#include "scarletEditor/panels/SceneHierarchyPanel.hpp"
using namespace scarlet;

#include "scarlet/core/logger/Logger.hpp"

SceneHierarchyPanel::SceneHierarchyPanel() : ImGuiPanel("Scene Hierarchy")
{
    this->selectedContext = nullptr;
}

GameObject* SceneHierarchyPanel::GetSelectedContext()
{
    return this->selectedContext;
}

void SceneHierarchyPanel::DrawEntityNode(GameObject* entity)
{
    std::string& name = entity->GetComponent<Tag>()->name;
    ImGuiTreeNodeFlags flags = ((this->selectedContext == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
    
    bool opened = ImGui::TreeNodeEx((void*)entity->GetInstanceId(), flags, name.c_str());
    
    if(ImGui::IsItemClicked())
        this->selectedContext = entity;
    
    if(opened)
        ImGui::TreePop();
}

void SceneHierarchyPanel::OnUpdate()
{   
    ImGui::Begin(this->title.c_str());

    for(auto entity : EditorSceneManager::Get()->GetActiveScene()->GetEntities())
        if(entity.second)
            DrawEntityNode(entity.second);

    if(InputManager::GetMouseButtonDown(0) && ImGui::IsWindowHovered())
        this->selectedContext = nullptr;

    ImGui::End();
}