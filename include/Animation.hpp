#ifndef INCLUDE_ANIMATION_HPP_
#define INCLUDE_ANIMATION_HPP_

#include "GameObject.hpp"
#include "Timer.hpp"
#include "Sprite.hpp"

class Animation : public GameObject {
public:
	Animation(float x, float y, float rotation, std::string sprite, int frameCount,
			float frameTime, bool ends);
	void Update(float dt);
	void Render();
	bool IsDead();
	void NotifyCollision(GameObject& other);
	bool Is(std::string type);

private:
	Timer endTimer;
	float timeLimit;
	bool oneTimeOnly;
	Sprite sp;
};

#endif /* INCLUDE_ANIMATION_HPP_ */
