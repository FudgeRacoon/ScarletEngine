#include "core/primitives/Rect.hpp"
using namespace scarlet;

Rect::Rect(real x, real y, real width, real height)
{   
    this->x = x; this->y = y;
    this->width = width; this->height = height;
    this->xMax = this->x + this->width; this->yMax = this->y - this->height;

    this->dataBuffer = new real[20];
    this->indicesBuffer = new uint32[6];

    //Vertex 0
    *(this->dataBuffer + 0) = this->x;
    *(this->dataBuffer + 1) = this->y;
    *(this->dataBuffer + 2) = 0.0f;
    
    //UV (0,1)
    *(this->dataBuffer + 3) = 0.0f;
    *(this->dataBuffer + 4) = 1.0f;

    //Vertex 1
    *(this->dataBuffer + 5) = this->x;
    *(this->dataBuffer + 6) = this->yMax;
    *(this->dataBuffer + 7) = 0.0f;
    
    //UV (0,0)
    *(this->dataBuffer + 8) = 0.0f;
    *(this->dataBuffer + 9) = 0.0f;

    //Vertex 2
    *(this->dataBuffer + 10) = this->xMax;
    *(this->dataBuffer + 11) = this->yMax;
    *(this->dataBuffer + 12) = 0.0f;
    
    //UV (1,0)
    *(this->dataBuffer + 13) = 1.0f;
    *(this->dataBuffer + 14) = 0.0f;

    //Vertex 3
    *(this->dataBuffer + 15) = this->xMax;
    *(this->dataBuffer + 16) = this->y;
    *(this->dataBuffer + 17) = 0.0f;
    
    //UV (1,1)
    *(this->dataBuffer + 18) = 1.0f;
    *(this->dataBuffer + 19) = 1.0f;

    //Indicies
    *(this->indicesBuffer) = 0;
    *(this->indicesBuffer + 1) = 1;
    *(this->indicesBuffer + 2) = 2;
    *(this->indicesBuffer + 3) = 2;
    *(this->indicesBuffer + 4) = 3;
    *(this->indicesBuffer + 5) = 0;

    this->vao = new VertexArray();
    this->vbo = new VertexBuffer(this->dataBuffer, sizeof(real) * 20, GL_DYNAMIC_DRAW);
    this->ibo = new IndexBuffer(this->indicesBuffer, sizeof(uint32) * 6);
    
    VertexBufferLayout layout;
    layout.Push<real>(3, false);
    layout.Push<real>(2, false);

    this->vao->AddBuffer(*this->vbo, layout);
}
Rect::~Rect()
{
    delete this->vao;
    delete this->vbo;
    delete this->ibo;
}

void Rect::SetX(real x)
{
    this->x = x;
    this->xMax = this->x + this->width;

    this->vbo->Bind();
    this->vbo->UpdateBufferData(0, sizeof(real), &this->x);
    this->vbo->UpdateBufferData(sizeof(real) * 5, sizeof(real), &this->x);
    this->vbo->UpdateBufferData(sizeof(real) * 10, sizeof(real), &this->xMax);
    this->vbo->UpdateBufferData(sizeof(real) * 15, sizeof(real), &this->xMax);
    this->vbo->UnBind();
}
void Rect::SetY(real y)
{
    this->y = y;
    this->yMax = this->y - this->height;

    this->vbo->Bind();
    this->vbo->UpdateBufferData(sizeof(real), sizeof(real), &this->y);
    this->vbo->UpdateBufferData(sizeof(real) * 6, sizeof(real), &this->yMax);
    this->vbo->UpdateBufferData(sizeof(real) * 11, sizeof(real), &this->yMax);
    this->vbo->UpdateBufferData(sizeof(real) * 16, sizeof(real), &this->y);
    this->vbo->UnBind();
}
void Rect::SetWidth(real width)
{
    this->width = width;
    this->xMax = this->x + this->width;

    this->vbo->Bind();
    this->vbo->UpdateBufferData(sizeof(real) * 10, sizeof(real), &this->xMax);
    this->vbo->UpdateBufferData(sizeof(real) * 15, sizeof(real), &this->xMax);
    this->vbo->UnBind();
}
void Rect::SetHeight(real height)
{
    this->height = height;
    this->yMax = this->y - this->height;

    this->vbo->Bind();
    this->vbo->UpdateBufferData(sizeof(real) * 11, sizeof(real), &this->yMax);
    this->vbo->UpdateBufferData(sizeof(real) * 16, sizeof(real), &this->yMax);
    this->vbo->UnBind();
}
void Rect::SetCenter(Vector2 center)
{
    this->x = center.x - (this->width / 2);
    this->y = center.y - (this->height / 2);
}

real Rect::GetX()
{
    return this->x;
}
real Rect::GetY()
{
    return this->y;
}
real Rect::GetWidth()
{
    return this->width;
}
real Rect::GetHeight()
{
    return this->height;
}
Vector2 Rect::GetCenter()
{
    return Vector2(this->x + (this->width / 2), this->y + (this->height / 2));
}

bool Rect::Contains(Vector2 point)
{
    if(point.x >= this->x && point.x <= this->xMax &&
       point.y <= this->y && point.y >= this->yMax)
        return true;
    else
        return false;
}

void Rect::EnableBuffers()
{
    this->vao->Bind();
    this->ibo->Bind();
}
void Rect::DisbaleBuffers()
{
    this->vao->UnBind();
    this->ibo->UnBind();
}