#ifndef EDITOR_HPP
#define EDITOR_HPP

#include <iostream>

#include "../core/ScarletEngine.hpp"

class Editor : public IScene
{
private:
    scarlet::Camera* sceneCamera = nullptr;

private:
    scarlet::real vertices[28] = 
    {   
        //Position                //Color
        -100.0f, -100.0f, 0.0f,   1.0f, 0.0f, 0.0f, 1.0f,   //0
         100.0f, -100.0f, 0.0f,   0.0f, 1.0f, 0.0f, 1.0f,   //1
         100.0f,  100.0f, 0.0f,   0.0f, 0.0f, 1.0f, 1.0f,   //2
        -100.0f,  100.0f, 0.0f,   1.0f, 1.0f, 1.0f, 1.0f    //3
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

public:
    void OnEnter() override
    {
        this->sceneCamera = new scarlet::Camera();

        this->vb = new scarlet::VertexBuffer(this->vertices, sizeof(this->vertices));
        this->ib = new scarlet::IndexBuffer(this->indices, sizeof(this->indices));
        
        scarlet::VertexBufferLayout layout;
        layout.Push<float>(3, false);
        layout.Push<float>(4, false);
        
        this->va = new scarlet::VertexArray();
        this->va->AddBuffer(*vb, layout);

        this->shader = new scarlet::Shader("assets\\shaders\\vertex.shader", "assets\\shaders\\fragment.shader");
    }

    void Update() override
    {
        scarlet::Renderer::Get()->Render(*this->sceneCamera, this->va, this->ib, this->shader);
    }

    void OnExit() override
    {
        std::cout << "Exited the editor scene" << '\n';
    }
};

#endif