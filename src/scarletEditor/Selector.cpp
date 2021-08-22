#include "scarletEditor/Selector.hpp"
using namespace scarlet::editor;

#include "scarlet/system/EditorSceneManager.hpp"

Selector::Selector(uint32 width, uint32 height)
{
    this->SelectorFrameBuffer = new FrameBuffer();

    FrameBufferSpecification spec = {
        .width = width, 
        .height = height, 
        .type = GL_INT, 
        .format = GL_RED_INTEGER, 
        .internalFormat = GL_R32I
    };

    this->SelectorFrameBuffer->AttachColorTexture(spec);
}
Selector::~Selector()
{
    delete this->SelectorFrameBuffer;
}

void Selector::OnMouseDrag()
{

}
void Selector::OnMousePress()
{
    // this->SelectorFrameBuffer->Bind();

    // if(InputManager::GetMouseButton(0))
    // {
    //     int x = scarlet::InputManager::GetMousePosition().x;
    //     int y = scarlet::GraphicsContext::GetViewPort().w - scarlet::InputManager::GetMousePosition().y;

    //     int pixelVal = this->SelectorFrameBuffer->ReadPixel(GL_RED_INTEGER, GL_INT, x, y);

    //     GameObject* go = EditorSceneManager::Get()->GetActiveScene()->GetEntityById(pixelVal);

    //     if(go)
    //         Logger::LogDebug("%s", go->GetName().c_str());
    // }

    // this->SelectorFrameBuffer->UnBind();
}

void Selector::Bind()
{
    this->SelectorFrameBuffer->Bind();
}
void Selector::UnBind()
{
    this->SelectorFrameBuffer->UnBind();
}