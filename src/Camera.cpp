/*
 * Camera.cpp
 *
 *  Created on: 31 de mar de 2017
 *      Author: renne
 *
 *
 * Aluno: Renne Ruan Alves Oliveira
 * Matricula: 14/0030930
 * Introducao ao Desenvolvimento de Jogos 1/2017
 */

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
	InputManager InputInstance = InputManager::GetInstace();
	if(focus != nullptr){
		pos.x = focus->box.x +focus->box.w/2 - Game::GetInstance().GetWidth()/2;
		pos.y = focus->box.y +focus->box.h/2 - Game::GetInstance().GetHeight()/2;

		pos.x *= -1;
		pos.y *= -1;
	}else{
		if(InputInstance.IsKeyDown(LEFT_ARROW_KEY)) pos.x += speed.x;
		if(InputInstance.IsKeyDown(RIGHT_ARROW_KEY)) pos.x -= speed.x;
		if(InputInstance.IsKeyDown(UP_ARROW_KEY)) pos.y += speed.y;
		if(InputInstance.IsKeyDown(DOWN_ARROW_KEY)) pos.y -= speed.y;
	}
}




