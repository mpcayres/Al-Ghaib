#include <StorageObject.hpp>
#include "Camera.hpp"
#include "InputManager.hpp"

StorageObject::StorageObject(float x, float y, int id, std::string img) : id(id), sp(img){
	dead = false;
	rotation = 0;
	box.x = x  - sp.GetWidth()/2;
	box.y = y  - sp.GetHeight()/2;
	box.w = sp.GetWidth();
	box.h = sp.GetHeight();
}

void StorageObject::Update(float dt){

}

void StorageObject::Render(){
	sp.Render(box.x - Camera::pos.x, box.y - Camera::pos.y, rotation);
}

bool StorageObject::IsDead(){
	return dead;
}

void StorageObject::NotifyCollision(GameObject& other){
	if(!dead && other.Is("Player")){
		if(InputManager::GetInstance().KeyPress(Z_KEY)){
			dead = true;
			// adicionar ao inventário pelo id
			// ver alguma animação
		}
	}
}

bool StorageObject::Is(std::string type){
	return (type == "StorageObject");
}
