#version 330 core

in vec4 fColor;
in vec2 fTexCoord;

uniform sampler2D uTexSampler;

void main()
{
    gl_FragColor = texture(uTexSampler, fTexCoord);
}