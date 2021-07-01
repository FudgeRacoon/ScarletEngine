#version 330 core

in vec2 fTexCoord;

out vec4 color;

uniform vec4 u_color;
uniform sampler2D uTexSampler;

void main()
{
    vec4 c = u_color;
    color = texture(uTexSampler, fTexCoord) * c;
}