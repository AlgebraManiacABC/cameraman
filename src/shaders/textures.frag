#version 330 core

in vec2 texCoord;

uniform sampler2D tex;

vec4 getTexture()
{
	return texture(tex, texCoord);
}