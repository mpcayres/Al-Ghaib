#include "SceneDoor.hpp"

bool SceneDoor::changeState;

SceneDoor::SceneDoor(float x, float y, std::string img, std::string img2) :
	SceneObject(x, y, img, img2) {
	lock = true;
	changeState = false;
}

void SceneDoor::NotifyCollision(GameObject& other){
	SceneObject::NotifyCollision(other);
	if(other.Is("EmptyBox")){
		if(InputManager::GetInstance().KeyPress(Z_KEY) && lock == false){
			if(estado){
				changeState = true;
			} else{
				estado = true;
				sp.Open(change2);
				box.w = sp.GetWidth();
				box.h = sp.GetHeight();

				//Nesse caso nao precisa no eixo y
				if((Player::player->box.y + Player::player->box.h - OFFSET_PISO < box.y + box.h)
					&& (Player::player->GetDirecao() == Player::LESTE ||
						Player::player->GetDirecao() == Player::OESTE)){

					if((Player::player->box.x < box.x + box.w &&
							Player::player->box.x + Player::player->box.w > box.x + box.w )
							|| (box.InsideX(Player::player->box) &&
									Player::player->box.CenterX() >= box.CenterX())){
						Player::player->box.x = box.x + box.w + 1;
					} else if((Player::player->box.x + Player::player->box.w > box.x &&
							Player::player->box.x < box.x)
							|| (box.InsideX(Player::player->box) &&
									Player::player->box.CenterX() < box.CenterX())){
						Player::player->box.x = box.x - Player::player->box.w - 1;
					}

				}
			}
		}
	}
}

bool SceneDoor::Is(std::string type){
	return (type == "SceneDoor");
}

bool SceneDoor::ReceiveAction(InventoryObject* other){
	if(other->IsObject("InventoryKey")){
		if(lock == true){
			lock = false;
			return true;
		}
	}
	return false;
}

bool SceneDoor::GetChangeState(){
	return changeState;
}
