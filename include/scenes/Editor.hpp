#ifndef EDITOR_HPP
#define EDITOR_HPP

#include <iostream>
#include <chrono>
#include <time.h>

#include "../core/ScarletEngine.hpp"

class Editor : public IScene
{
private:
    scarlet::Camera* sceneCamera = nullptr;
    scarlet::Shader* shader = nullptr;
    scarlet::Rect* rect = nullptr;

public:
    void OnEnter() override
    {
        this->sceneCamera = new scarlet::Camera();
        this->shader = new scarlet::Shader("assets\\shaders\\defaultVertex.shader", "assets\\shaders\\defaultFragment.shader");
        this->rect = new scarlet::Rect(0.0f, 0.0f, 100.0f, 100.0f);
    }

    void Update() override
    {
        scarlet::Renderer::Get()->Render(this->sceneCamera, shader, this->rect);
    }   

    void OnExit() override
    {
        std::cout << "Exited the editor scene" << '\n';
    }
};

#endif