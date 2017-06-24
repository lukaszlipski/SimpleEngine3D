#version 330 core

uniform sampler2D u_screenTexture;
uniform bool u_pass;

in vec2 fs_texCoord;

out vec4 color;

//float weight[5] = float[](0.227027, 0.1945946, 0.1216216, 0.054054, 0.016216);
float weight[6] = float[](0.198596, 0.175713, 0.121703, 0.065984, 0.028002, 0.0093);

void main()
{ 
	vec2 texelSize = 1.0f / textureSize(u_screenTexture,0);
    vec3 result = texture(u_screenTexture, fs_texCoord).rgb * weight[0];

    if(!u_pass)
    {
        for(int i=1;i<6;++i)
        {
            result += texture(u_screenTexture, fs_texCoord + vec2(texelSize.x * i, 0.0f)).rgb * weight[i];
            result += texture(u_screenTexture, fs_texCoord - vec2(texelSize.x * i, 0.0f)).rgb * weight[i];
        }
    }
    else
    {
        for(int i=1;i<6;++i)
        {
            result += texture(u_screenTexture, fs_texCoord + vec2(0.0f,texelSize.x * i)).rgb * weight[i];
            result += texture(u_screenTexture, fs_texCoord - vec2(0.0f,texelSize.x * i)).rgb * weight[i];
        }
    }
    color = vec4(result,1.0f);
}