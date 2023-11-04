#ifndef TEXTURES_H
#define TEXTURES_H

#include "stb_image.h"
#include <GL/glew.h>
#include <cglm/cglm.h>

#ifdef __cplusplus
extern "C"
{
#endif

GLuint textureFromFile(const char * filename);

#ifdef __cplusplus
}
#endif

#endif