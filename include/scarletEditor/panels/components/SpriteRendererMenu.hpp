#ifndef SPRITERENDERERMENU_HPP
#define SPRITERENDERERMENU_HPP

#include "ImGui/imgui.h"

#include "scarletEditor/panels/components/ComponentUI.hpp"

#include "scarlet/utils/MemoryUtils.hpp"

namespace scarlet
{
    class SpriteRendererMenu : public ComponentUI
    {
    public:
        SpriteRendererMenu() : ComponentUI("SpriteRenderer")
        {
            
        }

    public:
        void OnCheck() override
        {
            
        }
        void OnUpdate() override
        {
            if(ImGui::CollapsingHeader(this->title.c_str(), ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_DefaultOpen))
            {   
                // //Sprite
                // {
                //     ImGui::SetCursorPosX(10.0f);

                //     ImGui::Text("Sprite");
                //     ImGui::SameLine();

                //     ImGui::SetCursorPosX(150.0f);

                //     ImGui::PushItemWidth(360.0f);

                //     ImGui::InputText(
                //         "##spriteText", 
                //         spriteName, 
                //         strlen(spriteName),
                //         ImGuiInputTextFlags_::ImGuiInputTextFlags_ReadOnly
                //     );

                //     ImGui::PopItemWidth();
                // }

                // //Color
                // {
                //     ImGui::SetCursorPosX(10.0f);

                //     ImGui::Text("Color");
                //     ImGui::SameLine();

                //     ImGui::SetCursorPosX(150.0f);

                //     ImGui::PushItemWidth(360.0f);
                    
                //     ImGui::ColorEdit4("##color", color);
                    
                //     ImGui::PopItemWidth();
                // }

                // //Flip
                // {
                //     ImGui::SetCursorPosX(10.0f);

                //     ImGui::Text("Flip");
                //     ImGui::SameLine();
                    
                //     ImGui::SetCursorPosX(150.0f);

                //     ImGui::Checkbox("X", &this->flipX);
                //     ImGui::SameLine();
                //     ImGui::Checkbox("Y", &this->flipY);
                // }

                // //Sorting Order
                // {   
                //     ImGui::SetCursorPosX(10.0f);

                //     ImGui::Text("Sorting Order");
                //     ImGui::SameLine();

                //     ImGui::SetCursorPosX(150.0f);

                //     ImGui::PushItemWidth(360.0f);

                //     ImGui::InputInt("##sortingOrder", &this->sortingOrder);

                //     ImGui::PopItemWidth();
                // }
            }
        }   
    };
}

#endif