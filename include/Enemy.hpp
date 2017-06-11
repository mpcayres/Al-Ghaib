#ifndef ENEMY_Player_HPP_
#define ENEMY_Player_HPP_

#include "GameObject.hpp"
#include "Sprite.hpp"
#include "Timer.hpp"
#include "Geometry.hpp"
#include "Player.hpp"
#define  VALUE 3
#define SPEED_CONTROL 3
#define ENEMY_COOLDOWN 3

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
	void Pursuit();

	static Enemy * enemy;

	Vec2 previousPos;
	static bool show;
private:
	Timer time;
	Sprite sp;
	Vec2 speed;
	int hp;
	bool seen;
	Vec2 destination;
};

#endif /* INCLUDE_Enemy_HPP_ */
