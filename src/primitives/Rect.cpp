#include "scarlet/primitives/Rect.hpp"
using namespace scarlet;

Rect::Rect(float x, float y, float width, float height)
{   
    this->x = x; this->y = y;
    this->width = width; this->height = height;
    this->xMax = this->x + this->width; this->yMax = this->y - this->height;

    this->dataBuffer = new float[20];
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
    this->vbo = new VertexBuffer(this->dataBuffer, sizeof(float) * 20, GL_DYNAMIC_DRAW);
    this->ibo = new IndexBuffer(this->indicesBuffer, sizeof(uint32) * 6);
    
    VertexBufferLayout layout;
    layout.Push<float>(3, false);
    layout.Push<float>(2, false);

    this->vao->AddBuffer(*this->vbo, layout);
}
Rect::~Rect()
{
    delete this->vao;
    delete this->vbo;
    delete this->ibo;
}

void Rect::SetX(float x)
{
    this->x = x;
    this->xMax = this->x + this->width;

    this->vbo->UpdateBufferData(0, sizeof(float), &this->x);
    this->vbo->UpdateBufferData(sizeof(float) * 5, sizeof(float), &this->x);
    this->vbo->UpdateBufferData(sizeof(float) * 10, sizeof(float), &this->xMax);
    this->vbo->UpdateBufferData(sizeof(float) * 15, sizeof(float), &this->xMax);
}
void Rect::SetY(float y)
{
    this->y = y;
    this->yMax = this->y - this->height;

    this->vbo->UpdateBufferData(sizeof(float), sizeof(float), &this->y);
    this->vbo->UpdateBufferData(sizeof(float) * 6, sizeof(float), &this->yMax);
    this->vbo->UpdateBufferData(sizeof(float) * 11, sizeof(float), &this->yMax);
    this->vbo->UpdateBufferData(sizeof(float) * 16, sizeof(float), &this->y);
}
void Rect::SetWidth(float width)
{
    this->width = width;
    this->xMax = this->x + this->width;

    this->vbo->UpdateBufferData(sizeof(float) * 10, sizeof(float), &this->xMax);
    this->vbo->UpdateBufferData(sizeof(float) * 15, sizeof(float), &this->xMax);
}
void Rect::SetHeight(float height)
{
    this->height = height;
    this->yMax = this->y - this->height;

    this->vbo->UpdateBufferData(sizeof(float) * 11, sizeof(float), &this->yMax);
    this->vbo->UpdateBufferData(sizeof(float) * 16, sizeof(float), &this->yMax);
}
void Rect::SetUV(Vector2 v1, Vector2 v2, Vector2 v3, Vector2 v4)
{
    //UV (0,0)
    *(this->dataBuffer + 8) = v1.x;
    *(this->dataBuffer + 9) = v1.y;

    float* v1Data = new float[2];
    *(v1Data + 0) = v1.x;
    *(v1Data + 1) = v1.y;
    this->vbo->UpdateBufferData(8 * sizeof(float), 2 * sizeof(float), v1Data);

    //UV (1,0)
    *(this->dataBuffer + 13) = v2.x;
    *(this->dataBuffer + 14) = v2.y;

    float* v2Data = new float[2];
    *(v2Data + 0) = v2.x;
    *(v2Data + 1) = v2.y;
    this->vbo->UpdateBufferData(13 * sizeof(float), 2 * sizeof(float), v2Data);

    //UV (1,1)
    *(this->dataBuffer + 18) = v3.x;
    *(this->dataBuffer + 19) = v3.y;

    float* v3Data = new float[2];
    *(v3Data + 0) = v3.x;
    *(v3Data + 1) = v3.y;
    this->vbo->UpdateBufferData(18 * sizeof(float), 2 * sizeof(float), v3Data);

    //UV (0,1)
    *(this->dataBuffer + 3) = v4.x;
    *(this->dataBuffer + 4) = v4.y;

    float* v4Data = new float[2];
    *(v4Data + 0) = v4.x;
    *(v4Data + 1) = v4.y;
    this->vbo->UpdateBufferData(3 * sizeof(float), 2 * sizeof(float), v4Data);

    delete[] v1Data;
    delete[] v2Data;
    delete[] v3Data;
    delete[] v4Data;
}

float Rect::GetX()
{
    return this->x;
}
float Rect::GetY()
{
    return this->y;
}
float Rect::GetWidth()
{
    return this->width;
}
float Rect::GetHeight()
{
    return this->height;
}
std::vector<Vector2> Rect::GetUV()
{
    std::vector<Vector2> uvCoords;

    Vector2 uv00(this->dataBuffer[8], this->dataBuffer[9]);
    Vector2 uv10(this->dataBuffer[13], this->dataBuffer[14]);
    Vector2 uv11(this->dataBuffer[18], this->dataBuffer[19]);
    Vector2 uv01(this->dataBuffer[3], this->dataBuffer[4]);

    uvCoords.push_back(uv00);
    uvCoords.push_back(uv10);
    uvCoords.push_back(uv11);
    uvCoords.push_back(uv01);

    return uvCoords;
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

void Rect::Bind()
{
    this->vao->Bind();
    this->ibo->Bind();
}
void Rect::UnBind()
{
    this->vao->UnBind();
    this->ibo->UnBind();
}