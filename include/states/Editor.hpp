#ifndef EDITOR_HPP
#define EDITOR_HPP

#include "../scarlet/ScarletEngine.hpp"
#include "../scarlet/imgui/AssetViewWindow.hpp"
#include "../scarlet/imgui/ProfilerWindow.hpp"
#include "../scarlet/imgui/InspectorWindow.hpp"
#include "../scarlet/imgui/TransformMenu.hpp"
#include "../scarlet/imgui/SpriteRendererMenu.hpp"

class Editor : public IState
{
private:
    scarlet::Camera* editorCamera = nullptr;
    scarlet::CameraController* editorCameraController = nullptr;
    
public:
    void OnEnter() override
    {
        editorCamera = new scarlet::Camera();
        editorCameraController = new scarlet::CameraController(editorCamera);

        scarlet::AssetPool::AddTexture("mario_sprite_sheet_texture", "assets\\textures\\MarioSpriteSheet.png");
        scarlet::AssetPool::AddSprite("mairo_sprite_sheet", scarlet::AssetPool::GetTexture("mario_sprite_sheet_texture"));
        scarlet::TextureUtils::SliceSprite(scarlet::AssetPool::GetSprite("mairo_sprite_sheet"), 64, 64);

        scarlet::ImGuiManager::AddWindow(new scarlet::ProfilerWindow());

        scarlet::EditorSceneManager::Get()->CreateScene("Scene_1");
        scarlet::EditorSceneManager::Get()->SetActiveScene(0);
    }

    void OnUpdate() override
    {   
        editorCameraController->OnUpdate();

        scarlet::EditorSceneManager::Get()->UpdateActiveScene(editorCamera);
    }   

    void OnExit() override
    {
        
    }   
};

#endif