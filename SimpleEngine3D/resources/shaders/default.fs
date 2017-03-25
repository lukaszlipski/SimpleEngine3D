#version 330 core

uniform sampler2D u_texture1;
uniform sampler2D u_texture2;
uniform vec3 u_color;

in vec2 fs_texCoord;

out vec4 color;

void main()
{
	float gamma = 2.2;

	vec4 texel = texture(u_texture1,fs_texCoord);
	vec3 pixelColor = pow(texel.rgb * u_color,vec3(1/gamma));
    color = vec4(pixelColor,texel.a);
}
