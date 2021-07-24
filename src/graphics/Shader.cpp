#include "scarlet/graphics/Shader.hpp"
using namespace scarlet;

const char* Shader::defaultVertexShaderSource =
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec2 aTexCoord;\n"
"out vec2 fTexCoord;\n"
"uniform mat4 u_model;\n"
"uniform mat4 u_view;\n"
"uniform mat4 u_proj;\n"
"void main()\n"
"{\n"
"   vec4 transformedVertex = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"   transformedVertex = transformedVertex * u_model;\n"
"   transformedVertex = transformedVertex * u_view;\n"
"   transformedVertex = transformedVertex * u_proj;\n"
"   gl_Position = transformedVertex;\n"
"   fTexCoord = aTexCoord;\n"
"}\0";

Shader::Shader(const char* fragmentShader)
{
    this->programID = glCreateProgram();

    if(this->programID == 0)
    {
        Logger::LogError("Failed to create shader program.");
        return;
    }

    CreateShaderWithSourceInternal(defaultVertexShaderSource, GL_VERTEX_SHADER);
    CreateShaderWithFileInternal(fragmentShader, GL_FRAGMENT_SHADER);

    glLinkProgram(this->programID);
    glValidateProgram(this->programID);

    int result;
    char buffer[512];
    glGetProgramiv(this->programID, GL_LINK_STATUS, &result);

    if(result == 0)
    {
        glGetProgramInfoLog(this->programID, 512, nullptr, buffer);
        Logger::LogError("Failed to link Shader\n%s", buffer);
        return;
    }
}
Shader::~Shader()
{
    glDeleteProgram(this->programID);
}

void Shader::CreateShaderWithFileInternal(const char* filepath, int shaderType)
{
    std::string source = ParseShaderInternal(filepath);
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
        Logger::LogError("Failed to compile Fragment Shader.\n%s", buffer);
        return;
    }

    glAttachShader(this->programID, shader);
    glDeleteShader(shader);
}
void Shader::CreateShaderWithSourceInternal(const char* source, int shaderType)
{
    int shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    int result;
    char buffer[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);

    if(result == 0)
    {
        glGetShaderInfoLog(shader, 512, nullptr, buffer);
        Logger::LogError("Failed to compile Vertex Shader.\n%s", buffer);
        return;
    }

    glAttachShader(this->programID, shader);
    glDeleteShader(shader);
}
std::string Shader::ParseShaderInternal(const char* filepath)
{
    std::fstream file(filepath, std::ios::in);

    if(!file)
    {
        Logger::LogError("Failed to open shader file.");
        return "";
    }

    std::string line;
    std::stringstream ss;

    while(getline(file, line))
        ss << line << '\n';
    
    return ss.str();
}

void Shader::SetBool(std::string varName, int value) const
{
    int uniformID = glGetUniformLocation(this->programID, varName.c_str());
    glUniform1i(uniformID, value);
}
void Shader::SetInt(std::string varName, int value) const
{
    int uniformID = glGetUniformLocation(this->programID, varName.c_str());
    glUniform1i(uniformID, value);
}
void Shader::SetFloat(std::string varName, float value) const
{
    int uniformID = glGetUniformLocation(this->programID, varName.c_str());
    glUniform1f(uniformID, value);
}
void Shader::SetVec2i(std::string varName, int x, int y) const
{
    int uniformID = glGetUniformLocation(this->programID, varName.c_str());
    glUniform2i(uniformID, x, y);
}
void Shader::SetVec2f(std::string varName, float x, float y) const
{
    int uniformID = glGetUniformLocation(this->programID, varName.c_str());
    glUniform2f(uniformID, x, y);
}
void Shader::SetVec4i(std::string varName, int x, int y, int z, int w) const
{
    int uniformID = glGetUniformLocation(this->programID, varName.c_str());
    glUniform4i(uniformID, x, y, z, w);
}
void Shader::SetVec4f(std::string varName, float x, float y, float z, float w) const
{
    int uniformID = glGetUniformLocation(this->programID, varName.c_str());
    glUniform4f(uniformID, x, y, z, w);
}
void Shader::SetMat4(std::string varName, Matrix4 m) const
{
    int uniformID = glGetUniformLocation(this->programID, varName.c_str());
    glUniformMatrix4fv(uniformID, 1, false, m.GetValuePointer());
}

void Shader::Bind() const
{
    glUseProgram(this->programID);
}
void Shader::UnBind() const
{
    glUseProgram(0);
}