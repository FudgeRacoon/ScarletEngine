#include "core/renderer/Shader.hpp"
using namespace scarlet;

Shader::Shader(const char* vertexShader, const char* fragmentShader)
{
    this->programID = glCreateProgram();

    if(this->programID == 0)
    {
        std::cerr << "[WARNING]: Failed to create shader program" << '\n';
        return;
    }

    CreateShader(vertexShader, GL_VERTEX_SHADER);
    CreateShader(fragmentShader, GL_FRAGMENT_SHADER);

    glLinkProgram(this->programID);
    glValidateProgram(this->programID);

    int result;
    char buffer[512];
    glGetProgramiv(this->programID, GL_LINK_STATUS, &result);

    if(result == 0)
    {
        glGetProgramInfoLog(this->programID, 512, nullptr, buffer);
        std::cerr << "[WARNING]: Failed to link shaders\n" << buffer << '\n';
        return; 
    }
}
Shader::~Shader()
{
    glDeleteProgram(this->programID);
}

void Shader::CreateShader(const char* filepath, int shaderType)
{
    std::string source = ParseShader(filepath);
    if(source.empty())
        return;

    const char* source_c_str = source.c_str();

    int shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &source_c_str, nullptr);
    glCompileShader(shader);

    int result;
    char buffer[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);

    if(result == 0)
    {
        glGetShaderInfoLog(shader, 512, nullptr, buffer);

        switch(shaderType)
        {
            case GL_VERTEX_SHADER: 
            {
                std::cerr << "[WARNING]: Failed to compile vertex shader\n" << buffer << '\n';
                return;
            }
            case GL_FRAGMENT_SHADER:
            {
                std::cerr << "[WARNING]: Failed to compile fragment shader\n" << buffer << '\n';
                return;
            }
        }
    }

    glAttachShader(this->programID, shader);
    glDeleteShader(shader);
}
std::string Shader::ParseShader(const char* filepath)
{
    std::fstream file(filepath, std::ios::in);

    if(!file)
    {
        std::cerr << "[WARNING]: Failed to open shader file" << '\n';
        return "";
    }

    std::string line;
    std::stringstream ss;

    while(getline(file, line))
        ss << line << '\n';
    
    return ss.str();
}

void Shader::SetBool(std::string varName, int value)
{
    int uniformID = glGetUniformLocation(this->programID, varName.c_str());
    glUniform1i(uniformID, value);
}
void Shader::SetInt(std::string varName, int value)
{
    int uniformID = glGetUniformLocation(this->programID, varName.c_str());
    glUniform1i(uniformID, value);
}
void Shader::SetFloat(std::string varName, float value)
{
    int uniformID = glGetUniformLocation(this->programID, varName.c_str());
    glUniform1f(uniformID, value);
}
void Shader::SetVec2i(std::string varName, int x, int y)
{
    int uniformID = glGetUniformLocation(this->programID, varName.c_str());
    glUniform2i(uniformID, x, y);
}
void Shader::SetVec2f(std::string varName, float x, float y)
{
    int uniformID = glGetUniformLocation(this->programID, varName.c_str());
    glUniform2f(uniformID, x, y);
}
void Shader::SetVec4i(std::string varName, int x, int y, int z, int w)
{
    int uniformID = glGetUniformLocation(this->programID, varName.c_str());
    glUniform4i(uniformID, x, y, z, w);
}
void Shader::SetVec4f(std::string varName, float x, float y, float z, float w)
{
    int uniformID = glGetUniformLocation(this->programID, varName.c_str());
    glUniform4i(uniformID, x, y, z, w);
}
void Shader::SetMat4(std::string varName, float* value)
{
    int uniformID = glGetUniformLocation(this->programID, varName.c_str());
    glUniformMatrix4fv(uniformID, 1, false, value);
}

void Shader::Bind()
{
    glUseProgram(this->programID);
}
void Shader::UnBind()
{
    glUseProgram(0);
}