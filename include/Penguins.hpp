#ifndef INCLUDE_PENGUINS_HPP_
#define INCLUDE_PENGUINS_HPP_

#include "GameObject.hpp"
#include "Sprite.hpp"
#include "Timer.hpp"
#include "Geometry.hpp"

class Penguins : public GameObject {
public:
	Penguins(float x, float y);
	~Penguins();

	void Update(float dt);
	void Render();
	bool IsDead();
	void NotifyCollision(GameObject& other);
	void Shoot();
	bool Is(std::string type);

	static Penguins * player;

private:
	Timer time;
	Sprite bodySp;
	Sprite cannonSp;
	Vec2 speed;
	float linearSpeed;
	float cannonAngle;
	int hp;
	int deltaX, deltaY;
	Rect AuxCannon;

};

#endif /* INCLUDE_PENGUINS_HPP_ */
