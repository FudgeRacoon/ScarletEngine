#ifndef TRANSFORMMENU_HPP
#define TRANSFORMMENU_HPP

#include "Imgui/imgui.h"

#include "scarlet/imgui/IComponentMenu.hpp"

namespace scarlet
{
    class TransformMenu : public IComponentMenu
    {
    public:
        float position[3] = {0.0f, 0.0f, 0.0f};
        float rotation[3] = {0.0f, 0.0f, 0.0f};
        float scale[3]    = {0.0f, 0.0f, 0.0f};

    public:
        TransformMenu()
        {
            this->title = "Transform";
            this->active = true;
        }

    public:
        void Update() override
        {
            if(ImGui::CollapsingHeader(this->title.c_str(), ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_DefaultOpen))
            {
                ImGui::PushItemWidth(100.0f);

                #pragma region Positon
                ImGui::Text("Position"); 
                ImGui::SameLine(0.0f, 25.0f);

                ImGui::Text("X");  
                ImGui::SameLine();
                ImGui::SliderFloat("##posX", position, -1.0f, 1.0f);

                ImGui::SameLine();

                ImGui::Text("Y");  
                ImGui::SameLine();
                ImGui::SliderFloat("##posY", position + 1, -1.0f, 1.0f);

                ImGui::SameLine();

                ImGui::Text("Z");  
                ImGui::SameLine();
                ImGui::SliderFloat("##posZ", position + 2, -1.0f, 1.0f);
                #pragma endregion

                #pragma region Rotation
                ImGui::Text("Rotation"); 
                ImGui::SameLine(0.0f, 25.0f);
                
                ImGui::Text("X");  
                ImGui::SameLine();
                ImGui::SliderFloat("##rotX", rotation, -1.0f, 1.0f);

                ImGui::SameLine();

                ImGui::Text("Y");  
                ImGui::SameLine();
                ImGui::SliderFloat("##rotY", rotation + 1, -1.0f, 1.0f);

                ImGui::SameLine();

                ImGui::Text("Z");  
                ImGui::SameLine();
                ImGui::SliderFloat("##rotZ", rotation + 2, -1.0f, 1.0f);
                #pragma endregion

                #pragma region Scale
                ImGui::Text("Scale   "); 
                ImGui::SameLine(0.0f, 25.0f);
                
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
                #pragma endregion
            }
        }
    };
}   

#endif