#include "Vec2.h"
#include <math.h>

Vec2::Vec2() {
	x = y = 0;
}

Vec2::Vec2(float x, float y) {
	this->x = x;
	this->y = y;
}

Vec2::~Vec2() { }

Vec2 Vec2::SomaVec(Vec2 v){
	return Vec2(this->x + v.x, this->y + v.y);
}

Vec2 Vec2::SubVec(Vec2 v){
	return Vec2(this->x - v.x, this->y - v.y);
}

Vec2 Vec2::MultVec(float esc){
	return Vec2(this->x * esc, this->y * esc);
}

float Vec2::MagVec(){
	return sqrt(pow(this->x,2) + pow(this->y,2));
}

Vec2 Vec2::NormVec(){
	float mag = Vec2::MagVec();
	return Vec2(this->x / mag, this->y / mag);
}

float Vec2::DistVec(Vec2 v){
	Vec2 aux = SubVec(v);
	return aux.MagVec();
}

float Vec2::IncVec(){
	return atan2(this->y, this->x);
}

float Vec2::IncReta(Vec2 v){
	Vec2 aux = SubVec(v);
	return atan2(aux.y, aux.x);
}

Vec2 Vec2::RotateVec(float ang){
	return Vec2(x*cos(ang*PI/180.0) - y*sin(ang*PI/180.0),
				y*cos((ang-360)*(-1)*PI/180.0) + x*sin((ang-360)*(-1)*PI/180.0));
}

Vec2 Vec2::RotateVecRad(float ang){
	return Vec2((x*cos(ang) - y*sin(ang)), (y*cos(ang) + x*sin(ang)));
}

Vec2 Vec2::PolarVec(float mag, float ang){
	return Vec2(mag, 0).RotateVecRad(ang);
}

void Vec2::operator=(const Vec2& v){
	this->x = v.x;
	this->y = v.y;
}

void Vec2::operator+=(const Vec2& v){
	this->x += v.x;
	this->y += v.y;
}

void Vec2::operator-=(const Vec2& v){
	this->x -= v.x;
	this->y -= v.y;
}

void Vec2::operator*=(const float&  p){
	this->x *= p;
	this->y *= p;
}

void Vec2::operator/=(const float&  p){
	this->x /= p;
	this->y /= p;
}

Vec2 Vec2::operator+(const Vec2& v) const {
	return Vec2(x+v.x, y+v.y);
}

Vec2 Vec2::operator-(const Vec2& v) const {
	return Vec2(x-v.x, y-v.y);
}

Vec2 Vec2::operator*(const float& p) const {
	return Vec2(x*p, y*p);
}

Vec2 Vec2::operator/(const float& p) const {
	return Vec2(x/p, y/p);
}
