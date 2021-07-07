#version 330 core

in vec2 fTexCoord;

out vec4 color;

uniform vec4 u_color;
uniform sampler2D uTexSampler;

void main()
{
    vec4 texel = texture(uTexSampler, fTexCoord);
    
    if(texel.a < 0.1)
        discard;

    color = texel * u_color;
}