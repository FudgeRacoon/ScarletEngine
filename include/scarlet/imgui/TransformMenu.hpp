#ifndef TRANSFORMMENU_HPP
#define TRANSFORMMENU_HPP

#include "Imgui/imgui.h"

#include "scarlet/imgui/ComponentMenu.hpp"

namespace scarlet
{
    class TransformMenu : public ComponentMenu
    {
    public:
        float* position;
        float* rotation;
        float* scale;

    public:
        TransformMenu() : ComponentMenu("Transform")
        {
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
        ~TransformMenu()
        {
            delete[] this->position;
            delete[] this->rotation;
            delete[] this->scale;
        }

    public:
        void Update() override
        {
            if(ImGui::CollapsingHeader(this->title.c_str(), ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_DefaultOpen))
            { 
                //Position
                {
                    ImGui::SetCursorPosX(this->START_POS);

                    ImGui::Text("Position"); 
                    ImGui::SameLine();
                    
                    ImGui::SetCursorPosX(this->SPACING);

                    ImGui::PushItemWidth(100.0f);

                    ImGui::Text("X");  
                    ImGui::SameLine();
                    ImGui::SliderFloat("##posX", position + 0, -1.0f, 1.0f);

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
                
                //Rotation
                {
                    ImGui::SetCursorPosX(this->START_POS);

                    ImGui::Text("Rotation"); 
                    ImGui::SameLine();

                    ImGui::SetCursorPosX(this->SPACING);

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

                //Scale
                {
                    ImGui::SetCursorPosX(this->START_POS);

                    ImGui::Text("Scale"); 
                    ImGui::SameLine();

                    ImGui::SetCursorPosX(this->SPACING);

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
            }
        }
    };
}   

#endif