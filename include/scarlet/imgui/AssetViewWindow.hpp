#ifndef ASSETVIEWWINDOW_HPP
#define ASSETVIEWWINDOW_HPP

#include <map>
#include <vector>
#include <string>

#include "scarlet/graphics/Sprite.hpp"

#include "scarlet/imgui/ImGuiManager.hpp"

#include "scarlet/system/AssetPool.hpp"

#include "scarlet/math/Vector2.hpp"

namespace scarlet
{
    class AssetViewWindow : public ImGuiWindow
    {
    public:
        AssetViewWindow() : ImGuiWindow("Assets") {}

    public:
        void OnUpdate() override
        {
            // ImGui::Begin(this->title.c_str());

            // static int id = 0;

            // ImVec2 windowPos   = ImGui::GetWindowPos();
            // ImVec2 windowSize  = ImGui::GetWindowSize();
            // ImVec2 itemSpacing = ImGui::GetStyle().ItemSpacing;

            // float windowXMax = windowPos.x + windowSize.x;

            // for(std::pair<std::string, Sprite*> sprite : AssetPool::GetSprites())
            // {
            //     float spriteWidth                   = sprite.second->GetRect()->GetWidth() * 0.75f;
            //     float spriteHeight                  = sprite.second->GetRect()->GetHeight() * 0.75f;
            //     std::vector<Vector2> spriteUvCoords = sprite.second->GetRect()->GetUV();
            //     int spriteTextureID                 = sprite.second->GetTexture()->GetID();
                
            //     ImGui::PushID(id++);
                
            //     ImVec2 imageSize = ImVec2(spriteWidth, spriteHeight);
            //     ImVec2 uv00      = ImVec2(spriteUvCoords[0].x, spriteUvCoords[2].y);
            //     ImVec2 uv11      = ImVec2(spriteUvCoords[2].x, spriteUvCoords[0].y);
            //     if(ImGui::ImageButton((int*)spriteTextureID, imageSize, uv00, uv11))
            //     {
                    
            //     }
                
            //     ImGui::PopID();

            //     float lastButtonXMax = ImGui::GetItemRectMax().x;
            //     float nextButtonXMax = lastButtonXMax + itemSpacing.x + spriteWidth;

            //     if(nextButtonXMax < windowXMax)
            //         ImGui::SameLine();
            // }   

            // id = 0;

            // ImGui::End();
        }
    };
}

#endif