#include "game.h"
#include "shaders.h"
#include "debug.h"
#include "events.h"
#include "assets.h"
#include "render.h"
#include "Physics.h"
#include "Rect.h"
#include "main.h"
#include "button.h"

GLuint STATUS_LEVEL_PICK[LEVEL_COUNT]
{
	STATUS_LEVEL_SPRINT,
	//STATUS_LEVEL_SKIING,
	//STATUS_LEVEL_SHARK,
	//STATUS_LEVEL_VOLCANO,
	//STATUS_LEVEL_NUCLEAR,
	//STATUS_LEVEL_ROCKET,
	//STATUS_LEVEL_BLACK_HOLE
};

GLuint (*fnPointers[])() =
{
	NULL,
	mainMenu,
	levelSelect,
	levelSprint
};

void playGame()
{
	initRenderer();
	if(!loadUniversalShaders()) return;
	if(loadAssets()) return;

	GLuint status = STATUS_MAIN_MENU;
	while(status != STATUS_GAME_EXIT)
	{
		status = fnPointers[status]();
	}
}

GLuint mainMenu()
{
	button *playButton = createButton(ww/2,wh/2,ww/3,ww/15,textureList[TEX_ID_BUTTON_PLAY]);
	button *quitButton = createButton(ww/2,wh/(1.5),ww/4,ww/20,textureList[TEX_ID_BUTTON_QUIT_MAIN]);
	Uint32 buttonsHeld = (0b0);
	bool shouldClose = false;
	while(!shouldClose)
	{
		(void)handleEvents(&shouldClose, &buttonsHeld);
		if(shouldClose) return STATUS_GAME_EXIT;

		if(updateButton(playButton) == BUTTON_ACTIVATED) return STATUS_LEVEL_SELECT;
		if(updateButton(quitButton) == BUTTON_ACTIVATED) return STATUS_GAME_EXIT;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		renderBackground(textureList[TEX_ID_MAIN_MENU_BG]);
		renderButton(playButton);
		renderButton(quitButton);
		SDL_GL_SwapWindow(w);
		SDL_Delay(1000/FPS);
	}
	return STATUS_GAME_EXIT;
}

GLuint levelSelect()
{
	int levelButtonWidth = ww/10;
	button * levelButtons[LEVEL_COUNT] = {0};
	for(int i=0; i<LEVEL_COUNT; i++)
	{
		levelButtons[i] = createButton(i+levelButtonWidth,levelButtonWidth,
				levelButtonWidth,levelButtonWidth,
				textureList[TEX_ID_LEVEL_THUMBS[i]]);
	}
	Uint32 buttonsHeld = (0b0);
	bool shouldClose = false;
	while(!shouldClose)
	{
		(void)handleEvents(&shouldClose, &buttonsHeld);
		if(shouldClose) return STATUS_GAME_EXIT;

		for(int i=0; i<LEVEL_COUNT; i++)
		{
			if(updateButton(levelButtons[i]) == BUTTON_ACTIVATED) return STATUS_LEVEL_PICK[i];
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		renderBackground(textureList[TEX_ID_LEVEL_SELECT_BG]);
		for(int i=0; i<LEVEL_COUNT; i++)
		{
			renderButton(levelButtons[i]);
		}
		SDL_GL_SwapWindow(w);
		SDL_Delay(1000/FPS);
	}
	return STATUS_GAME_EXIT;
}

GLuint levelSprint()
{
	Physics physics {};
	physics.gravity.y = -10.0;
	vec2 cameramanPosition = { 0.0, 0.5 };
	Rect cameraman {cameramanPosition, 0.125, 0.25, false, textureList[TEX_ID_CAMERAMAN_R1]};
	physics.addBody(&cameraman);
	
	vec2 floorPosition = { -0.27, -0.3 };
	Rect floor {floorPosition, 0.5, 0.5, true, textureList[TEX_ID_FLOOR]};
	physics.addBody(&floor);

	
	Uint32 buttonsHeld = (0b0);
	bool shouldClose = false;
	while(!shouldClose)
	{
		const float deltaTime = 1000 / FPS;
		(void)handleEvents(&shouldClose, &buttonsHeld);
		if(shouldClose) return STATUS_GAME_EXIT;

		if(buttonsHeld & HOLDING_RETURN) return STATUS_LEVEL_SELECT;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		renderBackground(textureList[TEX_ID_LEVEL_SPRINT_BG]);


		Vector2<float> intersection = cameraman.getIntersection(floor);
		char buffer[512] = {0};
		sprintf(buffer, "%0.2f, %0.2f", intersection.x, intersection.y);
		SDL_SetWindowTitle(w, buffer);

		physics.update(deltaTime / 1000);
		SDL_GL_SwapWindow(w);
		SDL_Delay(deltaTime);
	}
	return STATUS_GAME_EXIT;
}