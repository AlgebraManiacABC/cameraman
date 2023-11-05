#include <vector>
#include <math.h>
#include <utility>
#include "Vector2.h"
#include "Physics.h"
#include "Rect.h"
#include <algorithm>
#include "main.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

std::vector<std::pair<Rect*, Rect*>> Physics::getPairs() {
	int length = bodies.size();
	int numPairs = length * (length - 1) / 2;// n(n - 1) / 2
	std::vector<std::pair<Rect*, Rect*>> pairs = {};
	pairs.reserve(numPairs);

	for (int i = 0; i < length - 1; ++i) {
		for (int j = i + 1; j < length; ++j) {
			if (!(bodies.at(i)->getStatic() && bodies.at(j)->getStatic())) {
				if (!(bodies.at(i)->hasCollisions && bodies.at(j)->hasCollisions)) continue;
				pairs.push_back({ bodies.at(i), bodies.at(j) });
			}
		}
	}

	return pairs;
}

void Physics::update(float delta) {
	std::vector<std::pair<Rect*, Rect*>> pairs = this->getPairs();

	for (std::pair<Rect*, Rect*>& pair : pairs) {
		if (pair.first == pair.second) {
			continue;
		}
		
		Rect& bodyA = *pair.first;
		Rect& bodyB = *pair.second;
		if (bodyA.isColliding(bodyB)) {
			this->solveCollision(bodyA, bodyB);
		}
	}

	this->updateVelocities(delta);
	this->render();
};
void Physics::render() {
	for (Rect* body : this->bodies) {
		body->updateMatrix(this);
		body->render();
	}
}
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
	}
}
void Physics::solveCollision(Rect& bodyA, Rect& bodyB) {
	bool staticA = bodyA.getStatic();
	bool staticB = bodyB.getStatic();

	if (staticA && staticB) { // 2 static bodies shouldn't move each other
		return;
	}
	if (!bodyA.hasCollisions || !bodyB.hasCollisions) {
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
		return;
	}

	float shareA = (staticA || staticB) ? (staticB ? 1.0 : 0.0) : 0.5;
	float shareB = 1.0 - shareA;

	Vector2<float> signedIntersection = bodyA.getSignedIntersection(bodyB);
	Vector2<float> shiftA = normal * (1 * shareA * Vector2<float>::dot(normal, signedIntersection));
	Vector2<float> shiftB = normal * (1 * shareB * Vector2<float>::dot(normal, signedIntersection));
	bodyA.translate(shiftA);
	bodyB.translate(shiftB);

	float force = Vector2<float>::dot(normal, relativeVelocity);
	if (force != 0) {
		Vector2<float> forceA = normal * ( force * shareA);
		Vector2<float> forceB = normal * (-force * shareB);
		velocityA += forceA;
		velocityB += forceB;
	}

	Collision collisionA { normal, &bodyA, &bodyB };
	bodyA.triggerCollision(collisionA);
	Collision collisionB { normal * -1, &bodyB, &bodyA };
	bodyA.triggerCollision(collisionB);
}

void Physics::addBody(Rect* body) {
	this->bodies.push_back(body);
	body->setPhysics(this);
}
void Physics::deleteBody(Rect* body) {
	std::remove_if(this->bodies.begin(), this->bodies.end(), [body](Rect* bodyB) {
		return bodyB == body;
	});
}

Rect::~Rect() { // body destructor here bc circular dependencies
	if (this->physics) {
		this->physics->deleteBody(this);
	}
}

void Rect::updateMatrix(Physics* physics) {
	float aspectRatio = static_cast<float>(wh) / ww;
	mat4 transformation = GLM_MAT4_IDENTITY_INIT;
	if (!physics) return;
	Vector2<float> camera = physics->getCamera();

	vec3 position = { (this->position.x - camera.x) * aspectRatio, this->position.y - camera.y, this->depth };
	glm_translate(transformation, position);

	Vector2<float> scale = { aspectRatio * static_cast<float>(this->width), static_cast<float>(this->height) };
	vec3 transformScale = { scale.x, scale.y, 1.0 };
	glm_scale(transformation, transformScale);

	glm_mat4_copy(transformation, this->modelMatrix);
}
Vector2<float> Rect::distanceToScreen(Vector2<int> screenPoint) {
	Vector2<float>& camera = this->physics->camera;
	float aspectRatio = static_cast<float>(wh) / ww;
	Vector2<float> dist { screenPoint.x / static_cast<float>(ww) - 0.95f - (this->position.x - camera.x) * aspectRatio * 0.5f, screenPoint.y / static_cast<float>(wh) * -1.0f + 0.75f - (this->position.y - camera.y) * 0.5f };
	return dist;
}