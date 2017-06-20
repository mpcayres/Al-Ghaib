#ifndef INCLUDE_Walls_HPP_
#define INCLUDE_Walls_HPP_

#include "Camera.hpp"
#include "GameObject.hpp"


class Walls: public GameObject{
public:
	Walls(float x, float y, float w, float h);
	~Walls();
	void Render();
	bool NotifyCollision(GameObject& other);
	bool Is(std::string type);
	bool IsDead();
	void Update(float dt);
};

#endif
