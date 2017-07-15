#version 330 core
layout (location = 0) in vec3 a_position;
layout (location = 1) in vec3 a_normal;
layout (location = 2) in vec2 a_texCoord;

uniform mat4 u_view;
uniform mat4 u_projection;
uniform mat4 u_correction;

out vec2 fs_texCoord;

void main()
{
    fs_texCoord = a_texCoord;
    mat3 view = mat3(u_view); 
    vec4 pos =  u_projection * mat4(view) * u_correction * vec4(a_position, 1.0);
    gl_Position = pos.xyww;

}  