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

bool MovingObject::NotifyCollision(GameObject& other){
	if(other.Is("EmptyBox")){
		if(InputManager::GetInstance().IsKeyDown(LCTRL_KEY) && InputManager::GetInstance().KeyPress(Z_KEY)){
			//colocar animacao para subir na cadeira
			if(!MissionManager::player->GetAboveObject()){
				MissionManager::player->box.x = box.x + box.w/2 - MissionManager::player->box.w/2;
				MissionManager::player->box.y = box.y + box.h/2 - MissionManager::player->box.h/2 - 12;
				MissionManager::player->ChangeAboveObject();
				return true;
			} else{
				MissionManager::player->box.x = MissionManager::player->previousPos.x;
				MissionManager::player->box.y = MissionManager::player->previousPos.y;
				MissionManager::player->ChangeAboveObject();
				return false;
			}
		} else if(InputManager::GetInstance().IsKeyDown(Z_KEY) && !MissionManager::player->GetAboveObject()){
			MissionManager::missionManager->movingBox = true;
			previousPos = Vec2(box.x, box.y);
			bool bloqMov = false;
			Rect boxAux = box, boxAuxPlayer = MissionManager::player->box;
			boxAux.x += MissionManager::player->GetSpeed().x; boxAux.y += MissionManager::player->GetSpeed().y;
			boxAuxPlayer.x += MissionManager::player->GetSpeed().x; boxAuxPlayer.y += MissionManager::player->GetSpeed().y;
			for(unsigned int i = 0; i < MissionManager::player->wallLimits.size(); i++){
				bloqMov = boxAux.Collide(MissionManager::player->wallLimits[i]);
				if(bloqMov == true) break;
				bloqMov = boxAuxPlayer.Collide(MissionManager::player->wallLimits[i]);
				if(bloqMov == true) break;
			}

			if(boxAux.x < MissionManager::player->limits.w - boxAux.w &&
					boxAuxPlayer.x < MissionManager::player->limits.w - boxAuxPlayer.w &&
					boxAux.x > MissionManager::player->limits.x &&
					boxAuxPlayer.x > MissionManager::player->limits.x && !bloqMov){
				if((MissionManager::player->box).Intersect(box) &&
						(MissionManager::player->GetDirecao() == NORTE || MissionManager::player->GetDirecao() == SUL)){
					MissionManager::missionManager->movingBox = false;
				} else{
					box.x += MissionManager::player->GetSpeed().x;
				}
			}
			if(boxAux.y < MissionManager::player->limits.h - boxAux.h &&
					boxAuxPlayer.y < MissionManager::player->limits.h - boxAuxPlayer.h &&
					boxAux.y > MissionManager::player->limits.y &&
					boxAuxPlayer.y > MissionManager::player->limits.y && !bloqMov){
				if((MissionManager::player->box).Intersect(box) &&
						(MissionManager::player->GetDirecao() == NORTE || MissionManager::player->GetDirecao() == SUL)){
					MissionManager::missionManager->movingBox = false;
				} else{
					box.y += MissionManager::player->GetSpeed().y;
				}
			}
		} else MissionManager::missionManager->movingBox = false;
	}

	if(other.Is("Player")){
		return MissionManager::player->CollidingPlayer(box, box.h/3);
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

		if((other.box.y + other.box.h - box.h/3 < box.y + box.h)){
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

	return false;
}

bool MovingObject::Is(std::string type){
	return (type == "MovingObject" || type == "CollidableObject");
}
