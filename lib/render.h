#ifndef RENDER_H
#define RENDER_H

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include "button.h"

#ifdef __cplusplus
extern "C"
{
#endif

extern GLuint actorVAO;
extern GLuint squareVAO;
extern GLuint backgroundVertexBuffer;
extern GLuint cameramanVertexBuffer;
extern GLuint rectElementBuffer;

void initRenderer(void);

void renderBackground(GLuint texture);

void renderButton(button *b);

#ifdef __cplusplus
}
#endif

#endif