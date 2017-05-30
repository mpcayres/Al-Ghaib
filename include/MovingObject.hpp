/*
 * MovingObject.h
 *
 *  Created on: 24 de mai de 2017
 *      Author: mp_ca
 */

#ifndef SRC_MOVINGOBJECT_H_
#define SRC_MOVINGOBJECT_H_
#include <string>

#include "GameObject.hpp"
#include "Sprite.hpp"

class MovingObject : public GameObject {
public:
	MovingObject(float x, float y, std::string img);

	void Update(float dt);
	void Render();
	bool IsDead();
	void NotifyCollision(GameObject& other);
	bool Is(std::string type);
	void SetMovementLimits(Rect limits);
	Vec2 previousPos;

private:
	Sprite sp;
	Rect limits;
};

#endif /* SRC_MOVINGOBJECT_H_ */
