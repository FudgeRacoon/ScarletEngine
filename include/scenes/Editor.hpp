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
    scarlet::Sprite* sprite = nullptr;
    scarlet::Sprite* sprite_1 = nullptr;
public:
    void OnEnter() override
    {
        this->sceneCamera = new scarlet::Camera();
        this->shader = new scarlet::Shader("assets\\shaders\\defaultVertex.shader", "assets\\shaders\\defaultFragment.shader");

        sprite = scarlet::AssetPool::AddSprite("coin", new scarlet::Texture("assets\\textures\\coin.png"));
    }

    void Update() override
    {
        shader->Bind();
        sprite->GetRect()->EnableBuffers();
        sprite->GetTexture()->Bind();

        this->sceneCamera->ProcessMouseMovement();

        shader->SetMat4("view", Matrix4::GetValuePointer(this->sceneCamera->GetViewMatrix()));
        shader->SetMat4("proj", Matrix4::GetValuePointer(this->sceneCamera->GetProjectionMatrix()));
        shader->SetVec4f("u_color", 1.0f, 1.0f, 1.0f, 1.0f);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }   

    void OnExit() override
    {
        std::cout << "Exited the editor scene" << '\n';
    }
};

#endif