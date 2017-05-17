#ifndef ENEMY_Player_HPP_
#define ENEMY_Player_HPP_

#include "GameObject.hpp"
#include "Sprite.hpp"
#include "Timer.hpp"
#include "Geometry.hpp"
#include "Player.hpp"

class Enemy : public GameObject{
public:
	Enemy(float x, float y);
	~Enemy();

	void Update(float dt);
	void Render();
	bool IsDead();
	void NotifyCollision(GameObject& other);
	void Shoot();
	bool Is(std::string type);

	static Enemy * enemy;

private:
	Timer time;
	Sprite bodySp;
	Vec2 speed;
	int hp;
	bool running = true;
};

#endif /* INCLUDE_Enemy_HPP_ */
