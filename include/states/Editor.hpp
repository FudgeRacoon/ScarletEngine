#ifndef EDITOR_HPP
#define EDITOR_HPP

#include "../scarlet/ScarletEngine.hpp"

#include "../scarletEditor/panels/ViewportPanel.hpp"
#include "../scarletEditor/panels/InspectorPanel.hpp"
#include "../scarletEditor/panels/AssetViewPanel.hpp"
#include "../scarletEditor/panels/SceneHierarchyPanel.hpp"

class Editor : public IState
{
private:
    scarlet::Camera* editorCamera = nullptr;
    scarlet::GameObject* go;

public:
    void OnEnter() override
    {
        editorCamera = new scarlet::Camera();
       
        scarlet::ImGuiManager::AddPanel(new scarlet::ViewportPanel());
        scarlet::ImGuiManager::AddPanel(new scarlet::SceneHierarchyPanel());
        scarlet::ImGuiManager::AddPanel(new scarlet::InspectorPanel());
        scarlet::ImGuiManager::AddPanel(new scarlet::AssetViewPanel());

        scarlet::EditorSceneManager::Get()->SetCamera(editorCamera);
        scarlet::EditorSceneManager::Get()->ActivateSelector();
        scarlet::EditorSceneManager::Get()->ActivateGridLines();
        scarlet::EditorSceneManager::Get()->ActivateCameraController();
        
        scarlet::EditorSceneManager::Get()->CreateScene("Scene_1");
        scarlet::EditorSceneManager::Get()->SetActiveScene(0);
        
        scarlet::AssetManager::AddTexture("mario_sprite_sheet_texture", "assets\\textures\\MarioSpriteSheet.png");
        scarlet::AssetManager::AddSprite("mairo_sprite_sheet", scarlet::AssetManager::GetTexture("mario_sprite_sheet_texture"));
        scarlet::SpriteUtils::SliceSprite(scarlet::AssetManager::GetSprite("mairo_sprite_sheet"), 64, 64);
    }
    
    void OnUpdate() override
    {   
        if(scarlet::InputManager::GetKeyDown(scarlet::KeyCode::Space))
        {
            scarlet::GameObject* go = scarlet::EditorSceneManager::Get()->GetActiveScene()->AddEntity();
            go->AddComponent<scarlet::SpriteRenderer>();
            go->GetComponent<scarlet::SpriteRenderer>()->sprite = scarlet::AssetManager::GetSprite("mairo_sprite_sheet_0");
        }

        scarlet::EditorSceneManager::Get()->UpdateActiveScene();
    }   

    void OnImGuiRender() override
    {
        scarlet::ImGuiManager::OnEvent(scarlet::InputManager::GetSDLEvent());
        scarlet::ImGuiManager::OnRender();
    }   
};

#endif