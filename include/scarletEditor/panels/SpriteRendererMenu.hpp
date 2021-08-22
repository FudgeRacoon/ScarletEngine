#ifndef SPRITERENDERERMENU_HPP
#define SPRITERENDERERMENU_HPP

#include "ImGui/imgui.h"

#include "scarletEditor/panels/ComponentMenu.hpp"

#include "scarlet/utils/MemoryUtils.hpp"

namespace scarlet
{
    class SpriteRendererMenu : public ComponentMenu
    {
    public:
        char*       spriteName;
        float*      color;
        bool        flipX, flipY;
        int         sortingOrder;
    
    public:
        SpriteRendererMenu() : ComponentMenu("SpriteRenderer")
        {
            this->spriteName = new char[16];
            this->spriteName[15] = '\0';
            MemoryUtils::MemorySet(this->spriteName, ' ', 15);
            
            this->color = new float[4];
            for(int i = 0; i < 4; i++)
                this->color[i] = 1.0f;

            this->flipX = false; this->flipY = false;
            this->sortingOrder = 0;
        }
        ~SpriteRendererMenu()
        {
            delete[] this->spriteName;
            delete[] this->color;
        }

    public:
        void Update() override
        {
            if(ImGui::CollapsingHeader(this->title.c_str(), ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_DefaultOpen))
            {   
                //Sprite
                {
                    ImGui::SetCursorPosX(this->START_POS);

                    ImGui::Text("Sprite");
                    ImGui::SameLine();

                    ImGui::SetCursorPosX(this->SPACING);

                    ImGui::PushItemWidth(360.0f);

                    ImGui::InputText(
                        "##spriteText", 
                        spriteName, 
                        strlen(spriteName),
                        ImGuiInputTextFlags_::ImGuiInputTextFlags_ReadOnly
                    );

                    ImGui::PopItemWidth();
                }

                //Color
                {
                    ImGui::SetCursorPosX(this->START_POS);

                    ImGui::Text("Color");
                    ImGui::SameLine();

                    ImGui::SetCursorPosX(this->SPACING);

                    ImGui::PushItemWidth(360.0f);
                    
                    ImGui::ColorEdit4("##color", color);
                    
                    ImGui::PopItemWidth();
                }

                //Flip
                {
                    ImGui::SetCursorPosX(this->START_POS);

                    ImGui::Text("Flip");
                    ImGui::SameLine();
                    
                    ImGui::SetCursorPosX(this->SPACING);

                    ImGui::Checkbox("X", &this->flipX);
                    ImGui::SameLine();
                    ImGui::Checkbox("Y", &this->flipY);
                }

                //Sorting Order
                {   
                    ImGui::SetCursorPosX(this->START_POS);

                    ImGui::Text("Sorting Order");
                    ImGui::SameLine();

                    ImGui::SetCursorPosX(this->SPACING);

                    ImGui::PushItemWidth(360.0f);

                    ImGui::InputInt("##sortingOrder", &this->sortingOrder);

                    ImGui::PopItemWidth();
                }
            }
        }   
    };
}

#endif