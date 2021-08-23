#ifndef ASSETVIEWWINDOW_HPP
#define ASSETVIEWWINDOW_HPP

#include <map>
#include <vector>
#include <string>

#include "scarlet/core/logger/Logger.hpp"
#include "scarlet/core/math/Vector2.hpp"

#include "scarlet/graphics/Sprite.hpp"

#include "scarlet/imgui/ImGuiPanel.hpp"

#include "scarlet/system/AssetManager.hpp"

namespace scarlet
{
    class AssetViewWindow : public ImGuiPanel
    {
    private:
        int buttonID;
        float imageSize;
    
    private:
        bool showSprites;
        bool showTextures;

    public:
        AssetViewWindow() : ImGuiPanel("Assets") 
        {
            this->buttonID = 0;
            this->imageSize = 0.75f;

            this->showSprites = true;
            this->showTextures = false;
        }

    private:
        void ResetID()
        {
            this->buttonID = 0;
        }

    private:
        void ShowSprites(ImVec2 windowPos, ImVec2 windowSize, ImVec2 itemSpacing)
        {
            float windowXMax = windowPos.x + windowSize.x;
            
            for(std::pair<std::string, Sprite*> sprite : AssetManager::GetSprites())
            {   
                if(sprite.second->GetTexture())
                {
                    float imageWidth        = 64.0f * this->imageSize;
                    float imageHeight       = 64.0f * this->imageSize;
                    std::vector<Vector2> uv = sprite.second->GetUV();
                    int textureID           = sprite.second->GetTexture()->GetID();

                    ImGui::PushID(this->buttonID++);

                    ImVec2 imageSize = ImVec2(imageWidth, imageHeight);
                    ImVec2 uv00      = ImVec2(uv[0].x, uv[2].y);
                    ImVec2 uv11      = ImVec2(uv[2].x, uv[0].y);

                    if(ImGui::ImageButton((int*)textureID, imageSize, uv00, uv11))
                    {

                    }

                    ImGui::PopID();

                    float lastImageXMax = ImGui::GetItemRectMax().x;
                    float nextImageXMax = lastImageXMax + itemSpacing.x + imageWidth;

                    if(nextImageXMax < windowXMax)
                        ImGui::SameLine();
                }
            }
        }
        void ShowTextures(ImVec2 windowPos, ImVec2 windowSize, ImVec2 itemSpacing)
        {
            float windowXMax = windowPos.x + windowSize.x;

            for(std::pair<std::string, Texture*> texture : AssetManager::GetTextures())
            {
                float imageWidth  = 64.0f * this->imageSize;
                float imageHeight = 64.0f * this->imageSize;
                int textureID     = texture.second->GetID();

                ImGui::PushID(this->buttonID++);

                ImVec2 imageSize = ImVec2(imageWidth, imageHeight);
                ImVec2 uv00      = ImVec2(0.0f, 1.0f);
                ImVec2 uv11      = ImVec2(1.0f, 0.0f);

                if(ImGui::ImageButton((int*)textureID, imageSize, uv00, uv11))
                {

                }

                ImGui::PopID();

                float lastImageXMax = ImGui::GetItemRectMax().x;
                float nextImageXMax = lastImageXMax + itemSpacing.x + imageWidth;

                if(nextImageXMax < windowXMax)
                    ImGui::SameLine();
            }
        }

    public:
        void OnUpdate() override
        {
            ImGui::Begin(this->title.c_str());

            ImVec2 windowPos   = ImGui::GetWindowPos();
            ImVec2 windowSize  = ImGui::GetWindowSize();
            ImVec2 itemSpacing = ImGui::GetStyle().ItemSpacing;

            ImGui::BeginTabBar("asset_categories");

            if(ImGui::TabItemButton("Sprites"))
            {
                this->showSprites = true;
                this->showTextures = false;
            }

            if(ImGui::TabItemButton("Textures"))
            {
                this->showSprites = false;
                this->showTextures = true;
            }

            if(this->showSprites)
                ShowSprites(windowPos, windowSize, itemSpacing);
            else if(this->showTextures)
                ShowTextures(windowPos, windowSize, itemSpacing);

            ResetID();
                
            ImGui::EndTabBar();

            ImGui::End();
        }
    };
}

#endif