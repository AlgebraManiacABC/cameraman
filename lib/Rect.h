#ifndef RECT_485939
#define RECT_485939

#include "./Body.h"

class Rect : public Body {
private:
	int width;
	int height;

public:
	Rect(Vector2<float> pos, float width, float height, GLuint texture, GLuint buffer);

	int getWidth();
	int getHeight();
};

#endif