#include "scarlet/graphics/GraphicsContext.hpp"
using namespace scarlet;

FrameBuffer* GraphicsContext::renderTarget = nullptr;
Vector4 GraphicsContext::viewport;

void GraphicsContext::OnInit()
{
    glewExperimental = true;
    if(glewInit() != 0)
    {
        Logger::LogFatal("Cannot Initialize Glew.");
        Window::Quit();
    }

    FrameBufferSpecification spec; 

    spec.width = Window::GetWidth();
    spec.height = Window::GetHeight();
    spec.type = GL_UNSIGNED_BYTE;
    spec.format = GL_RGBA;
    spec.internalFormat = GL_RGBA;
    
    FrameBuffer* fbo = new FrameBuffer();
    fbo->AttachColorTexture(spec);
    
    renderTarget = fbo;
}

Vector4 GraphicsContext::GetViewPort()
{
    return viewport;
}
FrameBuffer* GraphicsContext::GetRenderTarget()
{
    return renderTarget;
}
uint32 GraphicsContext::GetMaxTextureSlots()
{
    int maxSlots;
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &maxSlots);
    return maxSlots;
}
const byte* GraphicsContext::GetGlVersion()
{
    return glGetString(GL_VERSION);
}

void GraphicsContext::SetViewPort(uint32 x, uint32 y, uint32 width, uint32 height)
{
    SCARLET_CORE_ASSERT((x >= 0 && y >= 0), "Viewport origin must be positive.");

    viewport = Vector4(x, y, width, height);
    glViewport(x, y, width, height);
}
void GraphicsContext::SetBlendingFunction(GraphicsBlendFunction sFactor, GraphicsBlendFunction dFactor)
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

void GraphicsContext::ClearBuffers(GraphicsBufferType buffers)
{
    glClear(buffers);
}
void GraphicsContext::SwapBuffers()
{
    SDL_GL_SwapWindow(Window::GetSDLWindow());
}