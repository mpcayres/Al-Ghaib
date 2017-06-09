#ifndef INCLUDE_CAMERA_HPP_
#define INCLUDE_CAMERA_HPP_

#include "GameObject.hpp"
#include "Geometry.hpp"
#include "Timer.hpp"

#define CAMERA_TYPE1 1
#define CAMERA_TYPE2 2


class Camera {
public:
	static void Follow(GameObject* newFocus, int type);
	static void Unfollow();
	static void Update(float dt);
	static void Move(int xDest, int yDest, int tempo);

	static Vec2 pos;
	static Vec2 speed;

private:
	static Timer time;
	static GameObject* focus;
	static int type, tempo;
	static bool isMoving, inWay, inWayBack;
	static Vec2 dest,previousPos;
};

#endif
