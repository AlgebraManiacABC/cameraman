#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#define FPS (60.0)

//	Finite state machine status list
#define STATUS_GAME_EXIT        (0)
#define STATUS_MAIN_MENU        (1)
#define STATUS_LEVEL_SELECT     (2)
#define STATUS_LEVEL_SPRINT     (3)
#define STATUS_LEVEL_SKIING     (4)
#define STATUS_LEVEL_SHARK      (5)
#define STATUS_LEVEL_VOLCANO    (6)
#define STATUS_LEVEL_NUCLEAR    (7)
#define STATUS_LEVEL_ROCKET     (8)
#define STATUS_LEVEL_BLACK_HOLE (9)

#define LEVEL_COUNT (1)

extern GLuint STATUS_LEVEL_PICK[LEVEL_COUNT];

//	TODO: turn into 7, the anticipated amount, as levels are implemented
#define LEVEL_ID_SPRINT     (0)
#define LEVEL_ID_SKIING     (1)
#define LEVEL_ID_SHARK      (2)
#define LEVEL_ID_VOLCANO    (3)
#define LEVEL_ID_NUCLEAR    (4)
#define LEVEL_ID_ROCKET     (5)
#define LEVEL_ID_BLACK_HOLE (6)

//	Held button bitfield
#define HOLDING_SPACE  (0)
#define HOLDING_W      (1)
#define HOLDING_A      (1 << 1)
#define HOLDING_S      (1 << 2)
#define HOLDING_D      (1 << 3)
#define HOLDING_LSHIFT (1 << 4)
#define HOLDING_RETURN (1 << 5)

/**
 * Initializes all important game assets, then opens the main menu
 */
void playGame(void);

//	All functions after this point return a status,
//	which tells the playGame function where to go next.

GLuint mainMenu(void);

GLuint levelSelect(void);

GLuint levelSprint(void);

#endif