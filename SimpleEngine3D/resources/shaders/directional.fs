#version 330 core

uniform sampler2D u_positionTexture;
uniform sampler2D u_normalTexture;
uniform sampler2D u_albedoTexture;
uniform sampler2D u_metallicRoughnessAOTexture;

uniform vec3 u_direction;
uniform float u_intensity;
uniform vec3 u_color;

uniform vec3 u_cameraPosition;

uniform mat4 u_view;
uniform mat4 u_projection;

uniform sampler2D u_shadow_map;

in vec2 fs_texCoord;

out vec4 color;

const float PI = 3.14159265359;

// Trowbridge-Reitz GGX
float NormalDistributionFunction(vec3 N, vec3 H, float a)
{
    float NDotH  = max(dot(N, H), 0.0);

    float denom = (NDotH*NDotH * (a*a - 1.0) + 1.0);
    denom = PI * denom * denom;
	
    return (a*a) / denom;
}

// Schlick-GGX
 float GeometryFunction(vec3 N, vec3 V, vec3 L, float a)
 {
    float k = ((a + 1) * (a + 1))/8.0f;
    float NDotV = max(dot(N, V), 0);
    float NDotL = max(dot(N, L), 0);
    float smith1 = NDotV / (NDotV * (1.0f - k) + k);
    float smith2 = NDotL / (NDotL * (1.0f - k) + k);

    return smith2 * smith1;
 }

 // Fresnel-Schlick
 vec3 FresnelEquation(vec3 N, vec3 V, vec3 F0)
 {
    return F0 + (1.0 - F0) * pow(1.0 - max(dot(N, V), 0.0), 5.0);
 }

 // Shadow
 float CalcShadow(vec3 P,vec3 N)
 {
    vec4 lightSpaceCoord = u_projection * u_view * vec4(P,1.0f);
    lightSpaceCoord = lightSpaceCoord * 0.5f + 0.5f;
    if(lightSpaceCoord.z > 1.0f) return 1.0f;
    float bias = 0.001f;
    return lightSpaceCoord.z - bias > texture(u_shadow_map,lightSpaceCoord.xy).r ? 0.0f : 1.0f;
 }

void main()
{ 
    vec3 position = texture(u_positionTexture, fs_texCoord).rgb;
    vec3 normal = normalize(texture(u_normalTexture, fs_texCoord).rgb);
    vec3 albedo = texture(u_albedoTexture, fs_texCoord).rgb;
    float metallic = texture(u_metallicRoughnessAOTexture, fs_texCoord).r;
    float roughness = clamp(texture(u_metallicRoughnessAOTexture, fs_texCoord).g,0.025f,1.0f);
    float ao = texture(u_metallicRoughnessAOTexture, fs_texCoord).b;

    vec3 F0 = mix(vec3(0.04f), albedo, metallic);
    vec3 V = normalize(u_cameraPosition - position);
    vec3 L = normalize(-u_direction);
    vec3 H = normalize(V + L);
    vec3 N = normal;

    vec3 radiance = u_color * u_intensity;

    // Cook-Torrance BRDF
    float NDF = NormalDistributionFunction(N,H,roughness);
    float G = GeometryFunction(N,V,L,roughness);
    vec3 F = FresnelEquation(H,V,F0);

    vec3 kS = F;
    vec3 kD = vec3(1.0f) - kS;
    kD *= 1.0f - metallic;

    vec3 specular = (NDF * G * F) / (4 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0) + 0.001);

    float shadow = CalcShadow(position,normal);

    color = vec4( shadow * (kD * albedo / PI + specular) * radiance * max(dot(N, L), 0.0),1);
}