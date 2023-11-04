#ifndef RECT_485939
#define RECT_485939

#include "Body.h"
#include "Vector2.h"
#include "cglm/cglm.h"

//	`vec2` pos, `vec2` width-height, `bool` isStatic, `GLuint` tex, `GLuint` buffer
class Rect : public Body {
private:
	int width;
	int height;

public:
	Rect(vec2 pos, float width, float height, bool isStatic, GLuint texture, GLuint buffer);
	~Rect();

	int getWidth();
	int getHeight();
	Vector2<float> getIntersection(Rect& bodyB); // returns the amount of intersection, negative if intersecting / positive if not
	bool isColliding(Rect& bodyB);
};

#endif