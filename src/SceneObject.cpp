#include "SceneObject.hpp"
#include "MissionManager.hpp"

SceneObject::SceneObject(float x, float y, std::string img, std::string img2) : sp(img) {
	this->change1 = img;
	this->change2 = img2;
	estado = false;
	rotation = 0;
	box.x = x; box.y = y;
	box.w = sp.GetWidth();
	box.h = sp.GetHeight();
}

bool SceneObject::IsDead(){
	return false;
}

void SceneObject::Update(float dt){

}

void SceneObject::Render(){
	sp.Render(box.x - Camera::pos.x, box.y - Camera::pos.y, rotation);
}

bool SceneObject::IsEstado(){
	return estado;
}

void SceneObject::NotifyCollision(GameObject& other){
	if(other.Is("Player")){
		if((MissionManager::player->box.CenterX() < box.x || MissionManager::player->box.CenterX() > box.x )
				&&(MissionManager::player->box.y + MissionManager::player->box.h - OFFSET_PISO < box.y + box.h)) {

			MissionManager::player->box.x = MissionManager::player->previousPos.x;

		}

		if(MissionManager::player->box.y + MissionManager::player->box.h - OFFSET_PISO < box.y + box.h ||
				MissionManager::player->box.y/* + MissionManager::player->box.h*/ > box.y + box.h){
			MissionManager::player->box.y = MissionManager::player->previousPos.y;
		}
	}

	if (other.Is("Enemy")){
		if(other.box.y + other.box.h - OFFSET_PISO < box.y + box.h){

			if((other.box.x < box.x + box.w &&
					other.box.x + other.box.w > box.x + box.w )
					|| (box.InsideX(other.box) &&
					other.box.CenterX() >= box.CenterX())){
								other.box.x = box.x + box.w + 1;
			} else if((other.box.x + other.box.w > box.x &&
					other.box.x < box.x)
					|| (box.InsideX(MissionManager::player->box) &&
					other.box.CenterX() < box.CenterX())){
							other.box.x = box.x - other.box.w - 1;
			}

		}
	}

	if(other.Is("EmptyBox")){
		if(InputManager::GetInstance().KeyPress(Z_KEY)){
			if(estado){
				estado = false;
				sp.Open(change1);
				box.x = box.x + box.w/2 - sp.GetWidth()/2;
				box.y = box.y + box.h/2 - sp.GetHeight()/2;
				box.w = sp.GetWidth();
				box.h = sp.GetHeight();
			} else{
				estado = true;
				sp.Open(change2);
				box.x = box.x + box.w/2 - sp.GetWidth()/2;
				box.y = box.y + box.h/2 - sp.GetHeight()/2;
				box.w = sp.GetWidth();
				box.h = sp.GetHeight();

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

					/*if((MissionManager::player->box.y < box.y + box.h &&
							MissionManager::player->box.y + MissionManager::player->box.h > box.y + box.h )
							|| (box.InsideY(MissionManager::player->box) &&
									MissionManager::player->box.CenterY() >= box.CenterY())){
						MissionManager::player->box.y = box.y + box.h + 1;
					} else if((MissionManager::player->box.y + MissionManager::player->box.h > box.y &&
							MissionManager::player->box.y < box.y)
							|| (box.InsideY(MissionManager::player->box) &&
									MissionManager::player->box.CenterY() < box.CenterY())){
						MissionManager::player->box.y = box.y - MissionManager::player->box.h - 1;
					}*/

				}
			}
		}
	}

}

bool SceneObject::Is(std::string type){
	return (type == "SceneObject" || type == "CollidableObject");
}
