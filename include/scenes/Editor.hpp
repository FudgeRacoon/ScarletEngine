#ifndef EDITOR_HPP
#define EDITOR_HPP

#include "../core/ScarletEngine.hpp"
#include "../core/layers/InspectorWindow.hpp"

class Editor : public IScene
{
private:
    scarlet::Camera* sceneCamera = nullptr;
    scarlet::Shader* shader = nullptr;
    scarlet::GameObject* go = nullptr;

public:
    void OnEnter() override
    {
        this->sceneCamera = new scarlet::Camera();
        this->shader = new scarlet::Shader("assets\\shaders\\defaultVertex.shader", "assets\\shaders\\defaultFragment.shader");
    }

    void Update() override
    {   
        sceneCamera->ProcessMouseMovement();

        scarlet::Renderer::Get()->Render(sceneCamera, shader, go);
    }   

    void OnExit() override
    {
        
    }
};

#endif