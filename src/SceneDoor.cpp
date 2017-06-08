#include "SceneDoor.hpp"
#include "MissionManager.hpp"

SceneDoor::SceneDoor(float x, float y, std::string img, std::string img2, std::string dest) :
	SceneObject(x, y, img, img2), dest(dest) {
	SDL_Color auxcolor = SDL_Color();
	auxcolor.r = 102;
	auxcolor.g = 0;
	auxcolor.b = 0;
	lock = true;
	changeState = false;
	//tried = false;
}

void SceneDoor::NotifyCollision(GameObject& other){
	SceneObject::NotifyCollision(other);
	if(other.Is("EmptyBox")){
		if(InputManager::GetInstance().KeyPress(Z_KEY) && lock == true){
			// mensagem de q n pode abrir porta
		}
		if(InputManager::GetInstance().KeyPress(Z_KEY) && lock == false){
			if(estado){
				changeState = true;
			} else{
				estado = true;
				sp.Open(change2);
				box.x += box.w - sp.GetWidth();
				box.w = sp.GetWidth();
				box.h = sp.GetHeight();

				//Nesse caso nao precisa no eixo y
				if((MissionManager::player->box.y + MissionManager::player->box.h - OFFSET_PISO < box.y + box.h)
					&& (MissionManager::player->GetDirecao() == Player::LESTE ||
						MissionManager::player->GetDirecao() == Player::OESTE)){

					if((MissionManager::player->box.x < box.x + box.w &&
							MissionManager::player->box.x + MissionManager::player->box.w > box.x + box.w )
							|| (box.InsideX(MissionManager::player->box) &&
									MissionManager::player->box.CenterX() >= box.CenterX())){
						MissionManager::player->box.x = box.x + box.w + 1;
					} else if((MissionManager::player->box.x + MissionManager::player->box.w > box.x &&
							MissionManager::player->box.x < box.x)
							|| (box.InsideX(MissionManager::player->box) &&
									MissionManager::player->box.CenterX() < box.CenterX())){
						MissionManager::player->box.x = box.x - MissionManager::player->box.w - 1;
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
/*bool SceneDoor::Tried(){
	return tried;
}*/
bool SceneDoor::GetChangeState(){
	return changeState;
}

void SceneDoor::SetChangeState(bool change){
	changeState = change;
}

std::string SceneDoor::GetDest(){
	return dest;
}
