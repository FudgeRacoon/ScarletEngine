#ifndef EDITOR_HPP
#define EDITOR_HPP

#include "../scarlet/ScarletEngine.hpp"
#include "../scarlet/imgui/AssetViewWindow.hpp"
#include "../scarlet/imgui/InspectorWindow.hpp"
#include "../scarlet/imgui/TransformMenu.hpp"
#include "../scarlet/imgui/SpriteRendererMenu.hpp"

class Editor : public IState
{
private:
    scarlet::Camera* editorCamera = nullptr;
    scarlet::InspectorWindow* inspector = nullptr;
    
public:
    void OnEnter() override
    {
        this->editorCamera = new scarlet::Camera();

        scarlet::AssetPool::AddTexture("mario_sprite_sheet_texture", "assets\\textures\\MarioSpriteSheet.png");
        scarlet::AssetPool::AddSprite("mairo_sprite_sheet", scarlet::AssetPool::GetTexture("mario_sprite_sheet_texture"));
        scarlet::TextureUtils::SliceSprite(scarlet::AssetPool::GetSprite("mairo_sprite_sheet"), 64, 64);

        scarlet::ImGuiManager::AddWindow(new scarlet::AssetViewWindow());

        inspector = (scarlet::InspectorWindow*)scarlet::ImGuiManager::AddWindow(new scarlet::InspectorWindow());
        inspector->AddComponentMenu(new scarlet::TransformMenu());
        inspector->AddComponentMenu(new scarlet::SpriteRendererMenu());
    }

    void OnUpdate() override
    {   
        editorCamera->ProcessMouseMovement();
    }   

    void OnExit() override
    {
        
    }   
};

#endif