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
			bool bloqMov = false;
			Rect boxAux = box;
			boxAux.x += MissionManager::player->GetSpeed().x; boxAux.y += MissionManager::player->GetSpeed().y;
			for(unsigned int i = 0; i < MissionManager::player->wallLimits.size(); i++){
				bloqMov = boxAux.Collide(MissionManager::player->wallLimits[i]);
				if(bloqMov == true) break;
			}

			if(boxAux.x < MissionManager::player->limits.w - box.w &&
					boxAux.x > MissionManager::player->limits.x && !bloqMov){
				box.x += MissionManager::player->GetSpeed().x;
				if((MissionManager::player->box).Intersect(box)) box.x -= MissionManager::player->GetSpeed().x;
			}
			if(boxAux.y < MissionManager::player->limits.h - box.h &&
					boxAux.y > MissionManager::player->limits.y && !bloqMov){
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

bool MovingObject::Is(std::string type){
	return (type == "MovingObject" || type == "CollidableObject");
}

