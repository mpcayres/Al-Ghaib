#include "MovingObject.hpp"
#include "Camera.hpp"
#include "InputManager.hpp"
#include "Player.hpp"
#include "MissionManager.hpp"
#include "Geometry.hpp"

MovingObject::MovingObject(float x, float y, std::string img) : sp(img){
	rotation = 0;
	box.x = x; box.y = y;
	box.w = sp.GetWidth();
	box.h = sp.GetHeight();
	previousPos = Vec2(x,y);
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
			previousPos = Vec2(box.x, box.y);

			if(box.x + MissionManager::player->GetSpeed().x < limits.w - box.w && box.x + MissionManager::player->GetSpeed().x > limits.x){
				box.x += MissionManager::player->GetSpeed().x;
				if((MissionManager::player->box).Intersect(box)) box.x -= MissionManager::player->GetSpeed().x;
			}
			if(box.y + MissionManager::player->GetSpeed().y < limits.h - box.h && box.y + MissionManager::player->GetSpeed().y > limits.y){
				box.y += MissionManager::player->GetSpeed().y;
				if((MissionManager::player->box).Intersect(box)) box.y -= MissionManager::player->GetSpeed().y;
			}
		}
	}

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

	if(other.Is("CollidableObject")){
		box.x = previousPos.x;
		box.y = previousPos.y;
		if(MissionManager::player->box.x < box.x + box.w ||
				MissionManager::player->box.x + MissionManager::player->box.w > box.x){
			MissionManager::player->box.x = MissionManager::player->previousPos.x;
		}
		if(MissionManager::player->box.y < box.y + box.h ||
				MissionManager::player->box.y + MissionManager::player->box.h > box.y){
			MissionManager::player->box.y = MissionManager::player->previousPos.y;
		}
	}

	if (other.Is("Enemy")){
		if(other.box.x < box.x + box.w ||
				other.box.x + other.box.w > box.x){
			other.box.x = box.x + box.w + 1;
		} else if(other.box.y < box.y + box.h ||
				other.box.y + other.box.h > box.y){
			other.box.x = box.x - other.box.w - 1;
		}
	}
}

void MovingObject::SetMovementLimits(Rect limits){
	this->limits.x = limits.x;
	this->limits.y = limits.y;
	this->limits.w = limits.w;
	this->limits.h = limits.h;
}

bool MovingObject::Is(std::string type){
	return (type == "MovingObject" || type == "CollidableObject");
}

