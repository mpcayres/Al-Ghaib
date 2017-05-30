#include "EmptyBox.hpp"
#include "Camera.hpp"
#include "InputManager.hpp"
#include "SceneDoor.hpp"
#include "Player.hpp"
#include "Game.hpp"

EmptyBox::EmptyBox( ){
	rotation = 0;
	box.x = Player::player->box.x + Player::player->box.w;
	box.y = Player::player->box.y;
	box.w = DISTANCIA;
	box.h = Player::player->box.h;
	inHand = Player::player->GetInHand();
}

void EmptyBox::Update(float dt){
	/*Vec2 rot = Vec2(Player::player->box.x - Player::player->box.CenterX(),
			Player::player->box.y - Player::player->box.CenterY());
	rot = rot.Rotate(Player::player->rotation*PI/180);*/
	switch(Player::player->GetDirecao()){
		case Player::NORTE:		//NORTE
			//box.x = rot.x + Player::player->box.CenterX();
			//box.y = rot.y + Player::player->box.CenterY() - DISTANCIA;
			box.x = Player::player->box.x;
			box.y = Player::player->box.y - DISTANCIA;
			box.w = Player::player->box.h;
			box.h = DISTANCIA + Player::player->box.w;
			break;
		case Player::SUL:		//SUL
			//box.x = rot.x + Player::player->box.CenterX();
			//box.y = rot.y + Player::player->box.CenterY();
			box.x = Player::player->box.x;
			box.y = Player::player->box.y;
			box.w = Player::player->box.h;
			box.h = DISTANCIA + Player::player->box.w;
			break;
		case Player::LESTE:		//LESTE
			box.x = Player::player->box.x;
			box.y = Player::player->box.y;
			box.w = DISTANCIA + Player::player->box.w;
			box.h = Player::player->box.h;
			break;
		case Player::OESTE:		//OESTE
			box.x = Player::player->box.x - DISTANCIA;
			box.y = Player::player->box.y;
			box.w = DISTANCIA + Player::player->box.w;
			box.h = Player::player->box.h;
			break;
	}
	inHand = Player::player->GetInHand();
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

void EmptyBox::NotifyCollision(GameObject& other){
	if(other.Is("SceneDoor")){
		if(InputManager::GetInstance().KeyPress(X_KEY) && inHand != nullptr){
			if(inHand->Action(&other) == true)
				Player::player->DeleteInventory();
		}
	}
}

bool EmptyBox::Is(std::string type){
	return (type == "EmptyBox");
}
