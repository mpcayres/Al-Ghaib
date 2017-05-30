#ifndef INCLUDE_GEOMETRY_HPP_
#define INCLUDE_GEOMETRY_HPP_

#define PI 3.14159265

class Vec2 {
public:
	float x, y;

	Vec2();
	Vec2(float x, float y);
	Vec2 Soma(Vec2 vector);
	Vec2 Sub(Vec2 vector);
	Vec2 Mult(int escalar);
	Vec2 Rotate(float angle);
	Vec2 Normalize();

	float Abs();
	float Distance(Vec2 vector);
	float Angle();
	float Inclination(Vec2 vector);

	void operator=(const Vec2& v);
	void operator+=(const Vec2& v);
	void operator-=(const Vec2& v);
	void operator*=(const float& p);
	void operator/=(const float& p);

	Vec2 operator+(const Vec2& rhs) const;
	Vec2 operator-(const Vec2& rhs) const;
	Vec2 operator*(const float rhs) const;
	Vec2 operator/(const float rhs) const;

};

class Rect {
public:
	float x, y, w, h;

	Rect();
	Rect(float x1, float y1, float w1, float h1);
	void SomaVec2(Vec2 vector);
	Vec2 Center();
	float CenterX();
	float CenterY();
	float DistanceRect(Rect rectangle2);
	bool Inside(float x, float y);
	bool Inside(Rect v2);
	bool InsideX(Rect v2);
	bool InsideY(Rect v2);
	bool Intersect(Rect v2);

	void operator=(const Rect& r);
};

#endif /* INCLUDE_GEOMETRY_HPP_ */
