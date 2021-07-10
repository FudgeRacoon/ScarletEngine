#ifndef EDITOR_HPP
#define EDITOR_HPP

#include "../core/ScarletEngine.hpp"
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

       inspector = (scarlet::InspectorWindow*)scarlet::ImGuiLayer::AddWindow(new scarlet::InspectorWindow());
       inspector->AddComponentMenu(new scarlet::TransformMenu());
       inspector->AddComponentMenu(new scarlet::SpriteRendererMenu());
    }

    void Update() override
    {   
        editorCamera->ProcessMouseMovement();

        scarlet::Renderer::Get()->Render(editorCamera, shader, go);
    }   

    void OnExit() override
    {
        
    }
};

#endif