#ifndef BODY_3489520
#define BODY_3489520

class Physics;

#include "cglm/cglm.h"
#include "GL/glew.h"
#include <vector>
#include "Vector2.h"

class Body {
protected:
	Vector2<float> position; // position is in percent of height, 1 being the distance to the top of the screen from the bottom
	Vector2<float> velocity {}; // in screen height / second
	Vector2<float> lastVelocity {};

	float frictionAir { 0.05 };
	bool isStatic { true };
	Physics* physics;
	
	GLuint texture {};
	GLuint indexBuffer {};
	mat4 modelMatrix {};

public:
	Body(GLuint texture, GLuint buffer);
	void setPhysics(Physics* physics); // needs to be called when created

	Vector2<float>& getPosition();
	Vector2<float>& getVelocity();
	Vector2<float>& getLastVelocity();
	float& getFrictionAir();
	bool getStatic();

	void translate(Vector2<float>& translation);
	void setPosition(Vector2<float>& newPosition);
	void setVelocity(Vector2<float>& newVelocity);
	void updateMatrix();

	void render();
};


#endif