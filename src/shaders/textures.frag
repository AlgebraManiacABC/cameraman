#version 330 core

in vec2 TexCoord;

uniform sampler2D tex;

vec4 getTexture()
{
	return texture(tex, TexCoord);
}