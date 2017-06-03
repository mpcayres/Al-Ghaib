#include "Camera.hpp"
#include "InputManager.hpp"
#include "Game.hpp"

GameObject* Camera::focus;
Vec2 Camera::pos;
Vec2 Camera::speed;
int Camera::type;

void Camera::Follow(GameObject* newFocus, int Ntype){
	Camera::focus = newFocus;
	Camera::type = Ntype;
}

void Camera::Unfollow(){
	focus = nullptr;
}

void Camera::Update(float dt){
	speed.x = speed.y = dt*300;
	InputManager InputInstance = InputManager::GetInstance();
	if(focus != nullptr){
		if(type == 1){
			pos.x = focus->box.CenterX() - Game::GetInstance().GetWidth()/2;
			pos.y = focus->box.CenterY() - Game::GetInstance().GetHeight()/2;
		} else if(type == 2){
			pos.x = focus->box.CenterX() - Game::GetInstance().GetWidth()/2;
			pos.y = 0;
		}
	}else{
		/*if(InputInstance.IsKeyDown(LEFT_ARROW_KEY)) pos.x += speed.x;
		if(InputInstance.IsKeyDown(RIGHT_ARROW_KEY)) pos.x -= speed.x;
		if(InputInstance.IsKeyDown(UP_ARROW_KEY)) pos.y += speed.y;
		if(InputInstance.IsKeyDown(DOWN_ARROW_KEY)) pos.y -= speed.y;*/
	}
}
