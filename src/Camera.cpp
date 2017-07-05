#include "Camera.hpp"
#include "InputManager.hpp"
#include "Game.hpp"

#include <iostream>

GameObject* Camera::focus;
Vec2 Camera::pos, Camera::speed;
int Camera::type;
float Camera::origDist, Camera::tempo;
Vec2 Camera::previousPos, Camera::dest;
bool Camera::isMoving, Camera::inWay, Camera::inWayBack, Camera::isZoomIn, Camera::isZoomOut;
bool Camera::zoomCreepy = false;
Timer Camera::time;

void Camera::SetType(int Ntype){
	type = Ntype;
	isMoving = false;
	if(type == CAMERA_TYPE3){
		pos.x = 80;
		pos.y = 80;
	}
}

void Camera::Follow(GameObject* newFocus, int Ntype){
	focus = newFocus;
	type = Ntype;
	if(type == 2){
		if(focus->box.CenterX() >= Game::GetInstance().GetCurrentState().GetStateLimits().w - OFFSET_TYPE2){
			pos.x = Game::GetInstance().GetCurrentState().GetStateLimits().w - Game::GetInstance().GetWidth()/2;
		} else if(focus->box.CenterX() <= Game::GetInstance().GetCurrentState().GetStateLimits().x + OFFSET_TYPE2){
			pos.x = Game::GetInstance().GetCurrentState().GetStateLimits().x + OFFSET_TYPE2/2 - Game::GetInstance().GetWidth()/2;
		}
		pos.y = 0;
	}
	isMoving = isZoomIn = isZoomOut = false;
}

void Camera::Unfollow(){
	focus = nullptr;
}

void Camera::Update(float dt){
	InputManager InputInstance = InputManager::GetInstance();
	if(focus != nullptr && !isMoving && !isZoomIn && !isZoomOut){
		if(type == CAMERA_TYPE1){
			pos.x = focus->box.CenterX() - Game::GetInstance().GetWidth()/2;
			pos.y = focus->box.CenterY() - Game::GetInstance().GetHeight()/2;
		} else if(type == CAMERA_TYPE2){
			if(focus->box.CenterX() < Game::GetInstance().GetCurrentState().GetStateLimits().w - OFFSET_TYPE2 &&
					focus->box.CenterX() > Game::GetInstance().GetCurrentState().GetStateLimits().x + OFFSET_TYPE2){
				pos.x = focus->box.CenterX() - Game::GetInstance().GetWidth()/2;
			}
		}
	} else if(isZoomIn){
		//std::cout << "ZOOM" << std::endl;
		time.Update(dt);
		if(time.Get() < tempo){
			MissionManager::missionManager->factorZoom = 1 + time.Get()*MAX_ZOOM/tempo;
		} else{
			isZoomIn = false;
			MissionManager::missionManager->factorZoom = 1 + MAX_ZOOM;
		}
		if(!zoomCreepy) UpdateZoom();
	} else if(isZoomOut){
		time.Update(dt);
		if(time.Get() < tempo){
			MissionManager::missionManager->factorZoom = 1 + (tempo - time.Get())*MAX_ZOOM/tempo;
		} else{
			isZoomOut = false;
			MissionManager::missionManager->factorZoom = 1;
			if(!zoomCreepy) MissionManager::player->SetBloqHUD(false);
			else MissionManager::player->SetBlocked(false);
			zoomCreepy = false;
		}
		if(!zoomCreepy) UpdateZoom();
	} else if(isMoving){
		// PODE SER UM ZOOM LOUCO, SE COLOCAR PELO SPRITE.HPP, DANDO PARA USAR EM CASOS BEM ESPECIFICOS, COMO NO QUARTO DA MAE
		// DESSE JEITO TEM PROBLEMA NO HUD E LEGENDA -> NAO MOSTRA-LOS NESSES MOMENTOS
		MissionManager::missionManager->factorZoom = 1 + ((origDist - pos.Distance(dest))*MAX_ZOOM/origDist);
		UpdateZoom();

		if(!inWayBack && pos.Distance(dest) < 5){
			//std::cout << pos.x << " - " << dest.x << " = " << pos.Distance(dest) << std::endl;
			pos = dest;
			inWay = false;
		} else if(inWay){
			pos.x -= speed.x;
			pos.y -= speed.y;
		}

		if(!inWay && !inWayBack){
			time.Update(dt);

			if(time.Get() >= tempo){
				inWayBack = true;
			}
		}

		if(inWayBack && pos.Distance(previousPos) < 5){
			//std::cout << pos.x << " - " << previousPos.x << " = " << pos.Distance(previousPos) << std::endl;
			pos = previousPos;
			inWayBack = false;
			isMoving = false;
			MissionManager::player->SetBloqHUD(false);
		} else if(inWayBack){
			pos.x += speed.x;
			pos.y += speed.y;
		}

	}
}

void Camera::Move(int xd, int yd, float tempoN){
	isMoving = true;
	inWay = true;
	inWayBack = false;
	tempo = tempoN;

	dest.x = xd - Game::GetInstance().GetWidth()/2;
	dest.y = yd - Game::GetInstance().GetHeight()/2;

	time.Restart();
	previousPos = pos;

	speed = (pos - dest).Normalize() * 10;

	printf("P %f D %f S %f\n", pos.x, dest.x, speed.x);
	origDist = pos.Distance(dest);
	MissionManager::player->SetBloqHUD(true);
}

void Camera::DontMove(){
	isMoving = false;
	isZoomIn = false;
	isZoomOut = false;
	time.Restart();

	MissionManager::missionManager->factorZoom = 1;
	UpdateZoom();
}

void Camera::Zoom(float tempoN, bool in){
	if(in) isZoomIn = true;
	else isZoomOut = true;
	MissionManager::player->SetBloqHUD(true);
	tempo = tempoN;
	time.Restart();
}

void Camera::ZoomCreepy(float tempoN, bool in){
	if(in) isZoomIn = true;
	else isZoomOut = true;
	MissionManager::player->SetBlocked(true);
	zoomCreepy = true;
	tempo = tempoN;
	time.Restart();
}

void Camera::ZoomCut(bool in){
	if(in){
		MissionManager::missionManager->factorZoom = 1.2;
		MissionManager::player->SetBloqHUD(true);
	} else{
		MissionManager::missionManager->factorZoom = 1;
		MissionManager::player->SetBloqHUD(false);
	}
	UpdateZoom();
}

void Camera::UpdateZoom(){
	SDL_RenderSetScale(Game::GetInstance().GetRenderer(),
			MissionManager::missionManager->factorZoom, MissionManager::missionManager->factorZoom);
}

bool Camera::GetMoving(){
	return isMoving;
}
