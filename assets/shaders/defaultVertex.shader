#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 fTexCoord;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_proj;

void main()
{
    vec4 transformedVertex = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    
    transformedVertex = u_model * transformedVertex;
    transformedVertex = u_view * transformedVertex;
    transformedVertex = u_proj * transformedVertex;

    gl_Position = transformedVertex;

    fTexCoord = aTexCoord;
};