#include "Camera.h"
#include "InputManager.h"

#define SPEEDX 200
#define SPEEDY 200

GameObject* Camera::focus = nullptr;
Vec2 Camera::pos;
Vec2 Camera::speed;

void Camera::Follow(GameObject* newFocus){
	focus = newFocus;
}

void Camera::Unfollow(){
	focus = nullptr;
}

void Camera::Update(float dt){
	InputManager &inputManager = InputManager::GetInstance();
	if(focus != nullptr)
		pos = focus->box.CoordCentro() - Vec2(WINDOW_W/2, WINDOW_H/2);
	else {
		speed.x = SPEEDX * dt;
		speed.y = SPEEDY * dt;
		if(inputManager.IsKeyDown(RIGHT_ARROW_KEY)){
			pos.x += speed.x;
		}
		if(inputManager.IsKeyDown(LEFT_ARROW_KEY)){
			pos.x -= speed.x;
		}
		if(inputManager.IsKeyDown(DOWN_ARROW_KEY)){
			pos.y += speed.y;
		}
		if(inputManager.IsKeyDown(UP_ARROW_KEY)){
			pos.y -= speed.y;
		}
	}
}

