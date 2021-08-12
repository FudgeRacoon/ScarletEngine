#ifndef EDITOR_HPP
#define EDITOR_HPP

#include "../scarlet/ScarletEngine.hpp"
#include "../scarlet/imgui/AssetViewWindow.hpp"

class Editor : public IState
{
private:
    scarlet::Camera* editorCamera = nullptr;
    scarlet::Random rand;

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
        if(scarlet::InputManager::GetKeyDown(scarlet::KeyCode::Space))
        {
            scarlet::GameObject* go = scarlet::EditorSceneManager::Get()->GetActiveScene()->AddGameObject();
            go->AddComponent<scarlet::SpriteRenderer>();
            go->GetComponent<scarlet::SpriteRenderer>()->sprite = scarlet::AssetPool::GetSprite("mairo_sprite_sheet_0");
            go->GetComponent<scarlet::Transform>()->position = Vector3(rand.NextFloat(-960.0f, 960.0f), rand.NextFloat(-540.0f, 540.0f), 0.0f);
        }

        scarlet::EditorSceneManager::Get()->UpdateActiveScene();
    }   

    void OnExit() override
    {
        
    }   
};

#endif