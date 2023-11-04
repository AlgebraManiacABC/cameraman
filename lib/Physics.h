#ifndef PHYSICS_9023584
#define PHYSICS_9023584

#include <vector>
#include "Body.h"
#include "Rect.h"

class Physics {
private:
	std::vector<Rect*> bodies {};
	Vector2<float> gravity { 0.0, 0.05 };

	void updateVelocities(float delta); // delta is the amount of time passed since last frame in seconds
	void solveCollision(Rect& bodyA, Rect& bodyB);
public:
	std::vector<std::pair<Rect*, Rect*>> getPairs();
	void update(float delta);
};

#endif