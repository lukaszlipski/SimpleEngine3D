#version 330 core

uniform sampler2D u_texture1;
uniform sampler2D u_texture2;

in vec2 fs_texCoord;

out vec4 color;

void main()
{
    color = texture(u_texture1,fs_texCoord) * texture(u_texture2,fs_texCoord);
}
