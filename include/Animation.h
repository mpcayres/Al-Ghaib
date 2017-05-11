#ifndef SRC_ANIMATION_H_
#define SRC_ANIMATION_H_

#include "GameObject.h"
#include "Sprite.h"
#include "Timer.h"
#include <string>

class Animation : public GameObject {
public:
	Animation(float x, float y, float rotation, std::string sprite,
			int frameCount, float frameTime, float timeLimit, bool ends);

	void Update(float dt);
	void Render();
	bool IsDead();
	void NotifyCollision(GameObject& other);
	bool Is(std::string type);

private:
	Sprite sp;
	Timer endTimer;
	float timeLimit;
	bool oneTimeOnly;
};

#endif /* SRC_ANIMATION_H_ */
