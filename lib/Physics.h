#ifndef PHYSICS_9023584
#define PHYSICS_9023584

#include <vector>
#include "Body.h"
#include "Rect.h"

class Physics {
private:
	std::vector<Body&> bodies {};

public:
	void update(); // ! needs to be implemented
	void solveCollision(Rect& bodyA, Rect& bodyB);
};

#endif