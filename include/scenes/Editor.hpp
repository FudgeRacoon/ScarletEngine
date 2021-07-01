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
public:
    void OnEnter() override
    {
        this->sceneCamera = new scarlet::Camera();
        this->shader = new scarlet::Shader("assets\\shaders\\defaultVertex.shader", "assets\\shaders\\defaultFragment.shader");
        this->rect = new scarlet::Rect(0.0f, 0.0f, 100.0f, 100.0f);

        s = new scarlet::Sprite(new scarlet::Texture("assets\\textures\\coin.png"), new scarlet::Rect(-16.0f, 16.0f, 256.0f, 256.0f));
    }

    void Update() override
    {
        sceneCamera->ProcessMouseMovement();

        shader->Bind();
        s->GetRect()->EnableBuffers();
        s->GetTexture()->Bind();

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