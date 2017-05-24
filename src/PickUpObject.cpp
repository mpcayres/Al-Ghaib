#include "PickUpObject.hpp"
#include "Camera.hpp"
#include "InputManager.hpp"
#include "Player.hpp"

PickUpObject::PickUpObject(float x, float y, std::string obj, std::string img) :
	obj(obj)/*, objSp(img)*/, sp(img){
	dead = false;
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

// Talvez colocar pra pegar quando estiver pr�ximo
void PickUpObject::NotifyCollision(GameObject& other){
	if(!dead && other.Is("Player")){
		if(InputManager::GetInstance().KeyPress(Z_KEY)){
			dead = true;
			Player::player->AddInventory(obj/*, objSp*/);
			// ver alguma anima��o
		}
	}
}

bool PickUpObject::Is(std::string type){
	return (type == "PickUpObject");
}