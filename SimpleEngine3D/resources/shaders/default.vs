#version 330 core
layout (location = 0) in vec3 a_position;
layout (location = 1) in vec3 a_normal;
layout (location = 2) in vec2 a_texCoord;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

out vec2 fs_texCoord;

void main()
{
	gl_Position = u_projection * u_view * u_model * vec4(a_position, 1.0f);
	fs_texCoord = a_texCoord;
}
