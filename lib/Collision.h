#ifndef COLLISION
#define COLLISION

#include "Vector2.h"
#include "Rect.h"

struct Collision {
	Vector2<float> normal {};
	Body* bodyA; // cur body
	Body* bodyB; // other body
};

#endif