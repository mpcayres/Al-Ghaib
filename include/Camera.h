#ifndef SRC_CAMERA_H_
#define SRC_CAMERA_H_

#include "GameObject.h"
#include "Vec2.h"

#define WINDOW_W	1024
#define WINDOW_H	600
#define MAPLIMIT_W	1408
#define MAPLIMIT_H	1280

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

#endif /* SRC_CAMERA_H_ */
