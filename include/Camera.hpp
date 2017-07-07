#ifndef INCLUDE_CAMERA_HPP_
#define INCLUDE_CAMERA_HPP_

#include "GameObject.hpp"
#include "Geometry.hpp"
#include "Timer.hpp"

#define CAMERA_TYPE0	0
#define CAMERA_TYPE1 	1
#define CAMERA_TYPE2	2
#define CAMERA_TYPE3	3
#define CAMERA_TYPE4	4
#define OFFSET_TYPE2	400
#define MAX_ZOOM		0.2

class Camera {
public:
	static void SetType(int Ntype);
	static void Follow(GameObject* newFocus, int type);
	static void Unfollow();
	static void Update(float dt);
	static void Move(int xDest, int yDest, float tempo);
	static void DontMove();
	static void Zoom(float tempoN, bool in);
	static void ZoomCreepy(float tempoN, bool in);
	static void ZoomCut(bool in);
	static void UpdateZoom();
	static bool GetMoving();

	static Vec2 pos;
	static Vec2 speed;
	static bool zoomCreepy;

private:
	static Timer time;
	static GameObject* focus;
	static int type;
	static float origDist, tempo;
	static bool isMoving, inWay, inWayBack, isZoomIn, isZoomOut;
	static Vec2 dest,previousPos;
};

#endif
