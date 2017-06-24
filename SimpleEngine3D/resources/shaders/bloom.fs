#version 330 core

uniform sampler2D u_screenTexture;

in vec2 fs_texCoord;

out vec4 color;

void main()
{ 
	vec3 texel = texture(u_screenTexture,fs_texCoord).rgb;
    //float brightness = dot(texel, vec3(0.0f)/3.0f);
    float brightness = dot(texel, vec3(0.2126f, 0.7152f, 0.0722f));
    color = vec4(texel,1.0f) * brightness;
}