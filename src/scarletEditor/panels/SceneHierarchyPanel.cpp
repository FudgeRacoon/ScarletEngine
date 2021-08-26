#include "scarletEditor/panels/SceneHierarchyPanel.hpp"
using namespace scarlet;

#include "scarlet/core/logger/Logger.hpp"

SceneHierarchyPanel::SceneHierarchyPanel() : ImGuiPanel("Scene Hierarchy")
{
    this->selectedContext = nullptr;
}

void SceneHierarchyPanel::DrawEntityNode(GameObject* entity)
{
    std::string& tag = entity->GetComponent<Tag>()->tag;
    ImGuiTreeNodeFlags flags = ((this->selectedContext == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
    
    bool opened = ImGui::TreeNodeEx((void*)entity->GetInstanceId(), flags, tag.c_str());

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

    ImGui::End();
}