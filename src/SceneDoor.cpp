#include "SceneDoor.hpp"
#include "MissionManager.hpp"
#include "Mission.hpp"
#include "Player.hpp"

int SceneDoor::ValorPassar =15;
int SceneDoor::count = 200;

SceneDoor::SceneDoor(float x, float y, std::string dest, bool locked, std::string img, std::string img2) :
	SceneObject(x, y, img, img2), dest(dest) {

	lock = locked;
	changeState = false;
	//count =0;
	contador = 0;
}

bool SceneDoor::NotifyCollision(GameObject& other){
	if(other.Is("Bear") || other.Is("Enemy")){
			count ++;
			//std::cout << "teste door" << count << std::endl;
			if(count == 1)
				sp.Open(change2);
			if(count == ValorPassar)
				sp.Open(change1);
			box.x += box.w - sp.GetWidth();
			box.w = sp.GetWidth();
			box.h = sp.GetHeight();
			if((MissionManager::player->box.y + MissionManager::player->box.h - offset < box.y + box.h)
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

	if(!other.Is("EmptyBox")){
		SceneObject::NotifyCollision(other);
	} else{
		if(InputManager::GetInstance().KeyPress(Z_KEY) && lock == true){
				MissionManager::player->SetDoor(true);
		}
		if((InputManager::GetInstance().KeyPress(Z_KEY) && lock == false)){
			if(estado){
				changeState = true;
			} else{
				estado = true;
				sp.Open(change2);
				box.x += box.w - sp.GetWidth();
				box.w = sp.GetWidth();
				box.h = sp.GetHeight();

				if((MissionManager::player->box.y + MissionManager::player->box.h - offset < box.y + box.h)
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

	return false;
}

bool SceneDoor::Is(std::string type){
	return (type == "SceneDoor" || type == "CollidableObject");
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

void SceneDoor::SetChangeState(bool change){
	changeState = change;
}

std::string SceneDoor::GetDest(){
	return dest;
}
