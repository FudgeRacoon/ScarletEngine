#include "scarletEditor/panels/AssetViewPanel.hpp"
using namespace scarlet;

AssetViewPanel::AssetViewPanel() : ImGuiPanel("Assets")
{
    this->buttonId = 0;
    this->imageSize = 0.75f;
    
    this->showSprites = true;
    this->showTextures = false;
}

void AssetViewPanel::ResetId()
{
    this->buttonId = 0;
}
void AssetViewPanel::ShowSprites()
{
    this->showSprites = true;
    this->showTextures = false;
}
void AssetViewPanel::ShowTextures()
{
    this->showSprites = false;
    this->showTextures = true;
}

void AssetViewPanel::DrawSprites()
{
    ImVec2 windowPos = ImGui::GetWindowPos();
    ImVec2 windowSize = ImGui::GetWindowSize();
    ImVec2 itemSpacing = ImGui::GetStyle().ItemSpacing;

    float windowXMax = windowPos.x + windowSize.x;
            
    for(std::pair<std::string, Sprite*> sprite : AssetManager::GetSprites())
    {   
        if(sprite.second->GetTexture())
        {
            float imageWidth        = 64.0f * this->imageSize;
            float imageHeight       = 64.0f * this->imageSize;
            std::vector<Vector2> uv = sprite.second->GetUV();
            int textureID           = sprite.second->GetTexture()->GetId();

            ImGui::PushID(this->buttonId++);

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
void AssetViewPanel::DrawTextures()
{
    ImVec2 windowPos = ImGui::GetWindowPos();
    ImVec2 windowSize = ImGui::GetWindowSize();
    ImVec2 itemSpacing = ImGui::GetStyle().ItemSpacing;

    float windowXMax = windowPos.x + windowSize.x;

    for(std::pair<std::string, Texture*> texture : AssetManager::GetTextures())
    {
        float imageWidth  = 64.0f * this->imageSize;
        float imageHeight = 64.0f * this->imageSize;
        int textureID     = texture.second->GetId();

        ImGui::PushID(this->buttonId++);

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

void AssetViewPanel::OnUpdate()
{
    ImGui::Begin(this->title.c_str());

    ImGui::BeginTabBar("asset_categories");

    if(ImGui::TabItemButton("Sprites"))
        ShowSprites();

    if(ImGui::TabItemButton("Textures"))
        ShowTextures();

    if(this->showSprites)
        DrawSprites();
    else if(this->showTextures)
        DrawTextures();

    ResetId();
        
    ImGui::EndTabBar();

    ImGui::End();
}