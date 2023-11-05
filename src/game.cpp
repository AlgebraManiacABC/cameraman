#include "game.h"
#include "shaders.h"
#include "debug.h"
#include "events.h"
#include "assets.h"
#include "render.h"
#include "Physics.h"
#include "Rect.h"
#include "main.h"

GLuint (*fnPointers[])() =
{
	NULL,
	mainMenu,
	levelSelect,
	levelSprint
};

void playGame()
{
	int ww, wh;
	SDL_GetWindowSize(w,&ww,&wh);

	initRenderer();
	if(!loadUniversalShaders()) return;
	if(loadAssets()) return;

	GLuint status = STATUS_MAIN_MENU;
	while(status != STATUS_GAME_EXIT)
	{
		status = fnPointers[status]();
		//switch(status)
		//{
		//	case STATUS_MAIN_MENU:
		//		status = mainMenu(w);
		//		break;
		//	case STATUS_LEVEL_SELECT:
		//		status = levelSelect(w);
		//		break;
		//	case STATUS_GAME_EXIT:
		//	default:
		//		return;
		//}
	}
}

GLuint mainMenu()
{
	//fprintf(stderr,"Main Menu\n");
	Uint32 buttonsHeld = (0b0);
	bool shouldClose = false;
	while(!shouldClose)
	{
		(void)handleEvents(&shouldClose, &buttonsHeld);
		if(shouldClose) return STATUS_GAME_EXIT;

		if(buttonsHeld & HOLDING_RETURN) return STATUS_LEVEL_SELECT;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		renderBackground(textureList[TEX_ID_MAIN_MENU_BG]);
		SDL_GL_SwapWindow(w);
		SDL_Delay(1000/FPS);
	}
	return STATUS_GAME_EXIT;
}

GLuint levelSelect()
{
	//fprintf(stderr,"Level Select\n");
	Uint32 buttonsHeld = (0b0);
	bool shouldClose = false;
	while(!shouldClose)
	{
		(void)handleEvents(&shouldClose, &buttonsHeld);
		if(shouldClose) return STATUS_GAME_EXIT;

		if(buttonsHeld & HOLDING_RETURN) return STATUS_LEVEL_SPRINT;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		renderBackground(textureList[TEX_ID_LEVEL_SELECT_BG]);
		SDL_GL_SwapWindow(w);
		SDL_Delay(1000/FPS);
	}
	return STATUS_GAME_EXIT;
}

GLuint levelSprint()
{
	Physics physics {};
	vec2 pos = { 0.0, 0.0 };
	Rect cameraman {pos, 1/8.0, 1/4.0, false, textureList[TEX_ID_CAMERAMAN_R1], cameramanVertexBuffer};
	physics.addBody(&cameraman);
	
	Uint32 buttonsHeld = (0b0);
	bool shouldClose = false;
	while(!shouldClose)
	{
		(void)handleEvents(&shouldClose, &buttonsHeld);
		if(shouldClose) return STATUS_GAME_EXIT;

		if(buttonsHeld & HOLDING_RETURN) return STATUS_LEVEL_SELECT;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		renderBackground(textureList[TEX_ID_LEVEL_SPRINT_BG]);
		cameraman.render();
		SDL_GL_SwapWindow(w);
		SDL_Delay(1000/FPS);
	}
	return STATUS_GAME_EXIT;
}