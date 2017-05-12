#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

#include "GameObject.hpp"
#include "Sprite.hpp"
#include "Geometry.hpp"

#ifndef INCLUDE_MINION_HPP_
#define INCLUDE_MINION_HPP_

class Minion : public GameObject{
public:
	Minion(GameObject* minionCenter, float arcOffset = 0);
	void Update(float dt);
	void Render();
	bool IsDead();
	void Shoot(Vec2 pos);
	void NotifyCollision(GameObject& other);
	bool Is(std::string type);

private:
	GameObject* center;
	bool dead;
	Sprite sp;
	float arc;
};

#endif /* INCLUDE_MINION_HPP_ */
