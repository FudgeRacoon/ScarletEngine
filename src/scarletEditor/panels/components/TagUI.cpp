#include "scarletEditor/panels/components/TagUI.hpp"
using namespace scarlet;

TagUI::TagUI() : ComponentUI("Tag")
{
    this->buffer = new char[this->bufferSize];
    
    this->hierarchyPanel = dynamic_cast<SceneHierarchyPanel*>(ImGuiManager::GetPanel("Scene Hierarchy"));
}
TagUI::~TagUI()
{
    delete[] this->buffer;
}

void TagUI::DrawTextControl(std::string label, char* value, size bytes, float columnWidth)
{
    ImGui::PushID(label.c_str());

    ImGui::Columns(2, nullptr, false);
    ImGui::SetColumnWidth(0, columnWidth);

    ImGui::Text(label.c_str());
    ImGui::NextColumn();

    ImGui::PushItemWidth(ImGui::CalcItemWidth());
    
    if(ImGui::InputText("##name", value, bytes, ImGuiInputTextFlags_::ImGuiInputTextFlags_EnterReturnsTrue))
        this->tagComponent->name = std::string(value);

    ImGui::PopItemWidth();

    ImGui::Columns(1, nullptr, false);

    ImGui::PopID();
}

void TagUI::OnCheck()
{
    GameObject* entity = this->hierarchyPanel->GetSelectedContext();

    if(!entity)
        this->active = false;
    else
    {
        this->tagComponent = entity->GetComponent<Tag>();

        if(!this->tagComponent)
            this->active = false;
        else
            this->active = true;
    }
}
void TagUI::OnUpdate()
{
    if(ImGui::CollapsingHeader(this->title.c_str(), ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_DefaultOpen))
    {
        std::string& name = this->tagComponent->name;
        
        MemoryUtils::MemorySet(this->buffer, 0, this->bufferSize);
        
        for(int i = 0; i < name.size(); i++)
            this->buffer[i] = name[i];

        DrawTextControl("Name", this->buffer, this->bufferSize);
    }
}