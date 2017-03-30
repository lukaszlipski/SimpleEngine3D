#version 330 core

uniform sampler2D u_positionTexture;
uniform sampler2D u_normalTexture;
uniform sampler2D u_albedoSpecularTexture;

uniform vec3 u_direction;
uniform float u_intensity;
uniform vec3 u_color;

uniform vec3 u_cameraPosition;

in vec2 fs_texCoord;

out vec4 color;

void main()
{ 
    vec3 position = texture(u_positionTexture, fs_texCoord).rgb;
    vec3 normal = normalize(texture(u_normalTexture, fs_texCoord).rgb) * 2.0f - 1.0f;
    vec3 albedo = texture(u_albedoSpecularTexture, fs_texCoord).rgb;
    float specular = texture(u_albedoSpecularTexture, fs_texCoord).a;

    vec3 lightDirection = normalize(-u_direction); 
    vec3 diffuse = albedo * u_color * u_intensity * max(dot(normal, lightDirection), 0.0);   

    color = vec4(diffuse,1);
}