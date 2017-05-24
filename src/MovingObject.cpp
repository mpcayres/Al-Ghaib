#include "MovingObject.hpp"
#include "Camera.hpp"
#include "InputManager.hpp"
#include "Player.hpp"

MovingObject::MovingObject(float x, float y, std::string img) : sp(img){
	rotation = 0;
	box.x = x; box.y = y;
	box.w = sp.GetWidth();
	box.h = sp.GetHeight();
}

bool MovingObject::IsDead(){
	return false;
}

void MovingObject::Update(float dt){

}

void MovingObject::Render(){
	sp.Render(box.x - Camera::pos.x, box.y - Camera::pos.y, rotation);
}

void MovingObject::NotifyCollision(GameObject& other){
	if(other.Is("EmptyBox")){
		if(InputManager::GetInstance().IsKeyDown(Z_KEY)){
			box.x += Player::player->GetSpeed().x;
			box.y += Player::player->GetSpeed().y;
		}
	}
	if(other.Is("Player")){
		if(Player::player->box.x < box.x + box.w ||
				Player::player->box.x + Player::player->box.w > box.x){
			Player::player->box.x = Player::player->previousPos.x;
		}
		if(Player::player->box.y < box.y + box.h ||
				Player::player->box.y + Player::player->box.h > box.y){
			Player::player->box.y = Player::player->previousPos.y;
		}
	}
}

bool MovingObject::Is(std::string type){
	return (type == "MovingObject");
}

