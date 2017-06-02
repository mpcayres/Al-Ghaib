#ifndef INCLUDE_CAMERA_HPP_
#define INCLUDE_CAMERA_HPP_

#include "GameObject.hpp"
#include "Geometry.hpp"

#define CAMERA_TYPE1 1
#define CAMERA_TYPE2 2


class Camera {
public:
	static void Follow(GameObject* newFocus, int type);
	static void Unfollow();
	static void Update(float dt);

	static Vec2 pos;
	static Vec2 speed;

private:
	static GameObject* focus;
	static int type;
};

#endif
