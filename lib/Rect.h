#ifndef RECT_485939
#define RECT_485939

#include "Body.h"
#include "Vector2.h"
#include "cglm/cglm.h"
#include "Collision.h"
#include <functional>
#include "Event.h"

//	`vec3` pos, `float` width, `float` height, `bool` isStatic, `GLuint` tex, `GLuint` buffer
class Rect : public Body {
private:
	float width;
	float height;
	float depth;

public:
	Rect(vec3 pos, float width, float height, bool isStatic, bool hasCollisions, GLuint texture);
	~Rect();

	float getWidth();
	float getHeight();
	Vector2<float> getIntersection(Rect& bodyB); // returns the amount of intersection, negative if intersecting / positive if not
	Vector2<float> getSignedIntersection(Rect& bodyB); // returns the amount of intersection, negative if intersecting / positive if not
	bool isColliding(Rect& bodyB);
	void updateMatrix();
	virtual void translate(Vector2<float>& translation);
	bool hasCollisions { true };

	Event* onCollision = nullptr;
	void triggerCollision(Collision collision) {
		if (this->onCollision != nullptr) {
			this->onCollision->callback(collision);
		}
	}

	Vector2<float> distanceToScreen(Vector2<int> screenPoint);
};

#endif