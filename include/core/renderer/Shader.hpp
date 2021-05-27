#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include "GL/glew.h"

namespace scarlet
{
    class Shader
    {
    private:
        uint32_t programID;

    public:
        Shader(const char* vertexShader, const char* fragmentShader);
        ~Shader();

    private:
        void CreateShader(const char* filepath, int shaderType);
        std::string ParseShader(const char* filepath);

    public:
        void SetBool(std::string varName, int value);
        void SetInt(std::string varName, int value);
        void SetFloat(std::string varName, float value);
        void SetVec2i(std::string varName, int x, int y);
        void SetVec2f(std::string varName, float x, float y);
        void SetVec4i(std::string varName, int x, int y, int z, int w);
        void SetVec4f(std::string varName, float x, float y, float z, float w);
        void SetMat4(std::string varName, float* value);

    public:
        void Bind();
        void UnBind();
    };
}

#endif