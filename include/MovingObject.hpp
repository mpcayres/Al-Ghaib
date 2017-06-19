#ifndef SRC_MOVINGOBJECT_H_
#define SRC_MOVINGOBJECT_H_

#include <string>

#include "GameObject.hpp"
#include "Sprite.hpp"

#define OFFSET_MOVI 30

class MovingObject : public GameObject {
public:
	MovingObject(float x, float y, std::string img);

	void Update(float dt);
	void Render();
	bool IsDead();
	void NotifyCollision(GameObject& other);
	bool Is(std::string type);
	Vec2 previousPos;

private:
	Sprite sp;
};

#endif /* SRC_MOVINGOBJECT_H_ */
