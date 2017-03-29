#version 330 core

uniform sampler2D u_screenTexture;

in vec2 fs_texCoord;

out vec4 color;

void main()
{ 
    float gamma = 2.2;

	vec4 texel = texture(u_screenTexture,fs_texCoord);
	vec3 pixelColor = pow(texel.rgb,vec3(1/gamma));
    color = vec4(pixelColor,texel.a);
    color = texture(u_screenTexture, fs_texCoord);
}