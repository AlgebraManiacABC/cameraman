#include "Vector2.h";
#include "Physics.h";

class TestPhysics {
public:
	Physics physics {};
	Rect bodyA {};
	Rect floor {};

	TestPhysics() {
		this->physics = {};
		this->bodyA = {};
		this->physics.addBody(&bodyA);
	}

	update() {
		physics.update();
	}
}