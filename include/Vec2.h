#ifndef VEC2_H_
#define VEC2_H_

#define PI 3.14159265

class Vec2 {
public:
	Vec2();
	Vec2(float x, float y);
	virtual ~Vec2();

	Vec2 SomaVec(Vec2 v);
	Vec2 SubVec(Vec2 v);
	Vec2 MultVec(float esc);
	float MagVec();
	Vec2 NormVec();
	float DistVec(Vec2 v);
	float IncVec();
	float IncReta(Vec2 v);
	Vec2 RotateVec(float ang);
	Vec2 RotateVecRad(float ang);
	static Vec2 PolarVec(float mag, float ang);

	void operator=(const Vec2& v);
	void operator+=(const Vec2& v);
	void operator-=(const Vec2& v);
	void operator*=(const float& p);
	void operator/=(const float& p);

	Vec2 operator+(const Vec2& v) const;
	Vec2 operator-(const Vec2& v) const;
	Vec2 operator*(const float& p) const;
	Vec2 operator/(const float& p) const;

	float x, y;
};

#endif /* VEC2_H_ */
