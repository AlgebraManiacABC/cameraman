#include "Rect.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

struct Controls {
	bool up    { false };
	bool down  { false };
	bool left  { false };
	bool right { false };
};

class Player {
private:
	void updateControls(Uint32 buttonsHeld);
	
public:
	Player(vec2 position);
	Rect body;
	Controls controls;
	float moveSpeed;

	void update(Uint32 buttonsHeld);
};