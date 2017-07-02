#include "EmptyBox.hpp"
#include "Camera.hpp"
#include "InputManager.hpp"
#include "SceneDoor.hpp"
#include "Player.hpp"
#include "MissionManager.hpp"
#include "Game.hpp"

EmptyBox::EmptyBox( ){
	rotation = 0;
	box.x = MissionManager::player->box.x + MissionManager::player->box.w;
	box.y = MissionManager::player->box.y;
	box.w = DISTANCIA;
	box.h = MissionManager::player->box.h;
	inHand = MissionManager::player->GetInHand();
}

void EmptyBox::Update(float dt){
	/*Vec2 rot = Vec2(MissionManager::player->box.x - MissionManager::player->box.CenterX(),
			MissionManager::player->box.y - MissionManager::player->box.CenterY());
	rot = rot.Rotate(MissionManager::player->rotation*PI/180);*/
	switch(MissionManager::player->GetDirecao()){
		case Player::NORTE:		//NORTE
			//box.x = rot.x + MissionManager::player->box.CenterX();
			//box.y = rot.y + MissionManager::player->box.CenterY() - DISTANCIA;
			box.x = MissionManager::player->box.x + REDUCE_BOX;
			box.y = MissionManager::player->box.y - DISTANCIA;
			box.w = MissionManager::player->box.h - 2*REDUCE_BOX;
			box.h = DISTANCIA + MissionManager::player->box.w;
			break;
		case Player::SUL:		//SUL
			//box.x = rot.x + MissionManager::player->box.CenterX();
			//box.y = rot.y + MissionManager::player->box.CenterY();
			box.x = MissionManager::player->box.x + REDUCE_BOX;
			box.y = MissionManager::player->box.y;
			box.w = MissionManager::player->box.h - 2*REDUCE_BOX;
			box.h = DISTANCIA + MissionManager::player->box.w;
			break;
		case Player::LESTE:		//LESTE
			box.x = MissionManager::player->box.x;
			box.y = MissionManager::player->box.y + REDUCE_BOX;
			box.w = DISTANCIA + MissionManager::player->box.w;
			box.h = MissionManager::player->box.h - 2*REDUCE_BOX;
			break;
		case Player::OESTE:		//OESTE
			box.x = MissionManager::player->box.x - DISTANCIA;
			box.y = MissionManager::player->box.y + REDUCE_BOX;
			box.w = DISTANCIA + MissionManager::player->box.w;
			box.h = MissionManager::player->box.h - 2*REDUCE_BOX;
			break;
	}
	inHand = MissionManager::player->GetInHand();
}

void EmptyBox::Render(){
	SDL_Rect dst;
	dst.x = box.x - Camera::pos.x; dst.y = box.y - Camera::pos.y;
	dst.h = box.h; dst.w = box.w;
	SDL_RenderDrawRect(Game::GetInstance().GetRenderer(), &dst);
}

bool EmptyBox::IsDead(){
	return false;
}

bool EmptyBox::NotifyCollision(GameObject& other){
	if(other.Is("SceneDoor") && inHand != nullptr){
		if(InputManager::GetInstance().KeyPress(X_KEY) &&
				(inHand->IsObject("InventoryKey") || inHand->IsObject("InventoryArame"))){
			if(inHand->Action(&other) == true)
				MissionManager::player->DeleteInventory();
		}
	}
	return false;
}

bool EmptyBox::Is(std::string type){
	return (type == "EmptyBox");
}
