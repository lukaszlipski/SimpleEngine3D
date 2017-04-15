#version 330 core
layout (location = 0) in vec3 a_position;
layout (location = 1) in vec3 a_normal;
layout (location = 2) in vec2 a_texCoord;
layout (location = 3) in vec3 a_tangent;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

out vec3 fs_position;
out vec2 fs_texCoord;
out mat3 fs_tbn;

void main()
{
	gl_Position = u_projection * u_view * u_model * vec4(a_position, 1.0f);

	vec4 globalPosition = u_model * vec4(a_position, 1.0f);
	fs_position = globalPosition.xyz;

	mat3 normalMatrix = transpose(inverse(mat3(u_model)));
	vec3 normal = normalize(normalMatrix * a_normal);
	vec3 tangent = normalize(normalMatrix * a_tangent);
	tangent = normalize(tangent - dot(tangent,normal) * normal);

	vec3 biTangent = cross(tangent,normal);
	fs_tbn = mat3(tangent,biTangent,normal);

	fs_texCoord = a_texCoord;
}
