#ifndef EDITOR_HPP
#define EDITOR_HPP

#include "../scarlet/ScarletEngine.hpp"
#include "../scarlet/imgui/AssetViewWindow.hpp"

class Editor : public IState
{
private:
    scarlet::Camera* editorCamera = nullptr;

public:
    void OnEnter() override
    {
        editorCamera = new scarlet::Camera();
       
        scarlet::EditorSceneManager::Get()->SetCamera(editorCamera);

        scarlet::EditorSceneManager::Get()->ActivateSelector();
        scarlet::EditorSceneManager::Get()->ActivateGridLines();
        scarlet::EditorSceneManager::Get()->ActivateCameraController();

        scarlet::AssetPool::AddTexture("mario_sprite_sheet_texture", "assets\\textures\\MarioSpriteSheet.png");
        scarlet::AssetPool::AddSprite("mairo_sprite_sheet", scarlet::AssetPool::GetTexture("mario_sprite_sheet_texture"));
        scarlet::TextureUtils::SliceSprite(scarlet::AssetPool::GetSprite("mairo_sprite_sheet"), 64, 64);
        
        scarlet::ImGuiManager::AddWindow(new scarlet::AssetViewWindow());

        scarlet::EditorSceneManager::Get()->CreateScene("Scene_1");
        scarlet::EditorSceneManager::Get()->SetActiveScene(0);
    }
    
    void OnUpdate() override
    {   
        scarlet::EditorSceneManager::Get()->UpdateActiveScene();
    }   

    void OnExit() override
    {
        
    }   
};

#endif