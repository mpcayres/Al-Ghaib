#ifndef SRC_BULLET_H_
#define SRC_BULLET_H_

#include "GameObject.h"
#include "Sprite.h"
#include "Vec2.h"
#include <string>

class Bullet : public GameObject {
public:
	Bullet(float x, float y, float angle, float speed,
			float maxDistance, std::string sprite,
			int frameCount = 1, float frameTime = 1, bool targetP = false);

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

#endif /* SRC_BULLET_H_ */
