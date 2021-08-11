#include "scarlet/graphics/GraphicsContext.hpp"
using namespace scarlet;

Vector4 GraphicsContext::viewport;

void GraphicsContext::OnInit()
{
    Logger::LogInfo("Intitializing Graphics Context Subsystem...");

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
uint32 GraphicsContext::GetMaxTextureSlots()
{
    int maxSlots;
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &maxSlots);
    return maxSlots;
}

void GraphicsContext::SetViewPort(uint32 x, uint32 y, uint32 width, uint32 height)
{
    viewport = Vector4(x, y, width, height);
    glViewport(x, y, width, height);
}
void GraphicsContext::SetBlendingFunction(Graphics_BlendFunction sFactor, Graphics_BlendFunction dFactor)
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

void GraphicsContext::ClearBuffers(Graphics_BufferType buffers)
{
    glClear(buffers);
}
void GraphicsContext::SwapBuffers()
{
    SDL_GL_SwapWindow(Window::Get()->GetSDLWindow());
}

void GraphicsContext::DrawArrays(Graphics_DrawMode mode, VertexArray* vao, uint32 count)
{
    vao->Bind();
    GLCALL(glDrawArrays(mode, 0, count));
    vao->UnBind();
}
void GraphicsContext::DrawElements(Graphics_DrawMode mode, VertexArray* vao, IndexBuffer* ibo, uint32 count)
{
    vao->Bind();
    ibo->Bind();
    GLCALL(glDrawElements(mode, count, GL_UNSIGNED_INT, 0));
    ibo->UnBind();
    vao->UnBind();
}