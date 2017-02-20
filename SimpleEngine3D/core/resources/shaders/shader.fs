#version 330 core

uniform sampler2D u_texture;
uniform sampler2D u_tex;

in vec2 texCoord;

out vec4 color;

void main()
{
    color = texture(u_texture,texCoord) * texture(u_tex,texCoord);
}
