/*
 * EmptyBox.cpp
 *
 *  Created on: May 18, 2017
 *      Author: ingrid
 */

#include "EmptyBox.hpp"
#include "Camera.hpp"
#include "InputManager.hpp"
#include "Player.hpp"

EmptyBox::EmptyBox(float x, float y){
	box.x = x;
	box.y = y;
	box.w = DISTANCIA;
	box.h = Player::player->box.h;
}

void EmptyBox::Render(){

}
bool EmptyBox::IsDead(){
return false;
}

void EmptyBox::Update(float dt){
	printf("invbox %d" , Player::player->getInvBox());
	printf("\n BOX box.x = %f, box.y = %f", box.x, box.y);

	switch(Player::player->getInvBox()){
	case 0:		//NORTE
		box.x = Player::player->box.x;
		box.y = Player::player->box.y - DISTANCIA;
		box.w = Player::player->box.w;
		box.h = DISTANCIA;
		break;
	case 1:		//SUL
		box.x = Player::player->box.x;
		box.y = Player::player->box.h + Player::player->box.y;
		box.w = Player::player->box.w;
		box.h = DISTANCIA;
		break;
	case 2:		//LESTE
		box.x = Player::player->box.x + Player::player->box.w;
		box.y = Player::player->box.y;
		box.w = DISTANCIA;
		box.h = Player::player->box.h;
		break;
	case 3:		//OESTE
		box.x = Player::player->box.x - DISTANCIA;
		box.y = Player::player->box.y;
		box.w = DISTANCIA;
		box.h = Player::player->box.h;
		break;
	}

}


// Talvez colocar pra pegar quando estiver pr�ximo
void EmptyBox::NotifyCollision(GameObject& other){
	/*if(!dead && other.Is("Player")){
		if(InputManager::GetInstance().KeyPress(Z_KEY)){
			dead = true;
			// adicionar ao invent�rio pelo id
			// ver alguma anima��o
		}
	}*/
}

bool EmptyBox::Is(std::string type){
	return (type == "EmptyBox");
}
