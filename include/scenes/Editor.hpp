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

private:
    scarlet::real vertices[36] = 
    {   
        //Position                //Color                   //UV
        -32.0f, -32.0f, 0.0f,   1.0f, 0.0f, 0.0f, 1.0f,   0.0f, 0.0f,    //0
         32.0f, -32.0f, 0.0f,   0.0f, 1.0f, 0.0f, 1.0f,   1.0f, 0.0f,    //1
         32.0f,  32.0f, 0.0f,   0.0f, 0.0f, 1.0f, 1.0f,   1.0f, 1.0f,    //2
        -32.0f,  32.0f, 0.0f,   1.0f, 1.0f, 1.0f, 1.0f,   0.0f, 1.0f     //3
    };
    scarlet::uint32 indices[6] = 
    {
        0, 1, 2,
        2, 3, 0
    };

private:
    scarlet::VertexBuffer* vb = nullptr;
    const scarlet::IndexBuffer* ib = nullptr;
    const scarlet::VertexArray* va = nullptr;
    const scarlet::Shader* shader = nullptr;
    const scarlet::Texture* texture = nullptr;

public:
    void OnEnter() override
    {
        this->sceneCamera = new scarlet::Camera();

        this->vb = new scarlet::VertexBuffer(this->vertices, sizeof(this->vertices));
        this->ib = new scarlet::IndexBuffer(this->indices, sizeof(this->indices));
        
        scarlet::VertexBufferLayout layout;
        layout.Push<float>(3, false);
        layout.Push<float>(4, false);
        layout.Push<float>(2, false);

        this->va = new scarlet::VertexArray();
        this->va->AddBuffer(*vb, layout);

        this->shader = new scarlet::Shader("assets\\shaders\\vertex.shader", "assets\\shaders\\fragment.shader");

        this->texture = new scarlet::Texture("assets\\textures\\coin.png");
    }

    void Update() override
    {
        scarlet::Renderer::Get()->Render(*this->sceneCamera, this->texture, this->va, this->ib, this->shader);
    }

    void OnExit() override
    {
        std::cout << "Exited the editor scene" << '\n';
    }
};

#endif