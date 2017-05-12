#ifndef INCLUDE_BULLET_HPP_
#define INCLUDE_BULLET_HPP_

#include <string>

#include "GameObject.hpp"
#include "Sprite.hpp"
#include "Geometry.hpp"

class Bullet : public GameObject{
public:
	Bullet(float x, float y, float angle, float speed, float maxDistance,
			std::string sprite, int frame, float frameTime, bool isPlayer);
	void Update(float dt);
	void Render();
	bool IsDead();
	void NotifyCollision(GameObject& other);
	bool Is(std::string type);

	bool targetsPlayer;

private:
	Sprite sp;
	Vec2 speed;
	float distanceLeft;
};

#endif /* INCLUDE_BULLET_HPP_ */
