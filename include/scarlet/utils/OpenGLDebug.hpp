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
    inline bool GLLogCall()
    {
        while(GLenum error = glGetError())
        {
            scarlet::Logger::LogError("Opengl error occured with error code %d", error);
            return false;
        }

        return true;
    }
}

#endif