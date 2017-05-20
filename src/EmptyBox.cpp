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
#include "Game.hpp"

EmptyBox::EmptyBox( ){
	rotation = 0;
	this->box.x = Player::player->box.x + Player::player->box.w + OFFSET;
	this->box.y = Player::player->box.y;
	this->box.w = DISTANCIA;
	this->box.h = Player::player->box.h;
}

void EmptyBox::Render(){
	//printf("invbox %d" , Player::player->getInvBox());
		//printf("\n BOX box.x = %f, box.y = %f", box.x, box.y);

	SDL_Rect dst;
	dst.x = this->box.x- Camera::pos.x, dst.y = this->box.y- Camera::pos.y;
	dst.h = this->box.h; dst.w = this->box.w;
	//SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture.get(),
	//		&clipRect, &dst, angle, nullptr, SDL_FLIP_NONE);
	SDL_RenderDrawRect(Game::GetInstance().GetRenderer() , &dst);
	//SDL_Surface *s;
	/* Creating the surface. */
	//s = SDL_CreateRGBSurface(0, box.w, box.h, 32, 0, 0, 0, 0);
	/* Filling the surface with red color. */
	//SDL_FillRect(s, NULL, SDL_MapRGB(s->format, 2OFFSETOFFSET, 0, 0));




	//sp.Render(box.x - Camera::pos.x, box.y - Camera::pos.y, rotation);
}
bool EmptyBox::IsDead(){
return false;
}

void EmptyBox::Update(float dt){
	Vec2 rot = Vec2(Player::player->box.x, Player::player->box.y);
			rot.Rotate(Player::player->rotation);
			switch(Player::player->getInvBox()){
			case 0:		//NORTE
				this->box.x = rot.x + Player::player->box.h/2;
				this->box.y = rot.y - DISTANCIA - Player::player->box.w/2 + OFFSET;
				this->box.w = Player::player->box.h;
				this->box.h = DISTANCIA;
				break;
			case 1:		//SUL
				this->box.x = rot.x  + Player::player->box.h/2;
				this->box.y = Player::player->box.h + rot.y  + Player::player->box.w/2 - OFFSET;
				this->box.w = Player::player->box.h;
				this->box.h = DISTANCIA;
				break;
			case 2:		//LESTE
				this->box.x = Player::player->box.x + Player::player->box.w + OFFSET;
				this->box.y = Player::player->box.y;
				this->box.w = DISTANCIA;
				this->box.h = Player::player->box.h;
				break;
			case 3:		//OESTE
				this->box.x = Player::player->box.x - DISTANCIA - OFFSET;
				this->box.y = Player::player->box.y;
				this->box.w = DISTANCIA;
				this->box.h = Player::player->box.h;
				break;
			}

}


// Talvez colocar pra pegar quando estiver pr�ximo
void EmptyBox::NotifyCollision(GameObject& other){
	//printf("\nhere");
	if(other.Is("SceneObject")){
		//printf("\nbatendo");
	}
}

bool EmptyBox::Is(std::string type){
	return (type == "EmptyBox");
}
