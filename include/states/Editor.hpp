#ifndef EDITOR_HPP
#define EDITOR_HPP

#include "../core/ScarletEngine.hpp"
#include "../core/layers/AssetViewWindow.hpp"
#include "../core/layers/InspectorWindow.hpp"
#include "../core/layers/TransformMenu.hpp"
#include "../core/layers/SpriteRendererMenu.hpp"

class Editor : public IState
{
private:
    scarlet::Camera* editorCamera = nullptr;
    scarlet::Shader* shader = nullptr;
    scarlet::InspectorWindow* inspector = nullptr;
    
public:
    void OnEnter() override
    {
        this->editorCamera = new scarlet::Camera();
        this->shader = new scarlet::Shader("assets\\shaders\\defaultVertex.shader", "assets\\shaders\\defaultFragment.shader");

        scarlet::AssetPool::AddTexture("mario_sprite_sheet_texture", "assets\\textures\\MarioSpriteSheet.png");
        scarlet::AssetPool::AddSprite("mairo_sprite_sheet", scarlet::AssetPool::GetTexture("mario_sprite_sheet_texture"));
        scarlet::Utilites::SliceSprite(scarlet::AssetPool::GetSprite("mairo_sprite_sheet"), 64, 64);

        scarlet::ImGuiLayer::AddWindow(new scarlet::AssetViewWindow());

        inspector = (scarlet::InspectorWindow*)scarlet::ImGuiLayer::AddWindow(new scarlet::InspectorWindow());
        inspector->AddComponentMenu(new scarlet::TransformMenu());
        inspector->AddComponentMenu(new scarlet::SpriteRendererMenu());
    }

    void Update() override
    {   
        editorCamera->ProcessMouseMovement();
    }   

    void OnExit() override
    {
        
    }   
};

#endif