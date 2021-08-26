#ifndef AssetViewPanel_HPP
#define AssetViewPanel_HPP

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
    class AssetViewPanel : public ImGuiPanel
    {
    private:
        int buttonId;
        float imageSize;
    
    private:
        bool showSprites;
        bool showTextures;

    public:
        AssetViewPanel();

    private:
        void ResetId();
        void ShowSprites();
        void ShowTextures();

    private:
        void DrawSprites();
        void DrawTextures();

    public:
        void OnUpdate() override;
    };
}

#endif