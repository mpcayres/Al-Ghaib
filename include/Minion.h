#ifndef SRC_MINION_H_
#define SRC_MINION_H_

#include "GameObject.h"
#include "Sprite.h"
#include "Vec2.h"

class Minion : public GameObject {
public:
	Minion(GameObject* minionCenter, float arcOffset = 0, float scale = 1);

	void Update(float dt);
	void Render();
	bool IsDead();
	void Shoot(Vec2 pos);
	void NotifyCollision(GameObject& other);
	bool Is(std::string type);

private:
	GameObject* center;
	Sprite sp;
	float arc;
};

#endif /* SRC_MINION_H_ */
