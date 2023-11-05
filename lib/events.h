#ifndef EVENTS_H
#define EVENTS_H

#include <stdbool.h>
#include <SDL2/SDL.h>

#ifdef __cplusplus
extern "C"
{
#endif

extern bool windowResizedThisFrame;

/**
 * Polls all incoming events through SDL
 * 
 * @param shouldClose Address to a bool which is set if SDL_QUIT (etc) is received
 * @param cam The camera struct, which will be updated depending on movement
 * 
 * @returns The number of events polled 
 */
int handleEvents(bool *shouldClose, Uint32 * buttonsHeld);

#ifdef __cplusplus
}
#endif

#endif