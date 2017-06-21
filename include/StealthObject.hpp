#ifndef INCLUDE_STEALTHOBJECT_HPP_
#define INCLUDE_STEALTHOBJECT_HPP_

#include "GameObject.hpp"
#include "Sprite.hpp"

class StealthObject :public GameObject {
public:
	StealthObject(float x, float y, std::string img);

	void Update(float dt);
	void Render();
	bool IsDead();
	bool NotifyCollision(GameObject& other);
	bool Is(std::string type);
	void SetMovementLimits(Rect limits);

private:
	Sprite sp;
	Rect limits;
};

#endif /* INCLUDE_STEALTHOBJECT_HPP_ */
