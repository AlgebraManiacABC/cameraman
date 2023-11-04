#define STB_IMAGE_IMPLEMENTATION
#include "textures.h"
#include "debug.h"

GLuint textureFromFile(const char * filename)
{
	int width, height;
	int numChannels;
	unsigned char * data = stbi_load(filename,&width,&height,&numChannels,0);
	if(!data)
	{
		setError(ERR_MESG,"Error retrieving data from \"%s\"!\n",filename);
		return 0;
	}
	//fprintf(stderr,"numChannels: %d\n",numChannels);
	GLushort bitDepth;
	switch(numChannels)
	{
		case 1:
			bitDepth = GL_LUMINANCE;
			break;
		case 3:
			bitDepth = GL_RGB;
			break;
		case 4:
			bitDepth = GL_RGBA;
			break;
		default:
			setError(ERR_MESG,"Unanticipated bit depth of %d\n",numChannels);
			return 0;
	}

	GLuint texture;
	glGenTextures(1,&texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, (vec4){1.0f,0.0f,0.0f,1.0f});
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, bitDepth, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D,0);

	return texture;
}