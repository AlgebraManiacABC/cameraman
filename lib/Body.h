#ifndef BODY_3489520
#define BODY_3489520

#include "cglm/cglm.h"
#include "GL/glew.h"
#include <vector>
#include "Vector2.h"

class Body {
protected:
	Vector2<float> position; // position is in percent of height, 1 being the distance to the top of the screen from the bottom
	Vector2<float> velocity; // in screen height / second
	std::vector<Vector2<float>> vertices;
	GLuint texture;
	GLuint indexBuffer;
	mat4 modelMatrix;
	bool isStatic { true };

public:
	Body(Vector2<float> pos, GLuint texture, GLuint buffer);

	Vector2<float>& getPosition();
	Vector2<float>& getVelocity();
	bool getStatic();

	void translate(Vector2<float>& translation);
	void setPosition(Vector2<float>& newPosition);
	void setVelocity(Vector2<float>& newVelocity);
	void updateMatrix(); // ! needs to be implemented
};


#endif