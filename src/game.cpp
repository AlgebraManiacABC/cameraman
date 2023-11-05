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
#include "Player.h"
#include <cmath>
#include <random>

bool paused = false;
Uint8 levelsCompleted = 0b0;

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
		if(shouldClose || buttonsHeld & HOLDING_ESCAPE) return STATUS_GAME_EXIT;

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
		if(shouldClose || buttonsHeld & HOLDING_ESCAPE) return STATUS_GAME_EXIT;

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

void loopBG(Rect& backgroundA, Rect& backgroundB, Rect& backgroundC, float playerX) {
	float width = backgroundA.getWidth();
	float relativePosition = static_cast<int>(playerX / width + 0.5);

	Vector2<float> bgAPos { static_cast<float>(relativePosition) * width, 0.0 };
	backgroundA.setPosition(bgAPos);
	Vector2<float> bgBPos { bgAPos.x + width, bgAPos.y };
	backgroundB.setPosition(bgBPos);
	Vector2<float> bgCPos { bgAPos.x - width, bgAPos.y };
	backgroundC.setPosition(bgCPos);
}


GLuint levelSprint()
{
	float score = 1.0;

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> getRandom(0.0, 1.0);

	Physics physics {};
	physics.gravity.y = -10.0;
	
	vec3 startingPosition { 0.0, 0.0, 0.4 };
	Player player { startingPosition };
	physics.addBody(&player.body);
	
	vec3 floorAPosition = { 2.5, -0.6, 0.4 };
	Rect floorA {floorAPosition, 100.0, 0.25, true, true, textureList[TEX_ID_FLOOR]};
	physics.addBody(&floorA);

	
	vec3 targetPosition = { 0.5, -0.05f, 0.4 };
	Rect target {targetPosition, 460.0f / 662.0f * 0.4f, 0.4, true, false, textureList[TEX_ID_SPRINTER1]};
	physics.addBody(&target);
	player.target = &target;

	vec3 backgroundAPosition = { 0.0, 0.0, 0.5 };
	Rect backgroundA {backgroundAPosition, 240.0f / 90.0f * 2.0f, 2.0, true, false, textureList[TEX_ID_LEVEL_SPRINT_BG]};
	physics.addBody(&backgroundA);
	Rect backgroundB {backgroundAPosition, 240.0f / 90.0f * 2.0f, 2.0, true, false, textureList[TEX_ID_LEVEL_SPRINT_BG]};
	physics.addBody(&backgroundB);
	Rect backgroundC {backgroundAPosition, 240.0f / 90.0f * 2.0f, 2.0, true, false, textureList[TEX_ID_LEVEL_SPRINT_BG]};
	physics.addBody(&backgroundC);

	std::vector<Rect*> obstacles {};
	auto createVault = [&](float x) {
		vec3 vaultPos = { x, -0.4, 0.4 };
		Rect* vault = new Rect(vaultPos, 3 * 0.02f, 14 * 0.02f, true, true, textureList[TEX_ID_VAULT]);
		physics.addBody(vault);
		obstacles.push_back(vault);
	};

	float maxDistance = 16.0;
	float totalVaultX = 0.5;
	for (int i = 0; i < 20; ++i) {
		totalVaultX += getRandom(mt) * 0.8 + 0.8;
		if (totalVaultX >= maxDistance) {
			break;
		}
		createVault(totalVaultX);
	}

	
	button *resumeButton = createButton(ww/2.0,wh/2.0,ww/4,ww/20,textureList[TEX_ID_BUTTON_RESUME]);
	button *levelsButton = createButton(ww/2.0,wh/1.7,ww/5,ww/25,textureList[TEX_ID_BUTTON_LEVELS]);
	button *quitButton = createButton(ww/2.0,wh/1.5,ww/5,ww/25,textureList[TEX_ID_BUTTON_QUIT_MAIN]);
	vec3 pauseLayer = {0.0, 0.0, 0.22};
	Rect pauseMenu { pauseLayer, 3, (float)((3.0*wh)/ww), true, false, textureList[TEX_ID_PAUSE_MENU_BG] };
	Uint32 buttonsHeld = (0b0);
	bool shouldClose = false;
	float time = 0;
	


	while(!shouldClose)
	{
		const float deltaTime = 1000 / FPS;
		time += deltaTime;
		(void)handleEvents(&shouldClose, &buttonsHeld);
		if(shouldClose) return STATUS_GAME_EXIT;
		if(windowResizedThisFrame)
		{
			recreateButton(resumeButton,ww/2.0,wh/2.0,ww/4,ww/20);
			recreateButton(resumeButton,ww/2.0,wh/1.7,ww/5,ww/25);
			recreateButton(quitButton,ww/2.0,wh/1.5,ww/5,ww/25);
		}
		if(buttonsHeld & HOLDING_RIGHT) return STATUS_LEVEL_SKIING;

		if(buttonsHeld & HOLDING_ESCAPE && firstFramePressedEscape)
		{
			if(paused)
			{
				paused = false;
			}
			else
			{
				paused = true;
			}
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		if(!paused)
		{
			// move target
			if (time > 600) {
				Vector2<float> lastPosition { target.getPosition() };
				Vector2<float> newPosition { lastPosition.x + 0.9f * deltaTime / 1000, lastPosition.y };
				target.setPosition(newPosition);
			}
			
			// move camera
			physics.camera.x = player.body.getPosition().x;
			if (std::abs(target.getPosition().x - player.body.getPosition().x) < 0.9) {
				physics.camera.x = (target.getPosition().x + player.body.getPosition().x) / 2;
			}


			loopBG(backgroundA, backgroundB, backgroundC, player.body.getPosition().x);
			player.update(buttonsHeld, score);
			if (score <= 0 || player.body.getPosition().x >= maxDistance) {
				return STATUS_LEVEL_SELECT;
			}

			physics.update(deltaTime / 1000);
		}
		else
		{
			physics.render();
			pauseMenu.render();
			renderButton(resumeButton);
			renderButton(levelsButton);
			renderButton(quitButton);

			if(updateButton(resumeButton) == BUTTON_ACTIVATED)
			{
				paused = false;
				deactivateButton(resumeButton);
			}
			else if(updateButton(levelsButton) == BUTTON_ACTIVATED)
			{
				paused = false;
				deactivateButton(levelsButton);
				deleteButton(resumeButton);
				deleteButton(levelsButton);
				deleteButton(quitButton);
				return STATUS_LEVEL_SELECT;
			}
			else if(updateButton(quitButton) == BUTTON_ACTIVATED)
			{
				deleteButton(resumeButton);
				deleteButton(levelsButton);
				deleteButton(quitButton);
				return STATUS_GAME_EXIT;
			}
		}

		SDL_GL_SwapWindow(w);
		SDL_Delay(deltaTime);
	}

	for (Rect* obstacle : obstacles) {
		delete obstacle;
	}

	return STATUS_GAME_EXIT;
}