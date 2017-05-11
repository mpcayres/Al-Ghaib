#ifndef RECT_H_
#define RECT_H_

#include "Vec2.h"

class Rect {
public:
	Rect();
	Rect(float x, float y, float w, float h);
	virtual ~Rect();

	float x, y, w, h;

	Rect SomaVecRect(Vec2 v);
	Vec2 CoordCentro();
	float DistCentros(Rect r);
	bool IsInside(float x, float y);

	Rect operator=(const Rect& r);
};

#endif /* RECT_H_ */
