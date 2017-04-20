#version 330 core
layout (location = 0) out vec3 gb_Position;
layout (location = 1) out vec3 gb_Normal;
layout (location = 2) out vec3 gb_Albedo;
layout (location = 3) out vec3 gb_MetallicRoughnessAO;

uniform sampler2D u_albedo;
uniform sampler2D u_normal;
uniform sampler2D u_metallic;
uniform sampler2D u_roughness;
uniform sampler2D u_ambientOcclusion;

in vec3 fs_position;
in vec2 fs_texCoord;
in mat3 fs_tbn;

void main()
{
	gb_Position = fs_position;

	vec3 normalTexel = texture(u_normal,fs_texCoord).rgb;
	//vec3 normal = normalize( vec3(normalTexel.x,1-normalTexel.y,normalTexel.z) * 2.0f - 1.0f );
	vec3 normal = normalize( normalTexel * 2.0f - 1.0f );
	gb_Normal = normalize( fs_tbn * normal );

	gb_Albedo.rgb = texture(u_albedo,fs_texCoord).rgb;
	
	gb_MetallicRoughnessAO.r = texture(u_metallic,fs_texCoord).r;
	gb_MetallicRoughnessAO.g = texture(u_roughness,fs_texCoord).r;
	gb_MetallicRoughnessAO.b = texture(u_ambientOcclusion,fs_texCoord).r;

}
