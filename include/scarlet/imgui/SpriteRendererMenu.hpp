#ifndef SPRITERENDERERMENU_HPP
#define SPRITERENDERERMENU_HPP

#include "ImGui/imgui.h"

#include "scarlet/imgui/IComponentMenu.hpp"

namespace scarlet
{
    class SpriteRendererMenu : public IComponentMenu
    {
    public:
        std::string spritePath;
        float       color[4] = {1.0f, 1.0f, 1.0f, 1.0f};
        bool        flipX = false, flipY = false;
        int         sortingOrder = 0;
    
    public:
        SpriteRendererMenu()
        {
            this->title = "SpriteRenderer";
            this->active = true;
        }

    public:
        void Update() override
        {
            if(ImGui::CollapsingHeader(this->title.c_str(), ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_DefaultOpen))
            {
                #pragma region Color
                ImGui::Text("Color");
                ImGui::SameLine(0.0f, 100.0f);
                ImGui::ColorEdit4("", color);
                #pragma endregion

                #pragma region Flip
                ImGui::Text("Flip");
                ImGui::SameLine(0.0f, 107.0f);

                ImGui::Checkbox("X", &this->flipX);
                ImGui::SameLine();
                ImGui::Checkbox("Y", &this->flipY);
                #pragma endregion

                #pragma region Sorting Order
                ImGui::PushItemWidth(100.0f);

                ImGui::Text("Sorting Order");
                ImGui::SameLine(0.0f, 44.0f);
                ImGui::InputInt("", &this->sortingOrder);
                #pragma endregion
            }
        }   
    };
}

#endif