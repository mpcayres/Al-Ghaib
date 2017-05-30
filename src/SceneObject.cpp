#include "SceneObject.hpp"

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
		if((Player::player->box.CenterX() < box.x /*+ box.w*/ /*- Player::player->box.w*/ ||
				Player::player->box.CenterX() /*+ Player::player->box.w */> box.x /*- Player::player->box.w*/ )
				&&(Player::player->box.y + Player::player->box.h - OFFSET_PISO < box.y + box.h)) {

				Player::player->box.x = Player::player->previousPos.x;

		}

		if(Player::player->box.y + Player::player->box.h - OFFSET_PISO < box.y + box.h  /*- Player::player->box.h*/||
				Player::player->box.y/* + Player::player->box.h*/ > box.y + box.h /*- Player::player->box.h*/){
			Player::player->box.y = Player::player->previousPos.y;
		}
	}

	if (other.Is("MovingObject") || other.Is("Enemy")){
		if(other.box.y + other.box.h - OFFSET_PISO < box.y + box.h)
							/*&& (Player::player->GetDirecao() == Player::LESTE ||
								Player::player->GetDirecao() == Player::OESTE))*/{

				if((other.box.x < box.x + box.w &&
						other.box.x + other.box.w > box.x + box.w )
						|| (box.InsideX(other.box) &&
						other.box.CenterX() >= box.CenterX())){
									other.box.x = box.x + box.w + 1;
				} else if((other.box.x + other.box.w > box.x &&
						other.box.x < box.x)
						|| (box.InsideX(Player::player->box) &&
						other.box.CenterX() < box.CenterX())){
								other.box.x = box.x - other.box.w - 1;
				}

		}
	}
}

bool SceneObject::Is(std::string type){
	return (type == "SceneObject");
}
