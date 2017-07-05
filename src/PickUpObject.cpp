#include "PickUpObject.hpp"
#include "Camera.hpp"
#include "InputManager.hpp"
#include "Player.hpp"
#include <iostream>

PickUpObject::PickUpObject(float x, float y, std::string obj, std::string img, bool bloq, float scaleX, float scaleY) :
	obj(obj), sp(img){
	sp.SetScaleX(scaleX); sp.SetScaleY(scaleY);
	dead = false;
	bloqPick = bloq;
	rotation = 0;
	box.x = x  - sp.GetWidth()/2;
	box.y = y  - sp.GetHeight()/2;
	box.w = sp.GetWidth();
	box.h = sp.GetHeight();
}

void PickUpObject::Update(float dt){

}

void PickUpObject::Render(){
	sp.Render(box.x - Camera::pos.x, box.y - Camera::pos.y, rotation);
}

bool PickUpObject::IsDead(){
	return dead;
}

// Talvez colocar pra pegar quando estiver proximo
bool PickUpObject::NotifyCollision(GameObject& other){
	if(!dead && other.Is("Player") && !bloqPick && !MissionManager::player->GetAboveObject()){
		if(InputManager::GetInstance().KeyPress(Z_KEY)){
			dead = true;
			MissionManager::player->AddInventory(obj);
		}
	}

	if(!dead && other.Is("EmptyBox") && bloqPick && MissionManager::player->GetAboveObject()){
		if(InputManager::GetInstance().KeyPress(Z_KEY)){
			dead = true;
			MissionManager::player->AddInventory(obj);
		}
	}
	return false;
}

bool PickUpObject::Is(std::string type){
	return (type == "PickUpObject");
}
