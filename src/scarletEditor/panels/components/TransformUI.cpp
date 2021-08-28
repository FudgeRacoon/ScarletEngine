#include "scarletEditor/panels/components/TransformUI.hpp"
using namespace scarlet;

TransformUI::TransformUI() : ComponentUI("Transform")
{
    this->hierarchyPanel = dynamic_cast<SceneHierarchyPanel*>(ImGuiManager::GetPanel("Scene Hierarchy"));
}

void TransformUI::AddVerticalSpacing(float height)
{
    ImGui::PushStyleVar(ImGuiStyleVar_::ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 0.0f));
    ImGui::Dummy(ImVec2(0, height));
    ImGui::PopStyleVar();
}
void TransformUI::DrawVector3Control(std::string label, Vector3& value, float resetValue, float columnWidth)
{
    ImGui::PushID(label.c_str());

    ImGui::Columns(2, nullptr, false);
    ImGui::SetColumnWidth(0, columnWidth);

    ImGui::Text(label.c_str());
    ImGui::NextColumn();

    ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
    ImGui::PushStyleVar(ImGuiStyleVar_::ImGuiStyleVar_ItemSpacing, ImVec2(5.0f, 0.0f));

    float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
    ImVec2 buttonSize = ImVec2(lineHeight + 3.0f, lineHeight);

    {
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.8f, 0.1f, 0.15f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.9f, 0.2f, 0.2f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.8f, 0.1f, 0.15f, 1.0f));

        ImGui::PushStyleVar(ImGuiStyleVar_::ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 0.0f));

        if(ImGui::Button("x", buttonSize))
            value.x = resetValue;

        ImGui::PopStyleColor(3);

        ImGui::SameLine();
        ImGui::DragFloat("##x", &value.x, 0.5f, 0.0f, 0.0f, "%.2f");
        ImGui::PopItemWidth();

        ImGui::PopStyleVar();
    }

    ImGui::SameLine();

    {
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.7f, 0.2f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.8f, 0.3f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.2f, 0.7f, 0.2f, 1.0f));

        ImGui::PushStyleVar(ImGuiStyleVar_::ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 0.0f));

        if(ImGui::Button("y", buttonSize))
            value.y = resetValue;

        ImGui::PopStyleColor(3);


        ImGui::SameLine();
        ImGui::DragFloat("##y", &value.y, 0.5f, 0.0f, 0.0f, "%.2f");
        ImGui::PopItemWidth();

        ImGui::PopStyleVar();
    }

    ImGui::SameLine();

    {   
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.1f, 0.25f, 0.8f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.2f, 0.35f, 0.9f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.1f, 0.25f, 0.8f, 1.0f));

        ImGui::PushStyleVar(ImGuiStyleVar_::ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 0.0f));

        if(ImGui::Button("z", buttonSize))
            value.z = resetValue;

        ImGui::PopStyleColor(3);

        ImGui::SameLine();
        ImGui::DragFloat("##z", &value.z, 0.5f, 0.0f, 0.0f, "%.2f");
        ImGui::PopItemWidth();

        ImGui::PopStyleVar();
    }

    ImGui::PopStyleVar();

    ImGui::Columns(1, nullptr, false);

    ImGui::PopID();
}

void TransformUI::OnCheck()
{
    GameObject* entity = this->hierarchyPanel->GetSelectedContext();

    if(!entity)
        this->active = false;
    else
    {
        this->transformComponent = entity->GetComponent<Transform>();

        if(!this->transformComponent)
            this->active = false;
        else
            this->active = true;
    }
}
void TransformUI::OnUpdate()
{
    if(ImGui::CollapsingHeader(this->title.c_str(), ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_DefaultOpen))
    { 
        Vector3 rotation;
        rotation.x = Math::RadToDegree(this->transformComponent->rotation.x);
        rotation.y = Math::RadToDegree(this->transformComponent->rotation.y);
        rotation.z = Math::RadToDegree(this->transformComponent->rotation.z);
        
        DrawVector3Control("Position", this->transformComponent->position);

        AddVerticalSpacing(5.0f);    

        DrawVector3Control("Rotation", rotation);

        AddVerticalSpacing(5.0f);

        DrawVector3Control("Scale", this->transformComponent->scale, 1.0f);

        this->transformComponent->rotation.x = Math::DegreeToRad(rotation.x);
        this->transformComponent->rotation.y = Math::DegreeToRad(rotation.y);
        this->transformComponent->rotation.z = Math::DegreeToRad(rotation.z);
    }
}