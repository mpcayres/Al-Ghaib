#ifndef INCLUDE_ALINE_HPP_
#define INCLUDE_ALINE_HPP_

#include <queue>
#include <vector>
#include <string>

#include "GameObject.hpp"
#include "Minion.hpp"
#include "Sprite.hpp"
#include "Timer.hpp"
#include "Geometry.hpp"

class Alien : public GameObject{
public:
	Alien(float x, float y, int nMinions);
	~Alien();
	void Update(float dt);
	void Render();
	bool IsDead();
	void NotifyCollision(GameObject& other);
	bool Is(std::string type);

	static int alienCount;

private:
	enum AlienState{ MOVING, RESTING };

	AlienState state;
	Timer restTimer;
	Vec2 destination;
	Sprite sp;
	Vec2 speed;
	int hp;
	int actionDelay;

	std::vector<Minion> minionArray;
};


#endif /* INCLUDE_ALINE_HPP_ */
