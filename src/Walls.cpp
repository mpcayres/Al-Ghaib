#include "Walls.hpp"

#include "Geometry.hpp"
#include "Sprite.hpp"
#include "Game.hpp"
#include "Player.hpp"
#include "MissionManager.hpp"
#include "Camera.hpp"
#include "InputManager.hpp"
#include <iostream>

Walls::Walls(float x, float y, float w, float h){
	rotation = 0;
	box.x = x;
	box.y = y;
	box.w = w;
	box.h = h;
}

Walls::~Walls(){

}

void Walls::Render(){
	SDL_Rect dst;
	dst.x = box.x - Camera::pos.x; dst.y = box.y - Camera::pos.y;
	dst.h = box.h; dst.w = box.w;
	SDL_RenderDrawRect(Game::GetInstance().GetRenderer(), &dst);
}

bool Walls::NotifyCollision(GameObject& other){

	if(other.Is("Player")){
		if(MissionManager::player->box.x < box.x + box.w ||
			MissionManager::player->box.x + MissionManager::player->box.w > box.x){
				MissionManager::player->box.x = MissionManager::player->previousPos.x;
		}
		if(MissionManager::player->box.y < box.y + box.h ||
			MissionManager::player->box.y + MissionManager::player->box.h > box.y){
				MissionManager::player->box.y = MissionManager::player->previousPos.y;
		}
	}

	/*if (other.Is("Enemy")){
		if(other.box.x < box.x + box.w ||
				other.box.x + other.box.w > box.x){
			other.box.x = box.x + box.w + 1;
		} else if(other.box.y < box.y + box.h ||
				other.box.y + other.box.h > box.y){
			other.box.x = box.x - other.box.w - 1;
		}
	}*/

	if (other.Is("Enemy")){
		std::cout << "BATEU" <<std::endl;
			if(other.box.x < box.x + box.w ||
					other.box.x + other.box.w > box.x){
				other.box.x =  other.previousPos.x;
			} else if(other.box.y < box.y + box.h ||
					other.box.y + other.box.h > box.y){
				other.box.y =  other.previousPos.y;
			}
	}

	return false;

}

bool Walls::Is(std::string type){
	return (type == "Wall" || type == "CollidableObject");
}

bool Walls::IsDead(){
	return false;
}

void Walls::Update(float dt){
}
