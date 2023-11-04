#ifndef WINDOW_H
#define WINDOW_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <GL/glew.h>
#include <SDL2/SDL.h>

/**
 * Initualizes SDL and creates an SDL window with GL context.
 * Additionally initializes glew!
 * 
 * @param SDL_initFlags Flags to send to `SDL_Init()`
 * @param SDL_winFlags Flags to send to `SDL_CreateWindow()`
 * @param winTitle Title to give the initial window
 * @param win_x initial x position of the window
 * @param win_y initial y position of the window
 * @param win_w initial width of the window
 * @param win_h initial height of the window
 * @param w Address to a `(SDL_Window *)`, which will be created
 * @param glContext Address to an `SDL_GLContext`, which will be created
 * 
 * @return `EXIT_SUCCESS` (`0`) if everything initialized as expected. Otherwise, you will have to check the error with `whatHappened()`
 */
int initWindow(Uint32 SDL_initFlags,
				Uint32 SDL_winFlags,
				const char * winTitle,
				Uint32 win_x, Uint32 win_y, Uint32 win_w, Uint32 win_h,
				SDL_Window ** w, SDL_GLContext * glContext);

#ifdef __cplusplus
}
#endif

#endif
