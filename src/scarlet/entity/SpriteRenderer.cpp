#include "scarlet/entity/SpriteRenderer.hpp"
using namespace scarlet;

SpriteRenderer::SpriteRenderer()
{
    this->sprite = nullptr;
    this->material = new Shader("assets\\shaders\\defaultFragment.shader");

    this->color = Color();
    this->flipX = false; this->flipY = false;
    this->sortingOrder = 0;
}

void SpriteRenderer::Setup()
{
    
}
void SpriteRenderer::Update()
{
    
}
void SpriteRenderer::GUI()
{
    
}