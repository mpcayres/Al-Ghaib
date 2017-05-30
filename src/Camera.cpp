#include "Camera.hpp"
#include "InputManager.hpp"
#include "Game.hpp"

GameObject* Camera::focus;
Vec2 Camera::pos;
Vec2 Camera::speed;

void Camera::Follow(GameObject* newFocus){
	Camera::focus = newFocus;
}

void Camera::Unfollow(){
	focus = nullptr;
}

void Camera::Update(float dt){
	speed.x = speed.y = dt*300;
	InputManager InputInstance = InputManager::GetInstance();
	if(focus != nullptr){
		pos.x = focus->box.CenterX() - Game::GetInstance().GetWidth()/2;
		pos.y = focus->box.CenterY() - Game::GetInstance().GetHeight()/2;
	} else{
		/*if(InputInstance.IsKeyDown(LEFT_ARROW_KEY)) pos.x += speed.x;
		if(InputInstance.IsKeyDown(RIGHT_ARROW_KEY)) pos.x -= speed.x;
		if(InputInstance.IsKeyDown(UP_ARROW_KEY)) pos.y += speed.y;
		if(InputInstance.IsKeyDown(DOWN_ARROW_KEY)) pos.y -= speed.y;*/
	}
}
