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
        std::string& tag = this->tagComponent->tag;
        
        MemoryUtils::MemorySet(this->buffer, 0, this->bufferSize);
        
        for(int i = 0; i < tag.size(); i++)
            this->buffer[i] = tag[i];

        if(ImGui::InputText("Tag", this->buffer, this->bufferSize))
            this->tagComponent->tag = std::string(this->buffer);
    }
}