#version 330 core

uniform sampler2D u_screenTexture;

in vec2 fs_texCoord;

out vec4 color;

void main()
{ 
    float gamma = 2.2f;
    float exposure = 1.0f;

	vec3 texel = texture(u_screenTexture,fs_texCoord).rgb;

    texel = vec3(1.0) - exp(-texel * exposure);

	vec3 pixelColor = pow(texel,vec3(1.0f/gamma));
    color = vec4(pixelColor,1.0f);
}