#include "Body.h"
#include "Vector2.h"

/*
todo:
	- change to work correctly with vec class
	- debug so it actually works
*/

Body::Body(Vector2<float> position, GLuint texture, GLuint indexBuffer) {
	this->position = position;
	this->texture = texture;
	this->indexBuffer = indexBuffer;
	this->frictionAir = 0.05;
}

Vector2<float>& Body::getPosition() {
	return this->position;
};
Vector2<float>& Body::getVelocity() {
	return this->velocity;
}
Vector2<float>& Body::getLastVelocity() {
	return this->lastVelocity;
}
float& Body::getFrictionAir() {
	return this->frictionAir;
}
bool Body::getStatic() {
	return this->isStatic;
}

void Body::translate(Vector2<float>& translation) {
	this->position += translation;

	for (Vector2<float>& vertice : this->vertices) {
		vertice += translation;
	}
}
void Body::setPosition(Vector2<float>& newPosition) {
	Vector2<float> translation { newPosition - this->position };
	this->translate(translation);
}
void Body::setVelocity(Vector2<float>& newVelocity) {
	this->velocity = newVelocity;
	this->lastVelocity = newVelocity;
}