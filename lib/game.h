#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#define FPS (60.0)

/**
 * Main game loop.
 * 
 * @param w The `SDL_Window *` created with a gl context
 */
void gameLoop(SDL_Window *w);

#endif