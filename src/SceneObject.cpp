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
		if((MissionManager::player->box.CenterX() < box.x /*+ box.w*/ /*- MissionManager::player->box.w*/ ||
				MissionManager::player->box.CenterX() /*+ MissionManager::player->box.w */> box.x /*- MissionManager::player->box.w*/ )
				&&(MissionManager::player->box.y + MissionManager::player->box.h - OFFSET_PISO < box.y + box.h)) {

				MissionManager::player->box.x = MissionManager::player->previousPos.x;

		}

		if(MissionManager::player->box.y + MissionManager::player->box.h - OFFSET_PISO < box.y + box.h  /*- MissionManager::player->box.h*/||
				MissionManager::player->box.y/* + MissionManager::player->box.h*/ > box.y + box.h /*- MissionManager::player->box.h*/){
			MissionManager::player->box.y = MissionManager::player->previousPos.y;
		}
	}

	if (other.Is("Enemy")){
		if(other.box.y + other.box.h - OFFSET_PISO < box.y + box.h)
							/*&& (MissionManager::player->GetDirecao() == Player::LESTE ||
								MissionManager::player->GetDirecao() == Player::OESTE))*/{

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
}

bool SceneObject::Is(std::string type){
	return (type == "SceneObject" || type == "CollidableObject");
}
