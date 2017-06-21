#include "Camera.hpp"
#include "InputManager.hpp"
#include "Game.hpp"

#define MULTIPLY 10

GameObject* Camera::focus;
Vec2 Camera::pos;
Vec2 Camera::speed;
int Camera::type, Camera::tempo;
Vec2 Camera::previousPos, Camera::dest;
bool Camera::isMoving, Camera::inWay, Camera::inWayBack;
Timer Camera::time;

void Camera::Follow(GameObject* newFocus, int Ntype){
	Camera::focus = newFocus;
	Camera::type = Ntype;
	isMoving = false;
}

void Camera::Unfollow(){
	focus = nullptr;
}

void Camera::Move(int xd, int yd, int tempoN){
	isMoving = true;
	inWay = true;
	inWayBack = false;
	tempo = tempoN;

	dest.x = xd - Game::GetInstance().GetWidth()/2;
	dest.y = yd - Game::GetInstance().GetHeight()/2;

	time.Restart();
	previousPos = pos;

	//Sprite::scaleZoom = zoom;

	speed = (pos - dest).Normalize() * 10;

	printf("P %f D %f S %f\n", pos.x, dest.x, speed.x);
}

void Camera::Update(float dt){
	InputManager InputInstance = InputManager::GetInstance();
	if(focus != nullptr && !isMoving){
		if(type == 1){
			pos.x = focus->box.CenterX() - Game::GetInstance().GetWidth()/2;
			pos.y = focus->box.CenterY() - Game::GetInstance().GetHeight()/2;
		} else if(type == 2){
			pos.x = focus->box.CenterX() - Game::GetInstance().GetWidth()/2;
			pos.y = 0;
		}
	} else if(isMoving){
		if(!inWayBack && abs(dest.x - pos.x) < 2 && abs(dest.y - pos.y) < 2){
			pos = dest;
			inWay = false;
		}else if(inWay){
			pos.x -= speed.x;
			pos.y -= speed.y;
		}

		if(!inWay && !inWayBack){
			time.Update(dt);

			if(time.Get() >= tempo){
				inWayBack = true;
			}
		}
		if(inWayBack && abs(previousPos.x - pos.x) < 2 && abs(previousPos.y - pos.y) < 2){
			pos = previousPos;
			inWayBack = false;
			isMoving = false;
		} else if(inWayBack){
			pos.x += speed.x;
			pos.y += speed.y;
		}

	} else{
		pos.x = 80;
		pos.y = 80;
	}
}

bool Camera::GetMoving(){
	return isMoving;
}
