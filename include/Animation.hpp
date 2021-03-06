#ifndef INCLUDE_ANIMATION_HPP_
#define INCLUDE_ANIMATION_HPP_

#include "GameObject.hpp"
#include "Timer.hpp"
#include "Sprite.hpp"

class Animation : public GameObject {
public:
	Animation(float x, float y, float rotation, std::string sprite, int frameCount,
			float frameTime, bool ends, float scaleX = 1, float scaleY = 1, bool back = false);
	void Update(float dt);
	void Render();
	bool IsDead();
	bool NotifyCollision(GameObject& other);
	bool Is(std::string type);

private:
	Timer endTimer;
	float timeLimit;
	bool oneTimeOnly;
	Sprite sp;
	Sprite backgroundsquare;
	bool back;
};

#endif /* INCLUDE_ANIMATION_HPP_ */
