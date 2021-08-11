#include "scarletEditor/Selector.hpp"
using namespace scarlet::editor;

Selector::Selector(uint32 width, uint32 height)
{
    this->SelectorFrameBuffer = new FrameBuffer();

    FrameBufferSpecification spec = {
        .width = width, 
        .height = height, 
        .type = Graphics_Type::SCARLET_UNSIGNED_INT_8_8_8_8, 
        .format = Graphics_Format::SCARLET_RGBA, 
        .internalFormat = Graphics_Format::SCARLET_RGBA
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
    this->SelectorFrameBuffer->Bind();

    if(InputManager::GetMouseButton(0))
    {
        int pixelVal = this->SelectorFrameBuffer->ReadPixel(
            Graphics_Format::SCARLET_RGBA,
            Graphics_Type::SCARLET_UNSIGNED_INT_8_8_8_8,
            InputManager::GetMousePosition().x,
            InputManager::GetMousePosition().y
        );

        Logger::LogDebug("%x", pixelVal);
    }

    this->SelectorFrameBuffer->UnBind();
}

void Selector::Bind()
{
    this->SelectorFrameBuffer->Bind();
}
void Selector::UnBind()
{
    this->SelectorFrameBuffer->UnBind();
}