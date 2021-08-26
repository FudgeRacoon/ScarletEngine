#include "scarletEditor/panels/components/TransformUI.hpp"
using namespace scarlet;

TransformUI::TransformUI() : ComponentUI("Transform")
{
    this->active = false;

    this->position = new float[3];
    for(int i = 0; i < 3; i++)
        this->position[i] = 0.0f;

    this->rotation = new float[3];
    for(int i = 0; i < 3; i++)
        this->rotation[i] = 0.0f;

    this->scale = new float[3];
    for(int i = 0; i < 3; i++)
        this->scale[i] = 1.0f;
}
TransformUI::~TransformUI()
{
    delete[] this->position;
    delete[] this->rotation;
    delete[] this->scale;
}

void TransformUI::DrawPositionField()
{
    ImGui::SetCursorPosX(10.0f);

    ImGui::Text("Position"); 
    ImGui::SameLine();
    
    ImGui::SetCursorPosX(150.0f);

    ImGui::PushItemWidth(100.0f);

    ImGui::Text("X");  
    ImGui::SameLine();
    //ImGui::SliderFloat("##posX", position + 0, -1.0f, 1.0f);
    ImGui::DragFloat("##posX", position + 0, 0.1f, -900.0f, 900.0f, "%.2f", 1.0f);

    ImGui::SameLine();

    ImGui::Text("Y");  
    ImGui::SameLine();
    ImGui::SliderFloat("##posY", position + 1, -1.0f, 1.0f);

    ImGui::SameLine();

    ImGui::Text("Z");  
    ImGui::SameLine();
    ImGui::SliderFloat("##posZ", position + 2, -1.0f, 1.0f);

    ImGui::PopItemWidth();
}
void TransformUI::DrawRotationField()
{
    ImGui::SetCursorPosX(10.0f);

    ImGui::Text("Rotation"); 
    ImGui::SameLine();

    ImGui::SetCursorPosX(150.0f);

    ImGui::PushItemWidth(100.0f);

    ImGui::Text("X");  
    ImGui::SameLine();
    ImGui::SliderFloat("##rotX", rotation + 0, -1.0f, 1.0f);

    ImGui::SameLine();

    ImGui::Text("Y");  
    ImGui::SameLine();
    ImGui::SliderFloat("##rotY", rotation + 1, -1.0f, 1.0f);

    ImGui::SameLine();

    ImGui::Text("Z");  
    ImGui::SameLine();
    ImGui::SliderFloat("##rotZ", rotation + 2, -1.0f, 1.0f);

    ImGui::PopItemWidth();
}
void TransformUI::DrawScaleField()
{
    ImGui::SetCursorPosX(10.0f);

    ImGui::Text("Scale"); 
    ImGui::SameLine();

    ImGui::SetCursorPosX(150.0f);

    ImGui::PushItemWidth(100.0f);

    ImGui::Text("X");  
    ImGui::SameLine();
    ImGui::SliderFloat("##scaleX", scale, -1.0f, 1.0f);

    ImGui::SameLine();

    ImGui::Text("Y");  
    ImGui::SameLine();
    ImGui::SliderFloat("##scaleY", scale + 1, -1.0f, 1.0f);

    ImGui::SameLine();

    ImGui::Text("Z");  
    ImGui::SameLine();
    ImGui::SliderFloat("##scaleZ", scale + 2, -1.0f, 1.0f);

    ImGui::PopItemWidth();
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