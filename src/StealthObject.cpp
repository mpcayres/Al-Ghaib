#include "StealthObject.hpp"
#include "Camera.hpp"
#include "InputManager.hpp"
#include "Player.hpp"
#include "MissionManager.hpp"
#include "Geometry.hpp"

StealthObject::StealthObject(float x, float y, std::string img) : sp(img){
	rotation = 0;
	box.x = x; box.y = y;
	box.w = sp.GetWidth();
	box.h = sp.GetHeight();
}

bool StealthObject::IsDead(){
	return false;
}

void StealthObject::Update(float dt){

}

void StealthObject::Render(){
	sp.Render(box.x - Camera::pos.x, box.y - Camera::pos.y, rotation);
}

bool StealthObject::NotifyCollision(GameObject& other){
	if(other.Is("EmptyBox")){
		if(InputManager::GetInstance().KeyPress(Z_KEY)){
			//pode mostrar uma animacao aqui
			MissionManager::player->ChangeHiddenState();
		}
	}

	if(other.Is("Player")){
		return MissionManager::player->CollidingPlayer(box, box.h/3);
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

	return false;
}

void StealthObject::SetMovementLimits(Rect limits){
	this->limits.x = limits.x;
	this->limits.y = limits.y;
	this->limits.w = limits.w;
	this->limits.h = limits.h;
}

bool StealthObject::Is(std::string type){
	return (type == "StealthObject" || type == "CollidableObject");
}

