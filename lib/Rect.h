#ifndef RECT_485939
#define RECT_485939

#include "Body.h"
#include "Vector2.h"
#include "cglm/cglm.h"

//	`vec2` pos, `vec2` width-height, `bool` isStatic, `GLuint` tex, `GLuint` buffer
class Rect : public Body {
private:
	float width;
	float height;

public:
	Rect(vec2 pos, float width, float height, bool isStatic, GLuint texture);
	~Rect();

	float getWidth();
	float getHeight();
	Vector2<float> getIntersection(Rect& bodyB); // returns the amount of intersection, negative if intersecting / positive if not
	Vector2<float> getSignedIntersection(Rect& bodyB); // returns the amount of intersection, negative if intersecting / positive if not
	bool isColliding(Rect& bodyB);
	void updateMatrix();
	virtual void translate(Vector2<float>& translation);
};

#endif