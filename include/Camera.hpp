#ifndef INCLUDE_CAMERA_HPP_
#define INCLUDE_CAMERA_HPP_

#include "GameObject.hpp"
#include "Geometry.hpp"

class Camera {
public:
	static void Follow(GameObject* newFocus);
	static void Unfollow();
	static void Update(float dt);

	static Vec2 pos;
	static Vec2 speed;

private:
	static GameObject* focus;
};

#endif
