#include "Rect.h"

Rect::Rect() {
	x = y = w = h = 0;
}

Rect::Rect(float x, float y, float w, float h){
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
}

Rect::~Rect() { }

Rect Rect::SomaVecRect(Vec2 v){
	return Rect(this->x + v.x, this->y + v.y, this->w, this->h);
}

Vec2 Rect::CoordCentro(){
	return Vec2((this->x + this->w/2), (this->y + this->h/2));
}

float Rect::DistCentros(Rect r){
	Vec2 v1 = Vec2((this->x + this->w)/2, (this->y + this->h)/2);
	Vec2 v2 = Vec2((r.x + r.w)/2, (r.y + r.h)/2);

	return v1.DistVec(v2);
}

bool Rect::IsInside(float pointX, float pointY){
	if(x + w < pointX) return false;
	if(x > pointX) return false;
	if(y + h < pointY) return false;
	if(y > pointY) return false;
	return true;
}

Rect Rect::operator=(const Rect& r){
	Rect rect;
	rect.x = r.x;
	rect.y = r.y;
	rect.w = r.w;
	rect.h = r.h;
	return rect;
}
