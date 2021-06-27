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
    scarlet::Sprite* s = nullptr;

    float c = 0.0f;

public:
    void OnEnter() override
    {
        this->sceneCamera = new scarlet::Camera();
        this->shader = new scarlet::Shader("assets\\shaders\\defaultVertex.shader", "assets\\shaders\\defaultFragment.shader");
        this->rect = new scarlet::Rect(0.0f, 0.0f, 100.0f, 100.0f);

        s = new scarlet::Sprite();
        s->SetTexture(new scarlet::Texture("assets\\textures\\coin.png"));
    }

    void Update() override
    {
        //scarlet::Renderer::Get()->Render(this->sceneCamera, shader, this->rect);

        shader->Bind();
        s->GetRect()->EnableBuffers();
        s->GetTexture()->Bind();

        sceneCamera->ProcessMouseMovement();

        shader->SetMat4("view", Matrix4::GetValuePointer(sceneCamera->GetViewMatrix()));
        shader->SetMat4("proj", Matrix4::GetValuePointer(sceneCamera->GetProjectionMatrix()));
        shader->SetVec4f("u_color", 1.0f, 1.0f, 1.0f, 1.0f);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }   

    void OnExit() override
    {
        std::cout << "Exited the editor scene" << '\n';
    }
};

#endif