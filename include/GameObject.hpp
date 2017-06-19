#ifndef INCLUDE_GAMEOBJECT_HPP_
#define INCLUDE_GAMEOBJECT_HPP_

#include <string>

#include "Geometry.hpp"

class GameObject{

public:
	virtual ~GameObject(){};

	virtual void Update(float dt) = 0;
	virtual void Render() = 0;
	virtual bool IsDead() = 0;
	virtual void NotifyCollision(GameObject& other) = 0;
	virtual bool Is(std::string type) = 0;

	float rotation;
	Rect box;
	Vec2 previousPos;

};

#endif /* INCLUDE_GAMEOBJECT_HPP_ */
