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
uniform sampler2D u_height;
uniform vec3 u_cameraPosition;
uniform float u_heightScale;

in vec3 fs_position;
in vec2 fs_texCoord;
in mat3 fs_tbn;

vec2 ParallaxOcclusionMapping(vec2 TC, vec3 V);

void main()
{
	gb_Position = fs_position;

	vec3 V = normalize( transpose(fs_tbn) * (fs_position - u_cameraPosition));
	vec2 newTC = ParallaxOcclusionMapping(fs_texCoord,V);

	vec3 normalTexel = texture(u_normal,newTC).rgb;
	//vec3 normal = normalize( vec3(normalTexel.x,1-normalTexel.y,normalTexel.z) * 2.0f - 1.0f );
	vec3 normal = normalize( normalTexel * 2.0f - 1.0f );
	gb_Normal = normalize( fs_tbn * normal );

	gb_Albedo.rgb = texture(u_albedo,newTC).rgb;
	
	gb_MetallicRoughnessAO.r = texture(u_metallic,newTC).r;
	gb_MetallicRoughnessAO.g = texture(u_roughness,newTC).r;
	gb_MetallicRoughnessAO.b = texture(u_ambientOcclusion,newTC).r;

}

vec2 ParallaxOcclusionMapping(vec2 TC, vec3 V)
{
	const float minLayers = 8.0f;
    const float maxLayers = 32.0f;

	float layers = mix(maxLayers, minLayers, abs(dot(vec3(0.0, 0.0, 1.0), V)));  
	float dDepth = 1.0f / layers;

	vec2 cTC = TC;
	vec2 dTC = u_heightScale * vec2(V.x,-V.y) / V.z / layers;
    float depthValue = 1 - texture(u_height, cTC).r;
	float depthLayer = 0.0f;

	while(depthLayer < depthValue)
    {
        cTC -= dTC;
        depthLayer += dDepth;  
        depthValue = 1 - texture(u_height, cTC).r;  
    }

	vec2 prevTC = cTC + dTC;

	float afterDepth  = depthValue - depthLayer;
    float beforeDepth = 1 - texture(u_height, prevTC).r - depthLayer + dDepth;

	float weight = afterDepth / (afterDepth - beforeDepth);

    return prevTC * weight + cTC * (1.0 - weight);

}