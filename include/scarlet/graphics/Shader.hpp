#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include "GL/glew.h"

#include "scarlet/utils/Logger.hpp"

namespace scarlet
{
    class Shader
    {
    private:
        uint32_t programID;

    private:
        static const char* defaultVertexShaderSource;

    public:
        Shader(const char* fragmentShader);
        ~Shader();

    private:
        void CreateShaderWithFileInternal(const char* filepath, int shaderType);
        void CreateShaderWithSourceInternal(const char* source, int shaderType);
        std::string ParseShaderInternal(const char* filepath);

    public:
        void SetBool(std::string varName, int value) const;
        void SetInt(std::string varName, int value) const;
        void SetFloat(std::string varName, float value) const;
        void SetVec2i(std::string varName, int x, int y) const;
        void SetVec2f(std::string varName, float x, float y) const;
        void SetVec4i(std::string varName, int x, int y, int z, int w) const;
        void SetVec4f(std::string varName, float x, float y, float z, float w) const;
        void SetMat4(std::string varName, const float* value) const;

    public:
        void Bind() const;
        void UnBind() const;
    };
}

#endif