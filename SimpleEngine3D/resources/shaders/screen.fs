#version 330 core

uniform sampler2D u_screenTexture;

in vec2 fs_texCoord;

out vec4 color;

void main()
{ 
    color = texture(u_screenTexture, fs_texCoord);
}