#ifndef PHYSICS_9023584
#define PHYSICS_9023584

#include <vector>
#include "Body.h"
#include "Rect.h"
#include "Vector2.h"

class Physics {
private:
	std::vector<Rect*> bodies {};

	void updateVelocities(float delta); // delta is the amount of time passed since last frame in seconds
	void solveCollision(Rect& bodyA, Rect& bodyB);
public:
	Vector2<float> gravity { 0.0, 0.0 };
	std::vector<std::pair<Rect*, Rect*>> getPairs();
	void update(float delta);
	void addBody(Rect* body);
	void deleteBody(Rect* body);
	void render();
	Vector2<float> camera { 0.0, 0.0 };

	Vector2<float>& getCamera() {
		return this->camera;
	}
};

#endif