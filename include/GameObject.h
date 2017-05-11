#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include "Rect.h"
#include <string>

class GameObject {
public:
	GameObject();
	virtual ~GameObject();

	virtual void Update(float dt) = 0;
	virtual void Render() = 0;
	virtual bool IsDead() = 0;
	virtual void NotifyCollision(GameObject& other) = 0;
	virtual bool Is(std::string type) = 0;

	Rect box;
	float rotation;
};

#endif /* GAMEOBJECT_H_ */
