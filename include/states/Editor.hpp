#ifndef EDITOR_HPP
#define EDITOR_HPP

#include "../scarlet/ScarletEngine.hpp"

#include "../scarletEditor/panels/ViewportPanel.hpp"
#include "../scarletEditor/panels/AssetViewWindow.hpp"

class Editor : public IState
{
private:
    scarlet::Random rand;
    scarlet::Camera* editorCamera = nullptr;
    scarlet::GameObject* go;

public:
    void OnEnter() override
    {
        editorCamera = new scarlet::Camera();
       
        scarlet::EditorSceneManager::Get()->SetCamera(editorCamera);

        scarlet::EditorSceneManager::Get()->ActivateSelector();
        scarlet::EditorSceneManager::Get()->ActivateGridLines();
        scarlet::EditorSceneManager::Get()->ActivateCameraController();

        scarlet::ImGuiManager::AddPanel(new scarlet::ViewportPanel());
        scarlet::ImGuiManager::AddPanel(new scarlet::AssetViewWindow());
        
        scarlet::AssetManager::AddTexture("mario_sprite_sheet_texture", "assets\\textures\\MarioSpriteSheet.png");
        scarlet::AssetManager::AddSprite("mairo_sprite_sheet", scarlet::AssetManager::GetTexture("mario_sprite_sheet_texture"));
        scarlet::SpriteUtils::SliceSprite(scarlet::AssetManager::GetSprite("mairo_sprite_sheet"), 64, 64);
        
        scarlet::EditorSceneManager::Get()->CreateScene("Scene_1");
        scarlet::EditorSceneManager::Get()->SetActiveScene(0);
    }
    
    void OnUpdate() override
    {   
        if(scarlet::InputManager::GetKeyDown(scarlet::KeyCode::Space))
        {
            scarlet::GameObject* go = scarlet::EditorSceneManager::Get()->GetActiveScene()->AddEntity();
            go->AddComponent<scarlet::SpriteRenderer>();
            go->GetComponent<scarlet::SpriteRenderer>()->sprite = scarlet::AssetManager::GetSprite("mairo_sprite_sheet_0");
            go->GetComponent<scarlet::Transform>()->position = scarlet::Vector3(rand.NextFloat(-960.0f, 960.0f), rand.NextFloat(-540.0f, 540.0f), 0.0f);
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