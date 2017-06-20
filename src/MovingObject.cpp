#include "MovingObject.hpp"
#include "Camera.hpp"
#include "InputManager.hpp"
#include "Player.hpp"
#include "MissionManager.hpp"
#include "Geometry.hpp"

MovingObject::MovingObject(float x, float y, std::string img) : sp(img){
	rotation = 0;
	box.x = x; box.y = y;
	box.w = sp.GetWidth();
	box.h = sp.GetHeight();
	previousPos = Vec2(x,y);
}

bool MovingObject::IsDead(){
	return false;
}

void MovingObject::Update(float dt){

}

void MovingObject::Render(){
	sp.Render(box.x - Camera::pos.x, box.y - Camera::pos.y, rotation);
}

void MovingObject::NotifyCollision(GameObject& other){
	if(other.Is("EmptyBox")){
		//Se ficar aqui, so de chegar perto, ja entra na animacao de empurrar
		//MissionManager::missionManager->movingBox = true;
		if(InputManager::GetInstance().IsKeyDown(Z_KEY)){
			MissionManager::missionManager->movingBox = true;
			previousPos = Vec2(box.x, box.y);
			bool bloqMov = false;
			Rect boxAux = box;
			boxAux.x += MissionManager::player->GetSpeed().x; boxAux.y += MissionManager::player->GetSpeed().y;
			for(unsigned int i = 0; i < MissionManager::player->wallLimits.size(); i++){
				bloqMov = boxAux.Collide(MissionManager::player->wallLimits[i]);
				if(bloqMov == true) break;
			}

			if(boxAux.x < MissionManager::player->limits.w - box.w &&
					boxAux.x > MissionManager::player->limits.x && !bloqMov){
				box.x += MissionManager::player->GetSpeed().x;
				if((MissionManager::player->box).Intersect(box)) box.x -= MissionManager::player->GetSpeed().x;
			}
			if(boxAux.y < MissionManager::player->limits.h - box.h &&
					boxAux.y > MissionManager::player->limits.y && !bloqMov){
				box.y += MissionManager::player->GetSpeed().y;
				if((MissionManager::player->box).Intersect(box)) box.y -= MissionManager::player->GetSpeed().y;
			}
		} else MissionManager::missionManager->movingBox = false;
	}

	if(other.Is("Player")){
		/*if(MissionManager::player->box.x < box.x + box.w ||
				MissionManager::player->box.x + MissionManager::player->box.w > box.x){
			MissionManager::player->box.x = MissionManager::player->previousPos.x;
		}
		if(MissionManager::player->box.y < box.y + box.h ||
				MissionManager::player->box.y + MissionManager::player->box.h > box.y){
			MissionManager::player->box.y = MissionManager::player->previousPos.y;
		}*/

		if((MissionManager::player->box.y + MissionManager::player->box.h - OFFSET_MOVI < box.y + box.h)){

			if((MissionManager::player->box.x < box.x + box.w &&
					MissionManager::player->box.x + MissionManager::player->box.w > box.x + box.w )
					|| (box.InsideX(MissionManager::player->box) &&
							MissionManager::player->box.CenterX() >= box.CenterX())){
				if(MissionManager::player->GetDirecao() == Player::SUL || MissionManager::player->GetDirecao() == Player::NORTE ){
					MissionManager::player->box.x = MissionManager::player->previousPos.x;
					MissionManager::player->box.y = MissionManager::player->previousPos.y;
				} else{
					MissionManager::player->box.x = box.x + box.w + 1;
				}
			} else if((MissionManager::player->box.x + MissionManager::player->box.w > box.x &&
					MissionManager::player->box.x < box.x)
					|| (box.InsideX(MissionManager::player->box) &&
							MissionManager::player->box.CenterX() < box.CenterX())){
				if(MissionManager::player->GetDirecao() == Player::SUL || MissionManager::player->GetDirecao() == Player::NORTE ){
					MissionManager::player->box.x = MissionManager::player->previousPos.x;
					MissionManager::player->box.y = MissionManager::player->previousPos.y;
				} else{
					MissionManager::player->box.x = box.x - MissionManager::player->box.w - 1;
				}
			}

		}
	}

	if(other.Is("CollidableObject")){
		box.x = previousPos.x;
		box.y = previousPos.y;
		if(MissionManager::player->box.x < box.x + box.w ||
				MissionManager::player->box.x + MissionManager::player->box.w > box.x){
			MissionManager::player->box.x = MissionManager::player->previousPos.x;
		}
		if(MissionManager::player->box.y < box.y + box.h ||
				MissionManager::player->box.y + MissionManager::player->box.h > box.y){
			MissionManager::player->box.y = MissionManager::player->previousPos.y;
		}
	}

	if (other.Is("Enemy")){
		/*if(other.box.x < box.x + box.w ||
				other.box.x + other.box.w > box.x){
			other.box.x = box.x + box.w + 1;
		} else if(other.box.y < box.y + box.h ||
				other.box.y + other.box.h > box.y){
			other.box.x = box.x - other.box.w - 1;
		}*/

		if((other.box.y + other.box.h - OFFSET_MOVI < box.y + box.h)){
			if((other.box.x < box.x + box.w &&other.box.x + other.box.w > box.x + box.w )
				|| (box.InsideX(other.box) && other.box.CenterX() >= box.CenterX())){

				if(other.direcao == 3|| other.direcao == 4 ){
					other.box.x = other.previousPos.x;
					other.box.y = other.previousPos.y;
				} else{
					other.box.x = box.x + box.w + 1;
				}
			} else if((other.box.x + other.box.w > box.x && other.box.x < box.x)
				|| (box.InsideX(other.box) && other.box.CenterX() < box.CenterX())){

				if(other.direcao == 3 || other.direcao == 4 ){
					other.box.x = other.previousPos.x;
					other.box.y = other.previousPos.y;
				} else{
					other.box.x = box.x - other.box.w - 1;
				}
			}
		}
	}

}

bool MovingObject::Is(std::string type){
	return (type == "MovingObject" || type == "CollidableObject");
}
