#version 330 core

in vec2 fTexCoord;

out vec4 color;

uniform vec4 u_color;
uniform sampler2D uTexSampler;

void main()
{
    color = texture(uTexSampler, fTexCoord) * u_color;
}