#include "scarletEditor/panels/components/TransformUI.hpp"
using namespace scarlet;

TransformUI::TransformUI() : ComponentUI("Transform")
{
    this->position = new float[3];

    this->hierarchyPanel = dynamic_cast<SceneHierarchyPanel*>(ImGuiManager::GetPanel("Scene Hierarchy"));
}
TransformUI::~TransformUI()
{
    delete[] this->position;
}

void TransformUI::DrawPositionField()
{   
    this->position[0] = this->transformComponent->position.x;
    this->position[1] = this->transformComponent->position.y;
    this->position[2] = this->transformComponent->position.z;

    if(ImGui::DragFloat3("Position", position, 0.5f))
    {
        this->transformComponent->position.x = this->position[0];
        this->transformComponent->position.y = this->position[1];
        this->transformComponent->position.z = this->position[2];
    }
}
void TransformUI::DrawRotationField()
{
    
}
void TransformUI::DrawScaleField()
{
    
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
        DrawPositionField();
        DrawRotationField();
        DrawScaleField();
    }
}