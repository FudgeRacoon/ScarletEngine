#ifndef OPENGLDEBUG_HPP
#define OPENGLDEBUG_HPP

#include "GL/glew.h"

#include "scarlet/utils/Logger.hpp"

namespace scarlet
{
    inline void GLClearError()
    {
        while(glGetError() != GL_NO_ERROR);
    }
    inline bool GLLogCall(const char* file, int line)
    {
        GLenum errorCode;

        while((errorCode = glGetError()) != GL_NO_ERROR)
        {
            char* error;

            switch(errorCode)
            {
                case GL_INVALID_ENUM:                  error = "INVALID_ENUM\0"; break;
                case GL_INVALID_VALUE:                 error = "INVALID_VALUE\0"; break;
                case GL_INVALID_OPERATION:             error = "INVALID_OPERATION\0"; break;
                case GL_STACK_OVERFLOW:                error = "STACK_OVERFLOW\0"; break;
                case GL_STACK_UNDERFLOW:               error = "STACK_UNDERFLOW\0"; break;
                case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY\0"; break;
                case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION\0"; break;
            }

            Logger::LogError("OpenGL Error: %s | %s (%d)", error, file, line);
            delete[] error;
            return false;
        }

        return true;
    }
}

#endif