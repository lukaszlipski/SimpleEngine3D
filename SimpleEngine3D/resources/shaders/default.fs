#version 330 core
layout (location = 0) out vec3 gb_Position;
layout (location = 1) out vec3 gb_Normal;
layout (location = 2) out vec4 gb_AlbedoSpec;

uniform sampler2D u_albedo;
uniform sampler2D u_normal;
uniform sampler2D u_specular;
uniform vec3 u_color;

in vec3 fs_position;
in vec3 fs_normal;
in vec2 fs_texCoord;

out vec4 color;

void main()
{
	gb_Position = fs_position;
	gb_Normal = normalize(fs_normal) * 0.5f + 0.5f;
	gb_AlbedoSpec.rgb = texture(u_albedo,fs_texCoord).rgb;
	//gb_AlbedoSpec.a = texture(u_specular, TexCoords).r
}
