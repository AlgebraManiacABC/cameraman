#include "events.h"
#include "game.h"

int handleEvents(bool *shouldClose, Uint32 * buttonsHeld)
{
	SDL_Event event;
	Uint32 eventCount = 0;
	while(SDL_PollEvent(&event))
	{
		eventCount++;
		switch(event.type)
		{
			case SDL_QUIT:
				(*shouldClose) = true;
				return eventCount;
			case SDL_KEYDOWN:
				switch(event.key.keysym.scancode)
				{
					case SDL_SCANCODE_ESCAPE:
						(*shouldClose) = true;
						return eventCount;
					case SDL_SCANCODE_W:
						(*buttonsHeld) |= HOLDING_W;
						break;
					case SDL_SCANCODE_A:
						(*buttonsHeld) |= HOLDING_A;
						break;
					case SDL_SCANCODE_S:
						(*buttonsHeld) |= HOLDING_S;
						break;
					case SDL_SCANCODE_D:
						(*buttonsHeld) |= HOLDING_D;
						break;
					case SDL_SCANCODE_LSHIFT:
						(*buttonsHeld) |= HOLDING_LSHIFT;
						break;
					case SDL_SCANCODE_SPACE:
						(*buttonsHeld) |= HOLDING_SPACE;
						break;
					case SDL_SCANCODE_LEFT:
						break;
					case SDL_SCANCODE_RIGHT:
						break;
					case SDL_SCANCODE_UP:
						break;
					case SDL_SCANCODE_DOWN:
						break;
					case SDL_SCANCODE_PAGEDOWN:
						break;
					case SDL_SCANCODE_PAGEUP:
						break;
					case SDL_SCANCODE_RETURN:
						(*buttonsHeld) |= HOLDING_RETURN;
						break;
					default:
						break;
				}
				break;
			case SDL_KEYUP:
				switch(event.key.keysym.scancode)
				{
					case SDL_SCANCODE_W:
						(*buttonsHeld) &= ~HOLDING_W;
						break;
					case SDL_SCANCODE_A:
						(*buttonsHeld) &= ~HOLDING_A;
						break;
					case SDL_SCANCODE_S:
						(*buttonsHeld) &= ~HOLDING_S;
						break;
					case SDL_SCANCODE_D:
						(*buttonsHeld) &= ~HOLDING_D;
						break;
					case SDL_SCANCODE_LSHIFT:
						(*buttonsHeld) &= ~HOLDING_LSHIFT;
						break;
					case SDL_SCANCODE_SPACE:
						(*buttonsHeld) &= ~HOLDING_SPACE;
						break;
					case SDL_SCANCODE_LEFT:
						break;
					case SDL_SCANCODE_RIGHT:
						break;
					case SDL_SCANCODE_UP:
						break;
					case SDL_SCANCODE_DOWN:
						break;
					case SDL_SCANCODE_PAGEDOWN:
						break;
					case SDL_SCANCODE_PAGEUP:
						break;
					case SDL_SCANCODE_RETURN:
						(*buttonsHeld) &= ~HOLDING_RETURN;
						break;
					default:
						break;
				}
				break;
			default:
				break;
		}
	}
	return eventCount;
}