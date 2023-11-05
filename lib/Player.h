#include "Rect.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include "Collision.h"
#include <vector>
#include "Event.h"

struct Controls {
	bool up    { false };
	bool down  { false };
	bool left  { false };
	bool right { false };
};

class Player {
private:
	void updateControls(Uint32 buttonsHeld);
	bool canJump { true };
	
public:
	Event onCollision;
	Player(vec2 position);
	Rect body;
	Controls controls;
	float moveSpeed;
	float jumpHeight;

	void update(Uint32 buttonsHeld);
};