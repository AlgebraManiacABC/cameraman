#include "Body.h"
#include "Vector2.h"
#include "cglm/cglm.h"
#include "render.h"
#include "shaders.h"

/*
todo:
	- change to work correctly with vec class
	- debug so it actually works
*/

Body::Body(GLuint texture, GLuint indexBuffer) {
	this->texture = texture;
	this->indexBuffer = indexBuffer;
	this->frictionAir = 0.05;

	// *(this->modelMatrix) = GLM_MAT4_IDENTITY_INIT;
	// this->updateMatrix();
}
void Body::setPhysics(Physics* physics) {
	this->physics = physics;
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
}
void Body::setPosition(Vector2<float>& newPosition) {
	Vector2<float> translation { newPosition - this->position };
	this->translate(translation);
}
void Body::setVelocity(Vector2<float>& newVelocity) {
	this->velocity = newVelocity;
	this->lastVelocity = newVelocity;
}

void Body::updateMatrix() {
	vec3 position = { this->position.x, this->position.y, 0.0 };
	glm_translate(this->modelMatrix, position);
}

void Body::render() {
	glBindVertexArray(actorVAO);
	glBindTexture(GL_TEXTURE_2D, this->texture);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rectElementBuffer);
	
	mat4 modelMatrix = GLM_MAT4_IDENTITY_INIT;
	glUniformMatrix4fv(transformLoc,1,GL_FALSE,(float*)modelMatrix);//this->modelMatrix);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
	
	// unbind
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}