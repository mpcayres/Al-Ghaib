#ifndef INCLUDE_Player_HPP_
#define INCLUDE_Player_HPP_

#include "GameObject.hpp"
#include "Sprite.hpp"
#include "Timer.hpp"
#include "Geometry.hpp"

class Player : public GameObject{
public:
	Player(float x, float y);
	~Player();

	void Update(float dt);
	void Render();
	bool IsDead();
	void NotifyCollision(GameObject& other);
	void Shoot();
	bool Is(std::string type);

	static Player * player;

private:
	Timer time;
	Sprite bodySp;
	Vec2 speed;
	int hp;
};

#endif /* INCLUDE_Player_HPP_ */
