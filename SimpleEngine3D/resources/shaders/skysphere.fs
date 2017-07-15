#version 330 core

uniform sampler2D u_skysphereTexture;

in vec2 fs_texCoord;

out vec4 color;

void main()
{ 
    color = vec4(texture(u_skysphereTexture, fs_texCoord).rgb,1.0f);
}