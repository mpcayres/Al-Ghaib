#ifndef SRC_MOVINGOBJECT_H_
#define SRC_MOVINGOBJECT_H_

#include <string>

#include "GameObject.hpp"
#include "Sprite.hpp"

class MovingObject : public GameObject {
public:
	MovingObject(float x, float y, std::string img, bool up = false);

	void Update(float dt);
	void Render();
	bool IsDead();
	bool NotifyCollision(GameObject& other);
	bool Is(std::string type);

	Vec2 previousPos;

private:
	Sprite sp;
	float offset;
	bool upObj;
};

#endif /* SRC_MOVINGOBJECT_H_ */
