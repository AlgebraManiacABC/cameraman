#include <vector>
#include <math.h>
#include <utility>
#include "Vector2.h"
#include "Physics.h"

std::vector<std::pair<Rect*, Rect*>> Physics::getPairs() {
	int length = bodies.size();
	int numPairs = length * (length - 1) / 2;// n(n - 1) / 2
	std::vector<std::pair<Rect*, Rect*>> pairs = {};
	pairs.reserve(numPairs);

	for (int i = 0; i < length - 1; ++i) {
		for (int j = i + 1; j < length; ++j) {
			if (!(bodies.at(i)->getStatic() && bodies.at(j)->getStatic())) {
				pairs.push_back({ bodies.at(i), bodies.at(j) });
			}
		}
	}

	return pairs;
}

void Physics::update(float delta) {
	std::vector<std::pair<Rect*, Rect*>> pairs = this->getPairs();

	for (std::pair<Rect*, Rect*>& pair : pairs) {
		Rect& bodyA = *pair.first;
		Rect& bodyB = *pair.second;
		if (bodyA.isColliding(bodyB)) {
			this->solveCollision(bodyA, bodyB);
		}
	}

	this->updateVelocities(delta);
};

void Physics::updateVelocities(float delta) {
	Vector2<float> gravity = this->gravity * delta;
	for (Rect* rect : this->bodies) {
		if (rect->getStatic()) {
			return;
		}
		float frictionAir = std::pow((1 - rect->getFrictionAir()), delta);
		Vector2<float>& velocity = rect->getVelocity();
		Vector2<float>& lastVelocity = rect->getLastVelocity();
		
		velocity += gravity;
		velocity *= frictionAir;
		
		Vector2<float> positionChange = (velocity + lastVelocity) * (delta / 2); // approximates trapezoid area under velocity to get total position change (trapezoidal approximation)
		rect->translate(positionChange);

		rect->updateMatrix();
	}
}
void Physics::solveCollision(Rect& bodyA, Rect& bodyB) {
	bool staticA = bodyA.getStatic();
	bool staticB = bodyB.getStatic();

	if (staticA && staticB) { // 2 static bodies shouldn't move each other
		return;
	}
	
	Vector2<float>& positionA = bodyA.getPosition();
	Vector2<float>& positionB = bodyB.getPosition();
	Vector2<float>& velocityA = bodyA.getVelocity();
	Vector2<float>& velocityB = bodyB.getVelocity();
	Vector2<float> relativePosition = positionB - positionA;
	Vector2<float> relativeVelocity = velocityB - velocityA;

	Vector2<float> intersection = bodyA.getIntersection(bodyB);
	Vector2<float> normal {};
	if (std::abs(intersection.x) < std::abs(intersection.y)) { // shift in x
		normal.x = copysign(1.0, relativePosition.x);
	}
	else { // shift in y
		normal.y = copysign(1.0, relativePosition.y);
	}

	if (Vector2<float>::dot(normal, relativeVelocity) > 0) { // Relative velocity and collision normal should be opposite directions
		// we don't suck!
		return;
	}

	float shareA = (staticA || staticB) ? (staticB ? 1.0 : 0.0) : 0.5;
	float shareB = 1.0 - shareA;

	positionA -= shareA * Vector2<float>::dot(normal, intersection);
	positionB += shareB * Vector2<float>::dot(normal, intersection);

	Vector2<float> forceA = normal * Vector2<float>::dot(normal, velocityA);
	Vector2<float> forceB = normal * Vector2<float>::dot(normal, velocityB);
	if (forceA.x > 0 || forceA.y > 0) {
		velocityA += forceA;
	}
	if (forceB.x > 0 || forceB.y > 0) {
		velocityB += forceB;
	}
}

void Physics::addBody(Rect* body) {
	this->bodies.push_back(body);
}
void Physics::deleteBody(Rect* body) {
	// swap and pop
	// Rect** bodyPtr;
	// for (Rect*& b : this->bodies) {
	// 	if (b == body) {
	// 		bodyPtr = &b;
	// 		break;
	// 	}
	// }
	// Rect** tmp = bodyPtr;
	// *bodyPtr = this->bodies.back();
	// this->bodies.back() = *tmp;

	// this->bodies.pop_back();
}

Rect::~Rect() { // body destructor here bc I hate circular dependencies
	this->physics->deleteBody(this);
}