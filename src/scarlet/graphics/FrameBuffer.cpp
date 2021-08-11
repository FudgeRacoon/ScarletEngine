#include "scarlet/graphics/FrameBuffer.hpp"
using namespace scarlet;

FrameBuffer::FrameBuffer() 
{
    GLCALL(glGenFramebuffers(1, &this->frameBufferID));
}
FrameBuffer::~FrameBuffer()
{
    GLCALL(glDeleteFramebuffers(1, &this->frameBufferID));
    GLCALL(glDeleteTextures(1, &this->colorAttachmentID));
}

uint32 FrameBuffer::GetFrameBufferID()
{
    return this->frameBufferID;
}
uint32 FrameBuffer::GetColorAttachmentID()
{
    return this->colorAttachmentID;
}

bool FrameBuffer::CheckStatus()
{
    GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, this->frameBufferID));

    GLenum statusCode;

    if((statusCode =  glCheckFramebufferStatus(GL_FRAMEBUFFER)) != GL_FRAMEBUFFER_COMPLETE)
    {
        char* status;
        switch(statusCode)
        {
            case GL_FRAMEBUFFER_UNDEFINED:                     status = "FRAMEBUFFER_UNDEFINED\0"; break;
            case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:         status = "FRAMEBUFFER_INCOMPLETE_ATTACHMENT\0"; break;
            case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT: status = "FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT\0"; break;
            case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:        status = "FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER\0"; break;
            case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:        status = "FRAMEBUFFER_INCOMPLETE_READ_BUFFER\0"; break;
            case GL_FRAMEBUFFER_UNSUPPORTED:                   status = "FRAMEBUFFER_UNSUPPORTED\0"; break;
            case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:        status = "FRAMEBUFFER_INCOMPLETE_MULTISAMPLE\0"; break;
        }

        Logger::LogError("Opengl FrameBuffer Error: %s", status);
        delete[] status;

        GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, 0));

        return false;
    }

    GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, 0));

    return true;
}

void FrameBuffer::AttachColorTexture(FrameBufferSpecification& spec)
{
    this->width = spec.width;
    this->height = spec.height;

    GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, this->frameBufferID));

    GLCALL(glGenTextures(1, &this->colorAttachmentID));
    GLCALL(glBindTexture(GL_TEXTURE_2D, this->colorAttachmentID));

    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
    GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
    
    GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, spec.internalFormat, this->width, this->height, 0, spec.format, spec.type, nullptr));

    GLCALL(glBindTexture(GL_TEXTURE_2D, 0));

    GLCALL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->colorAttachmentID, 0));

    GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

int FrameBuffer::ReadPixel(Graphics_Format format, Graphics_Type type, int x, int y, uint32 colorAttachmentIndex)
{
    SCARLET_CORE_ASSERT((x >= 0 && x < this->width) && (y >= 0 && y < this->height), "Pixel coordinates are out of bound.");

    int pixelData;

    GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, this->frameBufferID));

    GLCALL(glReadBuffer(GL_COLOR_ATTACHMENT0 + colorAttachmentIndex));
    GLCALL(glReadPixels(x, y, 1, 1, format, type, &pixelData));
    
    GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, 0));

    return pixelData;
}

void FrameBuffer::Bind()
{
    GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, this->frameBufferID));
}
void FrameBuffer::UnBind()
{
    GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}
