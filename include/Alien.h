#ifndef SRC_ALIEN_H_
#define SRC_ALIEN_H_

#include "Sprite.h"
#include "Vec2.h"
#include "InputManager.h"
#include "Minion.h"
#include "Timer.h"
#include <queue>
#include <vector>

class Alien : public GameObject {
public:
	Alien(float x, float y, int nMinions);
	virtual ~Alien();

	void Update(float dt);
	void Render();
	bool IsDead();
	void NotifyCollision(GameObject& other);
	bool Is(std::string type);

	static int alienCount;

private:
	Sprite sp;
	Vec2 speed;
	int hp;
	std::vector<Minion> minionArray;

	enum AlienState { MOVING, RESTING };
	AlienState state;
	Timer restTimer;
	Vec2 destination;
};

#endif /* SRC_ALIEN_H_ */
