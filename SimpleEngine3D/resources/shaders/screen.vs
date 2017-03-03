
#version 330 core
layout (location = 0) in vec2 a_position;
layout (location = 1) in vec2 a_texCoord;

out vec2 fs_texCoord;

void main()
{
    gl_Position = vec4(a_position.x, a_position.y, 0.0f, 1.0f); 
    fs_texCoord = a_texCoord;
}  