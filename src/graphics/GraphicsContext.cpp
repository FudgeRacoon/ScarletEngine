#include "scarlet/graphics/GraphicsContext.hpp"
using namespace scarlet;

Vector4 GraphicsContext::viewport;

void GraphicsContext::Init()
{
    glewExperimental = true;
    if(glewInit() != 0)
    {
        Logger::LogFatal("Cannot Initialize Glew.");
        Window::Get()->Quit();
    }
}

Vector4 GraphicsContext::GetViewPort()
{
    return viewport;
}

void GraphicsContext::SetViewPort(uint32 x, uint32 y, uint32 width, uint32 height)
{
    viewport = Vector4(x, y, width, height);
    glViewport(x, y, width, height);
}
void GraphicsContext::SetBlendingFunction(uint32 sFactor, uint32 dFactor)
{
    glBlendFunc(sFactor, dFactor);
}
void GraphicsContext::SetClearColor(Color color)
{
    glClearColor(
        (float)(color.r / 255.0f), 
        (float)(color.g / 255.0f), 
        (float)(color.b / 255.0f), 
        1.0f
    );
}

void GraphicsContext::EnableBlending(bool enable)
{
    switch(enable)
    {
        case true: glEnable(GL_BLEND); break;
        case false: glDisable(GL_BLEND); break;
    }
}

void GraphicsContext::ClearBuffers(uint32 buffers)
{
    glClear(buffers);
}
void GraphicsContext::SwapBuffers()
{
    SDL_GL_SwapWindow(Window::Get()->GetSDLWindow());
}
